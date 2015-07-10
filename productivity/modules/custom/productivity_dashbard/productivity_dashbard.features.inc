<?php
/**
 * @file
 * productivity_dashbard.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function productivity_dashbard_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}
