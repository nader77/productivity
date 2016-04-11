<?php
/**
 * @file
 * productivity_account.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function productivity_account_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function productivity_account_node_info() {
  $items = array(
    'account' => array(
      'name' => t('Account'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
