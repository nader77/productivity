<?php
/**
 * @file
 * Code for the Productivity time tracking feature.
 */

/**
 * Menu callback; display tracking table for issues.
 */
function productivity_github_time_tracking_issue_table($project_nid) {
  $table = array(
    'header' => array(
      t('Issue ID'),
      t('Issue name'),
      t('Time estimate'),
      t('Actual time'),
      t('Completed'),
    ),
    'data' => array(),
  );

  $project_wrapper = entity_metadata_wrapper('node', $project_nid);

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
    return t('No issues found for project @project.', array('@project' => $project_wrapper->label()));
  }

  $issue_nids = array_keys($result['node']);
  $issue_nodes = node_load_multiple($issue_nids);

  // Prepare table for tracking data.
  foreach($issue_nodes as $node_id => $node) {
    $wrapper = entity_metadata_wrapper('node', $node);
    $table['rows'][$node_id] = array(
      'class' => 'row-ok',
      'data' => array(
        // Issue ID.
        $wrapper->field_issue_id->value(),
        // Issue name,
        $wrapper->label(),
        // Time estimate.
        $wrapper->field_time_estimate->value(),
        // Actual time.
        'N/A',
        // Completed.
        'N/A',
      ),
    );
  }


  // Get list of pull request IDs related to the issues.
  $query = db_select('node', 'n');
  $query->rightJoin('field_data_field_github_content_type', 'ct', 'ct.entity_id = n.nid');
  $query->rightJoin('field_data_field_issue_reference', 'ir', 'ir.entity_id = n.nid');

  $result = $query
    ->fields('n', array('title', 'nid'))
    ->fields('ir', array('field_issue_reference_target_id'))
    ->condition('type', 'github_issue')
    ->condition('status', NODE_PUBLISHED)
    ->condition('ct.field_github_content_type_value', 'pull_request')
    ->condition('ir.field_issue_reference_target_id', $issue_nids, 'IN')
    ->execute()
    ->fetchAllAssoc('nid');


  if (empty($result)) {
    // The Github issues have no pull requests attached to them.
    return $table;
  }

  $pull_requests = array();
  foreach($result as $pull_request) {
    $pull_requests[$pull_request->nid] = array(
      'title' => $pull_request->title,
      'parent_issue' => $pull_request->field_issue_reference_target_id,
    );
  }

  // Tracking could point to issues as well as pull requests.
  $possible_tracking_node_ids_references = array_keys($pull_requests) + $issue_nids;

  // Get all tracking data for all the pull requests.
  $query = db_select('field_data_field_issues_logs', 'il');
  $result = $query
    ->fields('il', array('field_issues_logs_field_github_issue_target_id', 'field_issues_logs_field_time_spent_value'))
    ->condition('entity_type', 'node')
    ->condition('bundle', 'time_tracking')
    ->condition('field_issues_logs_field_github_issue_target_id', $possible_tracking_node_ids_references, 'IN')
    ->execute()
    ->fetchAll();


  if (empty($result)) {
    // No tracking data to process.
    return $table;
  }

  dpm($pull_requests);
  dpm($result);
  dpm($table['rows']);

  $unaccounted_row = array(
    '-',
    t('Unaccounted'),
  );

  foreach($result as $row) {
    // Figure out if this points at an issue, pull request, or at nothing at all.
  }

  return $table;
}

function productivity_github_time_display_tracking_issue_table() {
  $form = productivity_time_tracking_issue_table_get_form();


  $project_nid = 9279; // FIXME: get the nid from the form & redirect

  $table = array();
  if ($project_nid) {
    $table = productivity_github_time_tracking_issue_table($project_nid);
  }

  if (!is_array($table)) {
    // Table returned an error message.
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
