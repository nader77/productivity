<?php
/**
 * @file
 * Code for the Productivity time tracking feature.
 */

/**
 * Menu callback; Display monthly employee report.
 */
function productivity_timewatch_monthly_employee_report_callback($account = FALSE, $year = FALSE, $month = FALSE) {
  return productivity_timewatch_monthly_employee_report($account, $year, $month);
}

/**
 * Load all resources for the page.
 * @param $local
 */
function productivity_timewatch_monthly_employee_load_resources($local = FALSE) {
  // Add JavaScript file with the base url of the page.
  drupal_add_js(drupal_get_path('module', 'productivity_timewatch') . '/monthly_employee_report/monthly_employee_report.js');
  drupal_add_css(drupal_get_path('module', 'productivity_timewatch') . '/monthly_employee_report/monthly_employee_report.css');
  // No CDN.
  if ($local) {

    // Add Datepicker lib.
    drupal_add_js(drupal_get_path('theme', 'bootstrap_subtheme') . '/js/bootstrap-datepicker/js/bootstrap-datepicker.js');
    drupal_add_css(drupal_get_path('theme', 'bootstrap_subtheme') . '/js/bootstrap-datepicker/css/bootstrap-datepicker.min.css');// Add Datepicker lib.
    // Add select 2
    drupal_add_js(drupal_get_path('theme', 'bootstrap_subtheme') . '/js/select2/js/select2.js');
    drupal_add_css(drupal_get_path('theme', 'bootstrap_subtheme') . '/js/select2/css/select2.min.css');
  }
  else {
    // Add JavaScript file with the base url of the page.
    drupal_add_css('https://fonts.googleapis.com/css?family=Abril+Fatface', array('type' => 'external'));
    drupal_add_css("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/css/select2.min.css", array('type' => 'external'));
    drupal_add_js("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/js/select2.min.js", array('type' => 'external'));

    // Add Datepicker lib.
    drupal_add_js("https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.6.0/js/bootstrap-datepicker.min.js", array('type' => 'external'));
    drupal_add_css("https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.6.0/css/bootstrap-datepicker.min.css", array('type' => 'external'));
  }
}

/**
 */
function productivity_timewatch_monthly_employee_report($account = FALSE, $year = FALSE, $month = FALSE) {
  global $base_url;
  productivity_timewatch_monthly_employee_load_resources();

  $variables = array();
  $variables['year'] = !empty($year) ? $year : date('Y');
  $variables['month']= !empty($month) ? $month : date('m', strtotime("-1 month"));

  if ($year == 'all'){
    $variables['date'] = t('All time');
  }
  elseif ($month == 'all'){
    $variables['date'] = t('Year @year', array('@year' => $year));
  }
  else {
    $variables['date'] = date("F Y", strtotime("$year-$month-01"));
  }


  $variables['employees'] = user_load_multiple(productivity_account_get_employee_uids());
  $variables['current_uid'] = 0;
  $variables['project_title'] = 'Select a project';
  $variables['account'] = '';
  $variables['no_result'] = FALSE;
  $variables['message'] = '';
  $variables['table'] = '';

  drupal_add_js(array(
    'report' => array(
      'base_url' => $base_url,
      'year' => $variables['year'],
      'month' => $variables['month'],
    ),
  ), 'setting');

  // No project given.
  if (!$account) {
    return theme('productivity_timewatch_monthly_employee_report', $variables);
  }

  $wrapper = entity_metadata_wrapper('user', $account);

  $variables['fullname'] = $wrapper->field_full_name->label();

  $node_keys = productivity_timewatch_get_user_sessions($account->uid, $variables['year'], $variables['month']);
  $sessions = array();

  // Get all issues for the project.
  if ($node_keys) {
    $sessions = productivity_timewatch_create_issues_table($node_keys);
  }
  else {
    $variables['no_result'] = TRUE;
    $variables['message'] = t('No work done this month.');
  }

  $variables['theme_path'] = base_path() . drupal_get_path('theme', 'bootstrap_subtheme');

  // Create tables for the template.
  $variables['tables'] = array();
  $variables['total_types'] = array();
  $variables['grand_total'] = 0;
  $header = array('Date', 'Week day', 'Entry', 'Exit', 'Total', 'Project', 'Entry', 'Exit', 'Total', 'Project', 'Actual Total inc Missing');
  foreach ($sessions as $table_name => $table) {
    $variables['table_titles'][$table_name] = $table['label'];
    $variables['total_per_types'][$table_name] = 0;
    $variables['total_per_hours_types'][$table_name] = 0;

    foreach ($table['issues'] as $index => $issue) {
      $rows[$index]['label'] = l($issue['issue_num'], $project_url . $issue['issue_num'], array('absolute' => TRUE));
      $rows[$index]['gitHub_issue_num'] = $issue['label'];
      $rows[$index]['date'] = $issue['date'];
      $rows[$index]['time'] = $issue['time'];
      $rows[$index]['amount'] = $issue['issue_amount'] . ' ' . $issue['issue_currency'];
      $variables['total_per_types'][$table_name] += $issue['issue_amount'];
      $variables['total_per_hours_types'][$table_name] += $issue['time'];
      $variables['total_currency_per_types'][$table_name] = $issue['issue_currency'];
      $variables['grand_total'] += $issue['issue_amount'];
    }
    $variables['tables'][$table_name] = theme('table', array(
      'header' => $header,
      'rows' => $rows
    ));
    $rows = array();
  }

  // Get all the projects for project input
  $variables['current_uid'] = $account->uid;

  $variables['table'] = theme('productivity_timewatch_monthly_report_table', $variables);

  return theme('productivity_timewatch_monthly_employee_report', $variables);
}

/**
 * Create a matrix of all the issues from GitHub nodes,
 * And the url project.
 *
 * @param $nodes
 *  All the nodes return from the query.
 *
 * @return array
 *  Matrix of all the issues, and the URL project
 */
function productivity_timewatch_create_issues_table($node_keys) {
  $sessions = array();
  foreach($node_keys as $nid) {
    $wrapper = entity_metadata_wrapper('node', $nid);
    $start_time = $wrapper->field_session_date->value->value();
    $end_time = $wrapper->field_session_date->value2->value();
    $total_time = $end_time - $start_time;
    $hours = floor($total_time / 3600);
    $minutes = floor(($total_time % 3600) / 60);
    $day = date('d', $start_time);

    $sessions[$day][] = array(
      'session_start_date' => date('Y/m/d', $start_time),
      'session_start_time' => date('H:i', $start_time),
      'session_end_date' => date('Y/m/d', $end_time),
      'session_end_time' => date('H:i', $end_time),
      'project' => $wrapper->field_project->label(),
      'length' => $hours . ':' . str_pad($minutes, 2, '0', STR_PAD_LEFT),
    );
  }
  ksort($sessions);
  dpm($sessions);
  return $sessions;
}