<?php
/**
 * @file
 * Triggering the process of updating the time tracking entities to update the
 * spent time in the issues in case the total hours does not match.
 */
// Get the last node id.
$nid = drush_get_option('nid', 0);
// Get the number of nodes to be processed.
$batch = drush_get_option('batch', 50);
// Get allowed memory limit.
$memory_limit = drush_get_option('memory_limit', 500);

// Avoid sending emails to the managers email about updated hours.
variable_set('site_mail', 'test@test.com');

$i = 0;

$base_query = new EntityFieldQuery();
$base_query
  ->entityCondition('entity_type', 'node')
  ->propertyCondition('type', 'time_tracking')
  ->propertyCondition('status', NODE_PUBLISHED)
  ->propertyOrderBy('nid', 'ASC')
  ->addTag('DANGEROUS_ACCESS_CHECK_OPT_OUT');

if ($nid) {
  $base_query->propertyCondition('nid', $nid, '>');
}

$query_count = clone $base_query;
$count = $query_count->count()->execute();

if (!$count) {
  drush_log('All time tracking hours has been fixed.', 'success');
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
    $issues = $wrapper->field_issues_logs->value();
    $hours_in_issues = 0;
    $total_hours = $wrapper->field_track_hours->value();

    foreach ($issues as $issue) {
      $hours_in_issues += $issue->field_time_spent[LANGUAGE_NONE][0]['value'];
    }

    try {
      if (!$hours_in_issues && $total_hours > 0) {
        // Add the "time tracking" total hours to the first issue if the total
        // of issues' spent time is 0 and the hours in the time tracking is more
        // than that, not using 'wrapper' because we can't set one specific
        // value of a sub field with 'wrapper'.
        $node->field_issues_logs[LANGUAGE_NONE][0]['field_time_spent'][LANGUAGE_NONE][0]['value'] = $total_hours;
        node_save($node);
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
