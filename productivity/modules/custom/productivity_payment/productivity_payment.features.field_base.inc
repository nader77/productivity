<?php
/**
 * @file
 * productivity_payment.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function productivity_payment_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_amount'.
  $field_bases['field_amount'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_amount',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'money',
    'settings' => array(
      'max' => 99999999.99,
      'min' => -99999999.99,
      'precision' => 10,
      'scale' => 2,
    ),
    'translatable' => 0,
    'type' => 'money',
  );

  // Exported field_base: 'field_date_actual'.
  $field_bases['field_date_actual'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_date_actual',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'date',
    'settings' => array(
      'cache_count' => 4,
      'cache_enabled' => 0,
      'granularity' => array(
        'day' => 'day',
        'hour' => 0,
        'minute' => 0,
        'month' => 'month',
        'second' => 0,
        'year' => 'year',
      ),
      'timezone_db' => '',
      'todate' => '',
      'tz_handling' => 'none',
    ),
    'translatable' => 0,
    'type' => 'datetime',
  );

  // Exported field_base: 'field_date_expected'.
  $field_bases['field_date_expected'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_date_expected',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'date',
    'settings' => array(
      'cache_count' => 4,
      'cache_enabled' => 0,
      'granularity' => array(
        'day' => 'day',
        'hour' => 0,
        'minute' => 0,
        'month' => 'month',
        'second' => 0,
        'year' => 'year',
      ),
      'timezone_db' => '',
      'todate' => '',
      'tz_handling' => 'none',
    ),
    'translatable' => 0,
    'type' => 'datetime',
  );

  return $field_bases;
}
