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
$i = 0;
$base_query = new EntityFieldQuery();
$base_query
  ->entityCondition('entity_type', 'node')
  ->propertyCondition('type', 'project')
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
    try {
      // Code here.
      $node->field_table_rate['und']['field_days']['und']['0']['value'] = $wrapper->field_days->value();
      $node->field_table_rate['und']['field_hours']['und']['0']['value'] = $wrapper->field_hours->value();
      $node->field_table_rate['und']['field_issue_type']['und']['0']['value'] = '';
      $node->field_table_rate['und']['field_scope']['und']['0']['interval'] = $wrapper->field_scope->value();
      $node->field_table_rate['und']['field_type_rate']['und']['0']['amount'] = $wrapper->field_rate->value();

      node_save($node);
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
  if (round(memory_get_usage()/1048576) >= $memory_limit) {
    $params = array(
      '@memory' => round(memory_get_usage()/1048576),
      '@max_memory' => memory_get_usage(TRUE)/1048576,
    );
    drush_log(dt('Stopped before out of memory. Start process from the node ID @nid', array('@nid' => end($ids))), 'error');
    return;
  }
}