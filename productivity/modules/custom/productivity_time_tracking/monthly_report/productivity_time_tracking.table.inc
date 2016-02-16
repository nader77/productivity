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
function productivity_time_tracking_issue_table_callback($project_node, $year, $month) {
  return productivity_time_tracking_issue_table($project_node, $year, $month);
}

/**
 * Render callback;  Bidder page.
 */
function productivity_time_tracking_issue_table($node, $year, $month) {
  global $base_url;
  // Add JavaScript file with the base url of the page.
  drupal_add_js(drupal_get_path('module', 'productivity_time_tracking') . '/monthly-report/monthly_report.js');
  drupal_add_css(drupal_get_path('module', 'productivity_time_tracking') . '/monthly-report/monthly_report.css');
  drupal_add_css("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/css/select2.min.css", array('type' => 'external'));
  drupal_add_css('https://fonts.googleapis.com/css?family=Abril+Fatface', array('type' => 'external'));
  drupal_add_js("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/js/select2.min.js", array('type' => 'external'));

  drupal_add_js(array('monthly_report' => array(
    'base_url' => $base_url,
    'project_id' => $node->nid,
    )
  ), 'setting');

  $wrapper = entity_metadata_wrapper('node', $node);

  $variables = array();
  $variables['project_title'] = $wrapper->label();
  $variables['account'] = $wrapper->field_account->label();

  // TODO: Deal better with project URL.
  $project_url = '';
  if (isset($wrapper->field_github_repository_name)) {
    $first_repo_name = $wrapper->field_github_repository_name[0]->value();
    $project_url = "https://github.com/$first_repo_name";
  }

  $variables['year'] = isset($args[1]) ? $args[1] : date('Y');
  $variables['month']= isset($args[2]) ? $args[2] : date('m', strtotime("-1 month"));

  $nodes = productivity_github_get_project_github_issues_query($node->nid, $variables['year'], $variables['month']);
  $issues_table = array();
  $variables['no_result'] = FALSE;
  $variables['message'] = '';
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
    $variables['table_titles'][] = $table_name;
    $variables['total_per_types'][$table_name] = 0;

    foreach ($table as $index => $issue) {
      $rows[$index]['label'] = l($issue['issue_num'][0], $project_url . $issue['issue_num'][0], array('absolute' => TRUE));
      $rows[$index]['gitHub_issue_num'] = $issue['label'][0];
      $rows[$index]['date'] = $issue['date'][0];
      $rows[$index]['time'] = $issue['time'][0];
      $rows[$index]['amount'] = $issue['issue_amount'][0] . ' ' . $issue['issue_currency'][0];
      $variables['total_per_types'][$table_name] += $issue['issue_amount'][0];
      $variables['total_currency_per_types'][$table_name] = $issue['issue_currency'][0];
      $variables['grand_total'] += $issue['issue_amount'][0];
    }
    $variables['tables'][] = theme('table', array(
      'header' => $header,
      'rows' => $rows
    ));
    $rows = array();
  }

  // Get all the projects for project input
  $variables['projects'] = productivity_project_get_all_projects();
  $variables['current_project_id'] = $node->nid;

  return theme('productivity_monthly_report', $variables);
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
      // Check if the time spent on the issue is not 0.
      if(intval($issue_log_wrapper->field_time_spent->value())) {
        // push the issue details to the type table.
        $rate = productivity_project_get_rate($wrapper->field_project->getIdentifier(), $type);
        /// The table length of every type.
        $table_length = count($issues_table[$type]);

        $issue_id = '#';
        if (isset($issue_log_wrapper->field_github_issue->field_issue_id)) {
          $issue_id = $issue_log_wrapper->field_github_issue->field_issue_id->value();
        }

        $issues_table[$type][$table_length]['issue_num'][] = $issue_id;
        $issues_table[$type][$table_length]['label'][] = $issue_log_wrapper->field_issue_label->value();
        $issues_table[$type][$table_length]['date'][] = $date;
        $issues_table[$type][$table_length]['time'][] = $issue_log_wrapper->field_time_spent->value();
        $issues_table[$type][$table_length]['issue_amount'][] = $issue_log_wrapper->field_time_spent->value() * $rate['amount'];
        $issues_table[$type][$table_length]['issue_currency'][] = $rate['currency'];
      }
    }
  }
  return $issues_table;
}