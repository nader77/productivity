<?php
/**
 * @file
 * productivity_timewatch.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function productivity_timewatch_user_default_roles() {
  $roles = array();

  // Exported role: timewatch.
  $roles['timewatch'] = array(
    'name' => 'timewatch',
    'weight' => 10,
  );

  return $roles;
}
