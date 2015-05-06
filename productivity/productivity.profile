<?php
/**
 * @file
 * Productivity profile.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
function productivity_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];
}

/**
 * Implements hook_install_tasks().
 */
function productivity_install_tasks() {
  $tasks = array();

  $tasks['productivity_setup_blocks'] = array(
    'display_name' => st('Setup Blocks'),
    'display' => FALSE,
  );

  $tasks['productivity_setup_set_variables'] = array(
    'display_name' => st('Set Variables'),
    'display' => FALSE,
  );

  $tasks['productivity_set_permissions'] = array(
    'display_name' => st('Set Permissions'),
    'display' => FALSE,
  );

  $tasks['productivity_set_content_access'] = array(
    'display_name' => st('Set Content Access'),
    'display' => FALSE,
  );

  // Run this as the last task!
  $tasks['productivity_setup_rebuild_permissions'] = array(
    'display_name' => st('Rebuild Permissions'),
    'display' => FALSE,
  );

  return $tasks;
}

/**
 * Task callback; Setting permissions.
 */
function productivity_set_permissions() {
  // Enable default permissions for system roles.
  $permissions = array(
    'create time_tracking content',
    'edit any time_tracking content',
  );

  user_role_grant_permissions(DRUPAL_AUTHENTICATED_RID, $permissions);
}


/**
 * Task callback; Set content permissions.
 */
function productivity_set_content_access() {
  $permissions = array(
    'account' => array(
      'view_own' => array(),
      'view' => array(),
    ),
    'project' => array(
      'view_own' => array(),
      'view' => array(DRUPAL_AUTHENTICATED_RID),
    ),
    'salary' => array(
      'view_own' => array(),
      'view' => array(),
    ),
    'time_tracking' => array(
      'view_own' => array(DRUPAL_AUTHENTICATED_RID),
      'view' => array(DRUPAL_AUTHENTICATED_RID),
    ),
  );

  foreach ($permissions as $type_name => $settings) {
    content_access_set_settings($settings, $type_name);
  }
}


/**
 * Task callback; Setup blocks.
 */
function productivity_setup_blocks() {
  $default_theme = variable_get('theme_default', 'bartik');

  $blocks = array(
//    array(
//      'module' => 'system',
//      'delta' => 'user-menu',
//      'theme' => $default_theme,
//      'status' => 1,
//      'weight' => 0,
//      'region' => 'header',
//      'pages' => '',
//      'title' => '<none>',
//      'cache' => DRUPAL_NO_CACHE,
//    ),
  );

  drupal_static_reset();
  _block_rehash($default_theme);
  foreach ($blocks as $record) {
    $module = array_shift($record);
    $delta = array_shift($record);
    $theme = array_shift($record);
    db_update('block')
      ->fields($record)
      ->condition('module', $module)
      ->condition('delta', $delta)
      ->condition('theme', $theme)
      ->execute();
  }
}

/**
 * Task callback; Rebuild permissions (node access).
 *
 * Setting up the platform triggers the need to rebuild the permissions.
 * We do this here so no manual rebuild is necessary when we finished the
 * installation.
 */
function productivity_setup_rebuild_permissions() {
  node_access_rebuild();
}


/**
 * Task callback; Set variables.
 */
function productivity_setup_set_variables() {
  $variables = array(
    'jquery_update_jquery_version' => 1.8,
    'hours_count_as_day' => 7,
  );

  foreach ($variables as $key => $value) {
    variable_set($key, $value);
  }
}
