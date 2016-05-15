<?php
/**
 * @file
 * productivity_timewatch.multifield.inc
 */

/**
 * Implements hook_multifield_default_multifield().
 */
function productivity_timewatch_multifield_default_multifield() {
  $export = array();

  $multifield = new stdClass();
  $multifield->disabled = FALSE; /* Edit this to true to make a default multifield disabled initially */
  $multifield->api_version = 1;
  $multifield->machine_name = 'field_issues_logs';
  $multifield->label = 'field_issues_logs';
  $multifield->description = '';
  $export['field_issues_logs'] = $multifield;

  return $export;
}
