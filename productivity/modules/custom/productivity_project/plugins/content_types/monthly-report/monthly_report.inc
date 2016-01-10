<?php

/**
 * Plugin definition.
 *
 * Display the Monthly Report.
 */
$plugin = array(
  'title' => t('Monthly Report'),
  'description' => t('Display monthly_report'),
  'category' => t('Productivity'),
  'hook theme' => 'productivity_monthly_report_theme',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Render callback;  Bidder page.
 */
function productivity_project_monthly_report_content_type_render($subtype, $conf, $args, $context) {
  $variables = array();
  $variables['theme_path'] = base_path() . drupal_get_path('theme', 'bootstrap_subtheme');
  $block = new stdClass();
  $block->module = 'productivity_project';

  $variables['project_title'] = $context->title;
  $nodes = github_issues_query($args[0], $args[1], $args[2]);
  $issues_table = create_issues_table($nodes);

  // Create tables for the template.
  $variables['tables'] = array();
  $variables['total_types'] = array();
  $header = array('GitHub Issue Number', 'Label', 'Time', 'Amount');
  foreach($issues_table as $table_name => $table) {
    $variables['table_titles'][] = $table_name;
    $variables['total_types'][$table_name] = 0;

    foreach($table['label'] as $index => $label) {
      $rows[$index]['label'] = $table['issue_num'][$index];
      $rows[$index]['gitHub_issue_num'] = $label;
      $rows[$index]['time'] = $table['time'][$index];
      $rows[$index]['amount'] = $table['issue_amount'][$index] . " USD";
      $variables['total_types'][$table_name] += $table['issue_amount'][$index];
    }
    $variables['tables'][] = theme('table', array('header' => $header, 'rows' => $rows));
  }

  $block->content = theme('productivity_monthly_report', $variables);
  return $block;
}

/**
 *  Create a matrix of all the issues from GitHub nodes.
 *
 * @param $nodes
 *  All the nodes return from the query.
 *
 * @return array
 *  Matrix of all the issues,
 */
function create_issues_table($nodes) {
  $issues_table = array();
  foreach($nodes as $node) {
    $wrapper = entity_metadata_wrapper('node', $node);
    $project_wrapper = $wrapper->field_project->value();

    // Loop through all the issues in that day.
    $issues = $wrapper->field_issues_logs->raw();
    foreach($issues as $issue) {
      // Check if there is already a table with that type.
      $type = $issue['field_issue_type'][LANGUAGE_NONE][0]['value'];
      if(empty($issues_table[$type])) {
        $issues_table[$type] = array();
        $scope_amount = get_the_scope_amount($project_wrapper->field_table_rate[LANGUAGE_NONE], $type);
      }
      // Check if the time spent on the issue not 0.
      if(intval($issue['field_time_spent'][LANGUAGE_NONE][0]['value'])) {
        // push the issue details to the type table.
        $label = $issue['field_issue_label'][LANGUAGE_NONE][0]['value'];
        $issues_table[$type]['issue_num'][] = substr($label, 1, strpos($label, ':') - 1);
        $issues_table[$type]['label'][] = substr($label, strpos($label, ':') + 2, strlen($label));
        $issues_table[$type]['time'][] = $issue['field_time_spent'][LANGUAGE_NONE][0]['value'];
        $issues_table[$type]['issue_amount'][] = $issue['field_time_spent'][LANGUAGE_NONE][0]['value'] * $scope_amount;
      }
    }
  }
  return $issues_table;
}

/**
 * Find the amount of the scope in question.
 *
 * @param $table_rate
 *  The $table_rate scopes.
 * @param $scope_to_find
 *  The string of the scope in question.
 *
 * @return int
 *  return the scope amount or zero.
 *
 */
function get_the_scope_amount($table_rate, $scope_to_find) {
  foreach($table_rate as $scope) {
    $scope_type = $scope['field_issue_type'][LANGUAGE_NONE][0]['value'];
    if($scope_type === $scope_to_find) {
      return $scope['field_type_rate'][LANGUAGE_NONE][0]['amount'];
    }
  }
  return 0;
}

/**
 * Query DB for every GitHub issue linked to the project id from the URL,
 * that in the URL month and year.
 *
 * @param $project_id
 *  The project id number.
 * @param $year
 *  The year to filter the issues.
 * @param $month
 *  The month to filter the issues.
 *
 * @return $node
 *  All the nodes return from the query.
 */
function github_issues_query($project_id, $year, $month) {
  $project_start_month = format_string("@year-@month-01", array('@year' => $year, '@month' => $month));
  $project_end_month = (new DateTime($project_start_month))->format( 'Y-m-t' );

  $project_start_month = (new DateTime(format_string("2015-12-01")))->format( 'Y-m-t' );
  $project_end_month = (new DateTime(format_string("2016-01-20")))->format( 'Y-m-t' );

  $query = new EntityFieldQuery();
  $result = $query
    ->entityCondition('entity_type', 'node')
    ->fieldCondition('field_project', 'target_id', $project_id)
    ->fieldCondition('field_work_date', 'value', $project_start_month, '>=')
    ->fieldCondition('field_work_date', 'value', $project_end_month, '<=')
    ->execute();
  if(empty($result['node'])) {
    return;
  }
  return node_load_multiple(array_keys($result['node']));
}

/**
 * Delegated hook_theme().
 */
function productivity_monthly_report_theme(&$theme, $plugin) {
  $theme['productivity_monthly_report'] = array(
    'variables' => array(
      'project_title' => NULL,
      'table' => NULL,
      'table_titles' => NULL,
    ),
    'path' => $plugin['path'],
    'template' => 'monthly_report',
  );
}
