<?php
/**
 * @file
 * productivity_timewatch.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function productivity_timewatch_taxonomy_default_vocabularies() {
  return array(
    'session_types' => array(
      'name' => 'Session types',
      'machine_name' => 'session_types',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
