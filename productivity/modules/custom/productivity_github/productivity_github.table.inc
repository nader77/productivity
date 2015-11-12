<?php
/**
 * @file
 * Code for the Productivity time tracking feature.
 */
define('PRODUCTIVITY_GITHUB_ISSUE_OPEN_STATUS', t('WIP'));
define('PRODUCTIVITY_GITHUB_ISSUE_CLOSED_STATUS', t('Done'));


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
      t('Overtime'),
      t('Status'),
    ),
    'data' => array(),
    'attributes' => array('class' => array('per-issue-table')),
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
      'class' => '',
      'data' => array(
        'issue_id' => $wrapper->field_issue_id->value(),
        'issue_name' => $wrapper->label(),
        'estimate' => intval($wrapper->field_time_estimate->value()),
        'actual' => 0,
        'overtime' => 0,
        // TODO: Followup - closing/opening issue should change this.
        'status' => 'WIP',
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

  $total_row = array(
    'data' => array(
      'name' => array('data' => t('Total'), 'colspan' => 2),
      'total_estimate' => 0,
      'total_actual' => 0,
      'total_overtime' => 0,
      'status' => '',
    ),
  );

  foreach($result as $row) {
    // Figure out if this points at an issue, pull request, or at nothing at all.
    $target_id = $row->field_issues_logs_field_github_issue_target_id;
    $time_spent = $row->field_issues_logs_field_time_spent_value;

    if (!empty($table['rows'][$target_id])) {
      // This tracking points directly at an issue.
      $relevant_row = &$table['rows'][$target_id];
      $relevant_row['data']['actual'] += $time_spent;
    }
    elseif (!empty($pull_requests[$target_id]) && !empty($table['rows'][$pull_requests[$target_id]['parent_issue']])) {
      // This is a pull request pointing at an issue.
      $relevant_row = &$table['rows'][$pull_requests[$target_id]['parent_issue']];
      $relevant_row['data']['actual'] += $time_spent;
    }

    // Row becomes irrelevant in the next loop run.
    unset($relevant_row);
  }

  // Final calculations.
  $side = 'odd';
  foreach($table['rows'] as &$row) {
    $data = &$row['data'];
    $side = ($side == 'odd') ? 'even' : 'odd';

    // Total row.
    $total_row['data']['total_estimate'] += $data['estimate'];
    $total_row['data']['total_actual'] += $data['actual'];

    // Calculate overtime.
    $data['overtime'] = $data['actual'] - $data['estimate'];
    $total_row['data']['total_overtime'] += $data['overtime'];

    // Add class.
    $row['class'] = ($data['actual'] > $data['estimate'] ? 'row-bad-' : 'row-ok-') . $side;
  }

  // Total row. Includes non-referenced issues.
  $total_row['class'] = 'row-total-' . $side;
  $table['rows'][] = $total_row;

  return $table;
}

function productivity_github_time_display_tracking_issue_table($project_node_id = 0) {
  if (!$project_node_id) {

    return theme('item_list', array('items' => productivity_time_tracking_issue_table_get_list()));
  }

  $node = node_load($project_node_id);
  drupal_set_title(t('@project issue tracking table', array('@project' => $node->title)));

  $table = productivity_github_time_tracking_issue_table($project_node_id);
  if (!is_array($table)) {
    // Table returned an error message.
    return $table;
  }

  // Add a link to go to the project selection.
  $go_back_link = '<div class="back-link">' . l(t('Back to project list'), 'tracking/per-issue') . '</div>';

  return  $go_back_link . theme('table', $table);
}


/**
 * Build form for the per-issue tracking table.
 * @return array
 */
function productivity_time_tracking_issue_table_get_list() {
  // List of links for projects.
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
    $projects[strtolower($project->title)] = l($project->title, 'tracking/per-issue/' . $project->nid);
  }
  ksort($projects);

  return $projects;
}
