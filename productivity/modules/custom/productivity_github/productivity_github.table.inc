<?php
/**
 * @file
 * Code for the Productivity time tracking feature.
 */

/**
 * Menu callback; display tracking table for issues.
 */
function productivity_time_tracking_issue_table() {
  // Selection box for projects.
  $form = array();

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

  $projects = array();
  foreach($result as $project) {
    $projects[$project['nid']] = $project['title'];
  }

  $project_nid = 9279; // FIXME
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

  if (empty($result)) {
    return t('No issues found for project @project.', array('@project' => $project_name));
  }


  $table = array();

  return "foo";
}

