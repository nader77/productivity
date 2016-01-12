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
  global $base_url;
  // Add JavaScript file with the base url of the page.
  drupal_add_js(drupal_get_path('module', 'productivity_project') . '/plugins/content_types/monthly-report/monthly_report.js');
  drupal_add_js(array('monthly_report' => array('base_url' => $base_url)), 'setting');
  drupal_add_css(drupal_get_path('module', 'productivity_project') . '/plugins/content_types/monthly-report/monthly_report.css');
  drupal_add_css("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/css/select2.min.css", array('type' => 'external'));
  drupal_add_css('https://fonts.googleapis.com/css?family=Abril+Fatface', array('type' => 'external'));
  drupal_add_js("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/js/select2.min.js", array('type' => 'external'));

  $project_id = $args[0];
  $year = $args[1];
  $month = $args[2];

  $variables = array();
  // Get the project title for the page title.
  $variables['project_title'] = $context->title;
  $nodes = get_project_github_issues_query($project_id, $year, $month);
  $table = _productivity_project_create_issues_table($nodes);
  $issues_table = $table[0];
  $project_url = "https://github.com/" . $table[1] . "/pull/";;

  $variables['theme_path'] = base_path() . drupal_get_path('theme', 'bootstrap_subtheme');
  $variables['current_project_id'] = $project_id;

  // Get all the projects for project input
  $variables['projects'] = productivity_project_get_all_projects();

  // Create tables for the template.
  $variables['tables'] = array();
  $variables['total_types'] = array();
  $header = array('Issue', 'Label', 'Date', 'Time', 'Amount');
  foreach($issues_table as $table_name => $table) {
    $variables['table_titles'][] = $table_name;
    $variables['total_per_types'][$table_name] = 0;

    foreach($table as $index => $issue) {
      $rows[$index]['label'] = '<a href="' . $project_url . $issue['issue_num'][0] . '">'. $issue['issue_num'][0] . '</a>';
      $rows[$index]['gitHub_issue_num'] = $issue['label'][0];
      $rows[$index]['date'] = $issue['date'][0];
      $rows[$index]['time'] = $issue['time'][0];
      $rows[$index]['amount'] = $issue['issue_amount'][0] . ' ' . $issue['issue_currency'][0];
      $variables['total_per_types'][$table_name] += $issue['issue_amount'][0];
      $variables['total_currency_per_types'][$table_name] = $issue['issue_currency'][0];
    }
    $variables['tables'][] = theme('table', array('header' => $header, 'rows' => $rows));
    $rows = array();
  }

  $block = new stdClass();
  $block->module = 'productivity_project';
  $block->content = theme('productivity_monthly_report', $variables);

  return $block;
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
function _productivity_project_create_issues_table($nodes) {
  $issues_table = array();
  foreach($nodes as $node) {
    $wrapper = entity_metadata_wrapper('node', $node);
    $project_wrapper = $wrapper->field_project->value();
    $date = date('Y/m/d', $wrapper->field_work_date->value());

    // Loop through all the issues in that day.
    $issues = $wrapper->field_issues_logs->raw();
    foreach($wrapper->field_issues_logs as $issue_log_wrapper) {
      // Check if there is already a table with that type.
      $type = $issue_log_wrapper->field_issue_type->value();
      if(empty($issues_table[$type])) {
        $issues_table[$type] = array();
      }
      // Check if the time spent on the issue is not 0.
      if(intval($issue_log_wrapper->field_time_spent->value())) {
        // push the issue details to the type table.
        $scope_amount = get_the_scope_amount($project_wrapper->vid, $type);
        $table_legnth = count($issues_table[$type]);

        $issues_table[$type][$table_legnth]['issue_num'][] = $issue_log_wrapper->field_github_issue->raw();
        $issues_table[$type][$table_legnth]['label'][] = $issue_log_wrapper->field_issue_label->value();
        $issues_table[$type][$table_legnth]['date'][] = $date;
        $issues_table[$type][$table_legnth]['time'][] = $issue_log_wrapper->field_time_spent->value();
        $issues_table[$type][$table_legnth]['issue_amount'][] = $issue_log_wrapper->field_time_spent->value() * $scope_amount['field_table_rate_field_type_rate_amount'];
        $issues_table[$type][$table_legnth]['issue_currency'][] = $scope_amount['field_table_rate_field_type_rate_currency'];
      }
    }
  }
  return array($issues_table,  $project_wrapper->field_github_repository_name[LANGUAGE_NONE][0]['value']);
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

  $theme['productivity_monthly_report_pdf'] = array(
    'variables' => array(
      'image_path' => NULL,
    ),
    'path' => $plugin['path'],
    'template' => 'monthly_report_pdf',
  );
}

