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

drush_print('Item to process:' . $count);

while ($i < $count) {
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
      // Update scope hours from global hours
      $node->field_table_rate[LANGUAGE_NONE][0]['field_hours'][LANGUAGE_NONE][0]['value'] = number_format($wrapper->field_hours->value(), 2);
      // Update scope type to be hard coded dev
      $node->field_table_rate[LANGUAGE_NONE][0]['field_issue_type'][LANGUAGE_NONE][0]['value'] = 'dev';
      // Update scope interval from global scope interval
      $node->field_table_rate[LANGUAGE_NONE][0]['field_scope'][LANGUAGE_NONE][0]['interval'] = floatval(str_replace(',', '', $wrapper->field_scope->value()['interval']));
      // Update scope period from global scope period
      $node->field_table_rate[LANGUAGE_NONE][0]['field_scope'][LANGUAGE_NONE][0]['period'] = $wrapper->field_scope->value()['period'];
      // Update scope rate amount from global rate amount
      $node->field_table_rate[LANGUAGE_NONE][0]['field_rate'][LANGUAGE_NONE][0]['amount'] = floatval(str_replace(',', '', $wrapper->field_rate->value()['amount']));
      // Update scope rate currency from global rate currency
      $currency = $wrapper->field_rate->value()['currency'] ? $wrapper->field_rate->value()['currency'] : 'USD';
      $node->field_table_rate[LANGUAGE_NONE][0]['field_rate'][LANGUAGE_NONE][0]['currency'] = $currency;
      // Rate type. (hours/month/global)
      $node->field_table_rate[LANGUAGE_NONE][0]['field_rate_type'][LANGUAGE_NONE][0]['value'] = $wrapper->field_rate_type->value();

      node_save($node);
      drush_print('Save node:' . $node->nid);
    }
    catch (Exception $e) {
      $params = array(
        '@error' => $e->getMessage(),
        '@nid' => $node->nid,
        '@title' => $node->title,
        '@value' => $description,
      );
      drush_print(format_string('There was error updating the node(@nid) @title with the value @value. More info: @error', $params), 'error');
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
    drush_print(dt('Stopped before out of memory. Start process from the node ID @nid', array('@nid' => end($ids))), 'error');
    return;
  }
}