<?php
/**
 * @file
 * Code for the Productivity time tracking feature.
 */
define('PRODUCTIVITY_GITHUB_ISSUE_OPEN_STATUS', 'WIP');
define('PRODUCTIVITY_GITHUB_ISSUE_CLOSED_STATUS', 'Done');

/**
 * Menu callback; display tracking table for issues.
 */
function productivity_time_tracking_issue_table_callback($node = FALSE, $year = FALSE, $month = FALSE) {
  return productivity_time_tracking_issue_table($node, $year, $month);
}

/**
 * Render callback;  Bidder page.
 */
function productivity_time_tracking_issue_table($node = FALSE, $year = FALSE, $month = FALSE) {
  global $base_url;
  // Add JavaScript file with the base url of the page.
  drupal_add_js(drupal_get_path('module', 'productivity_time_tracking') . '/monthly_report/monthly_report.js');
  drupal_add_css(drupal_get_path('module', 'productivity_time_tracking') . '/monthly_report/monthly_report.css');
  drupal_add_css("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/css/select2.min.css", array('type' => 'external'));
  drupal_add_css('https://fonts.googleapis.com/css?family=Abril+Fatface', array('type' => 'external'));
  drupal_add_js("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/js/select2.min.js", array('type' => 'external'));

  // Add datepicker lib.
  drupal_add_js("https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.6.0/js/bootstrap-datepicker.min.js", array('type' => 'external'));
  drupal_add_css("https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.6.0/css/bootstrap-datepicker.min.css", array('type' => 'external'));

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


  $variables['projects'] = productivity_project_get_all_projects();
  $variables['current_project_id'] = 0;
  $variables['project_title'] = 'Select a project';
  $variables['account'] = '';
  $variables['no_result'] = FALSE;
  $variables['message'] = '';

  drupal_add_js(array('monthly_report' => array(
    'base_url' => $base_url,
    'year' => $variables['year'],
    'month' => $variables['month'],
    )
  ), 'setting');

  // No project given.
  if (!$node) {
    return theme('productivity_time_tracking_monthly_report', $variables);
  }

  drupal_add_js(array('monthly_report' => array(
    'project_id' => $node->nid,
    )
  ), 'setting');

  $wrapper = entity_metadata_wrapper('node', $node);

  $variables['project_title'] = $wrapper->label();
  $variables['account'] = $wrapper->field_account->label();

  $nodes = productivity_github_get_project_github_issues_query($node->nid, $variables['year'], $variables['month']);
  $issues_table = array();

  // Get all issues for the project.
  if ($nodes) {
    $issues_table = productivity_time_tracking_create_issues_table($nodes);
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
  $header = array('Issue', 'Label', 'Date', 'Time', 'Amount');
  foreach ($issues_table as $table_name => $table) {
    $variables['table_titles'][$table_name] = _productivity_time_tracking_get_table_title($table_name, $node, $table['label']);
    $variables['total_per_types'][$table_name] = 0;
    $variables['total_per_hours_types'][$table_name] = 0;

    foreach ($table['issues'] as $index => $issue) {
      $rows[$index]['label'] = $issue['issue_num'] == '#' ? 'N/A' : l($issue['issue_num'], $issue['gh_url'], array(
        'absolute' => TRUE,
        'attributes' => array('target' => '_blank'),
      ));
      $rows[$index]['gitHub_issue_num'] = l($issue['label'], 'node/' . $issue['nid'] . '/edit', array('attributes' => array('target' => '_blank')));
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
  $variables['current_project_id'] = $node->nid;

  $variables['table'] = theme('productivity_time_tracking_monthly_report_table', $variables);

  return theme('productivity_time_tracking_monthly_report', $variables);
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
function productivity_time_tracking_create_issues_table($nodes) {
  $issues_table = array();
  foreach($nodes as $node) {
    $wrapper = entity_metadata_wrapper('node', $node);
    $date = date('Y/m/d', $wrapper->field_work_date->value());

    // Loop through all the issues in that day.
    foreach($wrapper->field_issues_logs as $issue_log_wrapper) {
      // Check if there is already a table with that type.
      $type = $issue_log_wrapper->field_issue_type->value();
      if(empty($issues_table[$type])) {
        $issues_table[$type] = array();
      }
      // push the issue details to the type table.
      $rate = productivity_project_get_rate($wrapper->field_project->getIdentifier(), $type);
      /// The table length of every type.
      $issue_id = '#';
      $gh_id = '';
      if (isset($issue_log_wrapper->field_github_issue->field_issue_id)) {
        $issue_id = $issue_log_wrapper->field_github_issue->field_issue_id->value();
        $gh_id = $issue_log_wrapper->field_github_issue->field_github_project_id->value();
      }

      $issues_table[$type]['label'] = $issue_log_wrapper->field_issue_type->label();
      $issues_table[$type]['issues'][] = array(
        'nid' =>  $node->nid,
        'issue_num' => $issue_id,
        'gh_url' => 'https://github.com/' . $gh_id . '/issues/' . $issue_id,
        'label' => $issue_log_wrapper->field_issue_label->value(),
        'date' => $date,
        'time' => $issue_log_wrapper->field_time_spent->value(),
        'issue_amount' => $issue_log_wrapper->field_time_spent->value() * $rate['amount'],
        'issue_currency' => $rate['currency']
      );
    }
  }
  return $issues_table;
}

/**
 * Check for a project override to the table title.
 * These are set in the project's node field_work_type.
 * Function designed to run once per page load (can be optimized
 * if all the overrides are needed).
 *
 * @param $table_machine_name
 * @param $node
 * @param string $default_name
 * @return string
 */
function _productivity_time_tracking_get_table_title($table_machine_name, $node, $default_name = '') {
  // Find all of the overrides.
  $overrides = array();
  $wrapper = entity_metadata_wrapper('node', $node);
  foreach($wrapper->field_table_rate as $multifield) {
    $machine_name = $multifield->field_issue_type->value();
    $override = $multifield->field_issue_type_label->value();

    $overrides[$machine_name] = $override;
  }

  return empty($overrides[$table_machine_name]) ?  $default_name : $overrides[$table_machine_name];
}
