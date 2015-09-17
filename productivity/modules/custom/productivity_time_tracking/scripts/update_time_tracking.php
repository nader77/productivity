<?php
/**
 * @file
 * Triggering the process of updating the time tracking entities from the free
 * description to issues per PR format.
 */
// Get the last node id.
$nid = drush_get_option('nid', 0);
// Get the number of nodes to be processed.
$batch = drush_get_option('batch', 50);
// Get allowed memory limit.
$memory_limit = drush_get_option('memory_limit', 500);
// Get if to enable the multifield module and revert time tracking features.
$enable_multifield = drush_get_option('enable_module', FALSE);

// Avoid sending emails to the managers email about updated hours.
variable_set('site_mail', 'test@test.com');

$i = 0;

if ($enable_multifield) {
  // Enable multifield module.
  module_enable(array('multifield'));

  // Create the issues fields.
  $revert = array(
    'productivity_time_tracking' => array(
      'field_base',
      'field_instance',
    )
  );
  features_revert($revert);
  drush_log('Module multifield has been enabled and feature has been reverted.', 'success');
}

$base_query = new EntityFieldQuery();
$base_query
  ->entityCondition('entity_type', 'node')
  ->propertyCondition('type', 'time_tracking')
  ->propertyCondition('status', NODE_PUBLISHED)
  ->propertyOrderBy('nid', 'ASC')
  ->addTag('field_description')
  ->addTag('DANGEROUS_ACCESS_CHECK_OPT_OUT');
if ($nid) {
  $base_query->propertyCondition('nid', $nid, '>');
}

$query_count = clone $base_query;
$count = $query_count->count()->execute();

if (!$count) {
  drush_log('All time tracking has been converted.', 'success');
  return;
}

while ($i < $count) {
// Free up memory.
  drupal_static_reset();
  $query = clone $base_query;
  if ($nid) {
    $query
      ->propertyCondition('nid', $nid, '>');
  }
  $result = $query
    ->range(0, $batch)
    ->execute();
  if (empty($result['node'])) {
    return;
  }
  $ids = array_keys($result['node']);
  $nodes = node_load_multiple($ids);

  foreach ($nodes as $node) {
    $wrapper = entity_metadata_wrapper('node', $node);
    $description = $wrapper->field_description->value();
    // Explode to issues by "End of line" delimiter, Only when there's description
    // in the time tracking entity.
    $issues = $description != '' ? explode(PHP_EOL, $description) : array();

    $project_id = $wrapper->field_project->getIdentifier();

    // Get the GitHub issue entity for each line in the description, provided we
    // can extract the issue number from the description.
    $issues = $project_id && !empty($issues) ? productivity_time_tracking_get_git_hub_entities_from_description($issues, $project_id) : $issues;

    try {
      $field_issues = array();
      if (!empty($issues)) {
        foreach ($issues as $key => $issue) {
          $field_issues[$key] = array();
          // Add GitHub issue ID only if it exists.
          if (is_array($issue)) {
            $field_issues[$key]['field_github_issue'] = array(
              LANGUAGE_NONE => array(
                array(
                  'target_id' => isset($issue['issue_id']) ? $issue['issue_id'] : FALSE
                )
              )
            );
          }

          // Cannot use the `wrapper` on the sub-fields of a multi-field.
          // Add label, type and hours to each issue, since we don't have all this
          // information, we set all issues to development and time spent to 0.
          $field_issues[$key] += array(
            'field_issue_label' => array(LANGUAGE_NONE => array(array('value' => isset($issue['label']) ? $issue['label'] : $issue))),
            'field_issue_type' => array(LANGUAGE_NONE => array(array('value' => 'dev'))),
            'field_time_spent' => array(LANGUAGE_NONE => array(array('value' => 0))),
          );
        }

        $wrapper->field_issues_logs->set($field_issues);
        $wrapper->save();
      }
    } catch (Exception $e) {
      $params = array(
        '@error' => $e->getMessage(),
        '@nid' => $node->nid,
        '@title' => $node->title,
        '@value' => $description,
      );
      drush_log(format_string('There was error updating the node(@nid) @title with the value @value. More info: @error', $params), 'error');
    }
  }

  $i += count($nodes);
  $nid = end($ids);
  $params = array(
    '@start' => reset($ids),
    '@end' => end($ids),
    '@iterator' => $i,
    '@max' => $count,
  );
  drush_print(dt('Process entities from id @start to id @end. Batch state: @iterator/@max', $params));

  // Restore managers email to the site mail.
  variable_set('site_mail', 'info@gizra.com');

  if (round(memory_get_usage()/1048576) >= $memory_limit) {
    $params = array(
      '@memory' => round(memory_get_usage()/1048576),
      '@max_memory' => memory_get_usage(TRUE)/1048576,
    );
    drush_log(dt('Stopped before out of memory. Start process from the node ID @nid', array('@nid' => end($ids))), 'error');
    return;
  }
}

/**
 * Implements hook_query_TAG_alter()
 *
 * Limits resultset to those time tracks that do have a description.
 */
function productivity_time_tracking_query_field_description_alter(QueryAlterableInterface $query) {
  $query->leftJoin('field_data_field_description', 'field_data_field_description', '(node.nid = field_data_field_description.entity_id AND field_data_field_description.entity_type = \'node\')');
  $query->isNotNull('field_data_field_description.field_description_value');
}

/**
 * Helper function; Gets the GitHub entities by the issue number.
 *
 * Old issues has only description which has the issue number, we take this
 * number and search for a git hub entity with the same number in the
 * "Issue ID" field
 *
 * @param Array $issues_array
 *
 * @param int $project_id
 *
 * @return array
 *  The updated issues array, Only if there's issues otherwise return the same
 *  array that was sent to the function.
 */
function productivity_time_tracking_get_git_hub_entities_from_description($issues_array, $project_id) {
  $issues = array();
  foreach ($issues_array as $key => $issue) {
    preg_match('/(#\w+)/', $issue, $matches);
    $hashtag = str_replace('#', '', $matches[0]);
    $issue_number = is_numeric(intval($hashtag)) ? intval($hashtag) : 0;
    $issue_label = str_replace($matches[0], '', $issue);

    $query = new EntityFieldQuery();
    $results = $query
      ->entityCondition('entity_type', 'node')
      ->propertyCondition('type', 'github_issue')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->fieldCondition('field_issue_id', 'value', $issue_number)
      ->fieldCondition('field_project', 'target_id', $project_id)
      ->range(0, 1)
      ->execute();

    $github_issue_entity_id = !empty($results['node']) ? array_shift(array_keys($results['node'])) : 0;

    $issues[] = array(
      'issue_id' => $github_issue_entity_id,
      'label' => $issue_label,
    );
  }

  // Return the same issues array if there's no github issues.
  if (!empty($issues)) {
    return $issues;
  }
  else {
    return $issues_array;
  }
}
