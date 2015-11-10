<?php
/**
 * @file
 * Code for the Productivity time tracking feature.
 */

/**
 * Menu callback; display tracking table for issues.
 */
function productivity_time_tracking_issue_table($project_nid) {
  $project_name = 'Foo';

  // Get list of issues for a specific project.
  $query = new EntityFieldQuery();
  $result = $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'github_issue')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->fieldCondition('field_project', 'target_id', $project_nid)
    ->fieldCondition('field_github_content_type', 'value', 'issue')
    ->execute();

  if (empty($result['node'])) {
    return t('No issues found for project @project.', array('@project' => $project_name));
  }

  $issues_nids = array_keys($result['node']);

  $query = db_select('node', 'n');
  $query->rightJoin('field_data_field_github_content_type', 'ct', 'ct.entity_id = n.nid');
  $query->rightJoin('field_data_field_issue_reference', 'ir', 'ir.entity_id = n.nid');

  $result = $query
    ->fields('n', array('title', 'nid'))
    ->condition('type', 'github_issue')
    ->condition('status', NODE_PUBLISHED)
    ->condition('ct.field_github_content_type_value', 'pull_request')
    ->condition('ir.field_issue_reference_target_id', $issues_nids, 'IN')
    ->execute()
    ->fetchAll();


  dpm($result);
  // Get list of pull request IDs related to the issues.


  // Get all tracking data for all the issues.

  $table = array();

  return $table;
}

function productivity_time_display_tracking_issue_table() {
  $form = productivity_time_tracking_issue_table_get_form();


  $project_nid = 9279; // FIXME: get the nid from the form & redirect
  $table = productivity_time_tracking_issue_table($project_nid);

  if (!is_array($table)) {
    // Table returned as a message.
    return $table;
  }

  $return = "";
//  $return .= theme('form', $form);
  $return .= theme('table', $table);

  return $return;
}


/**
 * Build form for the per-issue tracking table.
 * @return array
 */
function productivity_time_tracking_issue_table_get_form() {
  $form = array();

  // Selection box for projects.
  $query = db_select('node', 'n');
  $result = $query
    ->fields('n', array('title', 'nid'))
    ->condition('type', 'project')
    ->condition('status', NODE_PUBLISHED)
    ->execute()
    ->fetchAll();

  if (empty($result)) {
    return t('No projects found in the database');
  }

  // TODO
  $projects = array();
  foreach($result as $project) {
    $projects[$project->nid] = $project->title;
  }

  return $form;
}
