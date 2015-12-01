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

  $total_row = array(
    'data' => array(
      'placeholder' => '',
      'name' => array('data' => t('Total')),
      'estimate' => 0,
      'actual' => 0,
      'overtime' => 0,
      'status' => '',
    ),
  );

  // Prepare table for tracking data.
  foreach($issue_nodes as $node_id => $node) {
    $wrapper = entity_metadata_wrapper('node', $node);

    $estimate = floatval($wrapper->field_time_estimate->value());
    $actual = floatval($wrapper->field_actual_hours->value());
    $github_issue_id = $wrapper->field_issue_id->value();
    $project_link =  'http://github.com/' . $wrapper->field_github_project_id->value();

    $issue_row = array(
      'class' => '',
      'data' => array(
        'issue_id' => l($github_issue_id,  $project_link . '/issues/' . $github_issue_id, array('attributes' => array('target' => '_blank'))),
        'issue_name' => $wrapper->label(),
        'estimate' => $estimate,
        'actual' => $actual,
        'overtime' => $actual - $estimate,
        // TODO: Followup - closing/opening issue should change this.
        'status' => 'WIP',
      ),
    );

    // Total row.
    $total_row['data']['estimate'] += $issue_row['data']['estimate'];
    $total_row['data']['actual'] += $issue_row['data']['actual'];
    $total_row['data']['overtime'] += $issue_row['data']['overtime'];

    // Add to the table
    $table['rows'][$node_id] = $issue_row;
  }

  // Add total row.
  array_unshift($table['rows'], $total_row);

  // Final calculations.
  $side = 'odd';
  foreach($table['rows'] as &$row) {
    $data = &$row['data'];
    $side = ($side == 'odd') ? 'even' : 'odd';

    // Add class only to overtime cells.
    $data['overtime'] = array(
      'class' => ($data['actual'] > $data['estimate'] ? 'cell-bad-' : 'cell-ok-') . $side,
      'data' => $data['overtime'],
    );
  }

  return $table;
}

/**
 * Render the time tracking per issue table.
 *
 * @param int $project_node_id
 *   Project to process.
 * @return string
 *   Rendered HTML.
 */
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
