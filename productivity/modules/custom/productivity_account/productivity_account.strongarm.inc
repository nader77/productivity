<?php
/**
 * @file
 * productivity_account.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function productivity_account_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_account';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_account'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_account';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_account'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_account';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_account'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_account';
  $strongarm->value = '0';
  $export['node_preview_account'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_account';
  $strongarm->value = 1;
  $export['node_submitted_account'] = $strongarm;

  return $export;
}
