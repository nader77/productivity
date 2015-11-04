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

// Revert the features.
features_revert(array('productivity_github'));

$i = 0;

$base_query = new EntityFieldQuery();
$base_query
  ->entityCondition('entity_type', 'node')
  ->propertyCondition('type', 'github_issue')
  ->propertyCondition('status', NODE_PUBLISHED)
  ->propertyOrderBy('nid', 'ASC')
  ->addTag('DANGEROUS_ACCESS_CHECK_OPT_OUT');

if ($nid) {
  $base_query->propertyCondition('nid', $nid, '>');
}

$query_count = clone $base_query;
$count = $query_count->count()->execute();

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
    $work_date = $wrapper->field_work_date->value();

    try {
      $wrapper->field_push_date->set(array($work_date));
      $wrapper->save();

    } catch (Exception $e) {
      $params = array(
        '@error' => $e->getMessage(),
        '@nid' => $node->nid,
        '@title' => $node->title,
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


  if (round(memory_get_usage()/1048576) >= $memory_limit) {
    $params = array(
      '@memory' => round(memory_get_usage()/1048576),
      '@max_memory' => memory_get_usage(TRUE)/1048576,
    );
    drush_log(dt('Stopped before out of memory. Start process from the node ID @nid', array('@nid' => end($ids))), 'error');
    return;
  }
}
