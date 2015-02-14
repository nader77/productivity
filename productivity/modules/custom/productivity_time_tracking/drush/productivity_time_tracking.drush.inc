<?php

/**
 * Implementation of hook_drush_command().
 */
function productivity_time_tracking_drush_command() {
  $items = array();

  $items['set-track-batch'] = array(
    'description' => "Makes a delicious sandwich.",
    'options' => array(
      'month' => array(
        'description' => 'Month to udpate',
        'example-value' => '1',
      ),
      'employee' => array(
        'description' => 'User to udpate',
        'example-value' => 'noga',
      ),
      'project_nid' => array(
        'description' => 'Project NID to udpate',
        'example-value' => '1',
      ),
      'year' => array(
        'description' => 'Year to udpate',
        'example-value' => '2014',
      ),
    ),
    'examples' => array(
      'drush ttb --month=1  --year=2014 --employee=noga --project_nid=nike1' => 'set all Jan to nike and noga',
    ),
    'aliases' => array('ttb'),
  );

  return $items;
}

/**
 * Example drush command callback. This is where the action takes place.
 */
function drush_productivity_time_tracking_set_track_batch() {

  if (!$month = drush_get_option('month')) {
    drush_print('Missing month use --month');
    return;
  }

  if (!$year = drush_get_option('year')) {
    drush_print('Missing month use --year');
    return;
  }

  if (!$employee = drush_get_option('employee')) {
    drush_print('Missing employee use --employee');
    return;
  }

  if (!$project_nid = drush_get_option('project_nid')) {
    drush_print('Missing project, use --project_nid');
    return;
  }
  $user = drush_get_option('user');
  if (!$user || $user != 1) {
    drush_print('Missing user admin, use --user=1');
    return;
  }
  $globals = productivity_time_tracking_get_global_days($month, $year);
  $last_day_this_month  = date('t', strtotime('1.' . $month . '.' . $year));
  drush_print(print_r($globals));
  // Save all days that are empty.
  for ($i = 1; $i <= $last_day_this_month; $i++) {

    $timestamp = strtotime($i . '.' . $month . '.' . $year);
    $week_day = date( "w", $timestamp);
    // Bypass Friday or Saturday.
    if (in_array($week_day, array(5, 6))) {
      drush_print('Bypass WE:' . $i);
      continue;
    }
    // Bypass Globals.
    if (isset($globals[str_pad($i, 2, '0', STR_PAD_LEFT)])) {
      drush_print('Bypass Global:' . $i);
      continue;
    }
    $strtime =  "$year-$month-$i 00:00:00";
    if (!productivity_time_tracking_get_employee_tracking_count($strtime, $employee)) {
      productivity_time_tracking_save($timestamp, $employee, $project_nid);
      drush_print('Saved day for ' . $i);
    }
    else {
      drush_print('Bypass saving for ' . $i);
    }
  }
}
