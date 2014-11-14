<?php
/**
 * @file
 * Skeleton_Title profile.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
function skeleton_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];

  // Disable the update module by default.
  // It slows down accessing the administration back-end.
  $form['update_notifications']['update_status_module']['#default_value'] = array(
    0 => 0,
    1 => 2,
  );
}

/**
 * Implements hook_install_tasks().
 */
function skeleton_install_tasks() {
  $tasks = array();

  $tasks['skeleton_setup_blocks'] = array(
    'display_name' => st('Setup Blocks'),
    'display' => FALSE,
  );

  // Run this as the last task!
  $tasks['skeleton_setup_rebuild_permissions'] = array(
    'display_name' => st('Rebuild permissions'),
    'display' => FALSE,
  );

  $tasks['skeleton_setup_set_variables'] = array(
    'display_name' => st('Set Variables'),
    'display' => FALSE,
  );


  return $tasks;
}

/**
 * Task callback; Setup blocks.
 */
function skeleton_setup_blocks() {
  $default_theme = variable_get('theme_default', 'bartik');

  $blocks = array(
    array(
      'module' => 'system',
      'delta' => 'user-menu',
      'theme' => $default_theme,
      'status' => 1,
      'weight' => 0,
      'region' => 'header',
      'pages' => '',
      'title' => '<none>',
      'cache' => DRUPAL_NO_CACHE,
    ),
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
function skeleton_setup_rebuild_permissions() {
  node_access_rebuild();
}


/**
 * Task callback; Set variables.
 */
function skeleton_setup_set_variables() {
  // Customer specific info.
  //  variable_set('circuit_customer_name', 'demo_site');
  //  variable_set('circuit_customer_theme', 'bootstrap_kedem');

  $theme = variable_get('circuit_customer_theme', 'bootstrap_subtheme');
  $variables = array(
    'jquery_update_jquery_version' => 1.8,
    // Connect to facebook app.
    'github_connect_client_id' => '6e2d1a14e1490746e5c2',
    'github_connect_client_secret' => 'b5da4ca47f9a1e699e16aac046b9bb8777cf15d4',
  );

  foreach ($variables as $key => $value) {
    variable_set($key, $value);
  }
}
