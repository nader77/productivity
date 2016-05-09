<?php
/**
 * @file
 * productivity_user.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function productivity_user_taxonomy_default_vocabularies() {
  return array(
    'stakeholders_roles' => array(
      'name' => 'Stakeholders Roles',
      'machine_name' => 'stakeholders_roles',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
