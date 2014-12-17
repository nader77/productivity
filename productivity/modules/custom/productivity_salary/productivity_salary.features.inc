<?php
/**
 * @file
 * productivity_salary.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function productivity_salary_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function productivity_salary_node_info() {
  $items = array(
    'salary' => array(
      'name' => t('Salary'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
