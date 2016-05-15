<?php
/**
 * @file
 * productivity_user.multifield.inc
 */

/**
 * Implements hook_multifield_default_multifield().
 */
function productivity_user_multifield_default_multifield() {
  $export = array();

  $multifield = new stdClass();
  $multifield->disabled = FALSE; /* Edit this to true to make a default multifield disabled initially */
  $multifield->api_version = 1;
  $multifield->machine_name = 'field_project_madaan';
  $multifield->label = 'field_project_madaan';
  $multifield->description = '';
  $export['field_project_madaan'] = $multifield;

  return $export;
}
