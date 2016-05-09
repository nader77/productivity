<?php
/**
 * @file
 * Code for the Productivity time tracking feature.
 */

/**
 * Menu callback; Display monthly employee report.
 */
function productivity_timewatch_monthly_employee_report_callback($account = FALSE, $year = FALSE, $month = FALSE) {
  return productivity_timewatch_monthly_employee_report($account, $year, $month);
}

/**
 * Load all resources for the page.
 * @param $local
 */
function productivity_timewatch_monthly_employee_load_resources($local = FALSE) {
  // Add JavaScript file with the base url of the page.
  drupal_add_js(drupal_get_path('module', 'productivity_timewatch') . '/monthly_employee_report/monthly_employee_report.js');
  drupal_add_css(drupal_get_path('module', 'productivity_timewatch') . '/monthly_employee_report/monthly_employee_report.css');
  // No CDN.
  if ($local) {

    // Add Datepicker lib.
    drupal_add_js(drupal_get_path('theme', 'bootstrap_subtheme') . '/js/bootstrap-datepicker/js/bootstrap-datepicker.js');
    drupal_add_css(drupal_get_path('theme', 'bootstrap_subtheme') . '/js/bootstrap-datepicker/css/bootstrap-datepicker.min.css');
    // Add select 2
    drupal_add_js(drupal_get_path('theme', 'bootstrap_subtheme') . '/js/select2/js/select2.js');
    drupal_add_css(drupal_get_path('theme', 'bootstrap_subtheme') . '/js/select2/css/select2.min.css');
  }
  else {
    // Add JavaScript file with the base url of the page.
    drupal_add_css('https://fonts.googleapis.com/css?family=Abril+Fatface', array('type' => 'external'));
    drupal_add_css("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/css/select2.min.css", array('type' => 'external'));
    drupal_add_js("//cdnjs.cloudflare.com/ajax/libs/select2/4.0.1/js/select2.min.js", array('type' => 'external'));

    // Add Datepicker lib.
    drupal_add_js("https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.6.0/js/bootstrap-datepicker.min.js", array('type' => 'external'));
    drupal_add_css("https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.6.0/css/bootstrap-datepicker.min.css", array('type' => 'external'));
  }
}

/**
 * Create the employee monthly report, with printable version.
 */
function productivity_timewatch_monthly_employee_report($account = FALSE, $year = FALSE, $month = FALSE) {
  global $base_url;
  // Load External resources.
  productivity_timewatch_monthly_employee_load_resources();

  $variables = array();
  $variables['year'] = !empty($year) ? $year : date('Y');
  $variables['month']= !empty($month) ? $month : date('m', strtotime("-1 month"));

  if ($year == 'all'){
    $variables['date'] = t('All time');
  }
  elseif ($month == 'all'){
    $variables['date'] = t('Year @year', array('@year' => $year));
  }
  else {
    $variables['date'] = date("F Y", strtotime("$year-$month-01"));
  }

  // Initialize variables.
  $variables['employees'] = user_load_multiple(productivity_account_get_employee_uids());
  $variables['current_uid'] = 0;
  $variables['project_title'] = 'Select a project';
  $variables['account'] = '';
  $variables['no_result'] = FALSE;
  $variables['message'] = '';
  $variables['table'] = '';

  // Add to JS settings current Month/Year.
  drupal_add_js(array(
    'report' => array(
      'base_url' => $base_url,
      'year' => $variables['year'],
      'month' => $variables['month'],
    ),
  ), 'setting');

  // No project given, return early.
  if (!$account) {
    return theme('productivity_timewatch_monthly_employee_report', $variables);
  }

  $wrapper = entity_metadata_wrapper('user', $account);
  $variables['fullname'] = $wrapper->field_full_name->label();

  // Get all nodes for the current month.
  $node_keys = productivity_timewatch_get_user_sessions($account->uid, $variables['year'], $variables['month']);
  $sessions = array();

  // TODO: Separate this into sub module for Madaam (Chief Sientist Bureau).
  // Summarize Madaan project total.
  $projects =  array();
  if ($node_keys) {
    // Get all issues for the project.
    $sessions = productivity_timewatch_create_sessions_table($node_keys, $projects, $wrapper);
  }
  // No working day return early.
  else {
    $variables['no_result'] = TRUE;
    $variables['message'] = t('No work done this month.');
  }

  // Theme path.
  $variables['theme_path'] = base_path() . drupal_get_path('theme', 'bootstrap_subtheme');

  // Main table headers.
  $header = array(
    t('Date'),
    t('Week day'),
    t('Entry'),
    t('Exit'),
    t('Total'),
    t('Project'),
    t('Source'),
    t('Retro'),
    t('All day Total'),
  );

  // Get the skeleton of the full month.
  $month_array = productivity_timewatch_build_month_skeleton($month, $year);
  $array_table = array();

  // Build month table with data.
  foreach($month_array as $day_key => $value) {
    $day = $value['day'];
    unset($value['day']);
    // We don't display.
    if (isset($sessions[$day])) {
      $day_total_minutes = 0;
      foreach ($sessions[$day] as $key => $session) {
        // Second entrance or more for the day.
        if ($key > 0) {
          // If more than one entrance in a day, display total only in last line.
          $array_table[$day_key]['all day total'] = '';
          $day_key = $day . '_' . $key;
          $array_table[$day_key] = $value;
          $array_table[$day_key] = array(
              'Date' => '',
              'Week day' => t('Re-entry'),
          );
          $day_total_minutes += $session['total'];
          // Change format to display (from array).
          $session['total'] = productivity_timewatch_format_total($session['total']);
        }
        // First entrance of the day.
        else {
          $array_table[$day_key] = $value;
          // Init total fo all entrance in that day.
          $day_total_minutes = $session['total'];
          // Change format to display (from array).
          $session['total'] = productivity_timewatch_format_total($session['total']);
        }
        $array_table[$day_key] += $session;
        $array_table[$day_key]['all day total'] = productivity_timewatch_format_total($day_total_minutes);
      }
    }
    // Create empty stub for no-data days.
    else {
      $array_table[$day_key] = $value;
      $array_table[$day_key] += array(
        'entry' => '',
        'exit' => '',
        'total' => '',
        'project' => '',
        'source' => '',
        'retro' => 'no',
        'all day total' => '',
      );
    }
  }

  // Sort by day.
  ksort($array_table);
  $variables['table'] = theme('table', array(
    'header' => $header,
    'rows' => $array_table
  ));

  $variables['table_summary'] = productivity_timewatch_create_summary_table($projects);
  // Get all the projects for project input
  $variables['current_uid'] = $account->uid;

  return theme('productivity_timewatch_monthly_employee_report', $variables);
}

/**
 * Build monthly array skeleton
 */
function productivity_timewatch_build_month_skeleton($month, $year){
  $array = array();
  $last_day_this_month  = date('t', strtotime('1.' . $month . '.' . $year));
  for ($day = 1; $day <= $last_day_this_month; $day++) {
    // Add leading zeros.
    $day_key = str_pad($day, 2, '0', STR_PAD_LEFT);
    $key = $day_key. '_0';
    $date_string = format_string("@month/@day/@year", array(
      '@day' => $day,
      '@month' => $month,
      '@year' => $year,
    ));
    $date = strtotime($date_string);
    $array[$key]  = array(
      'day' => $day_key,
      'Date' => date('d/m/y', $date),
      'Week day' => date('l', $date),
    );
  }
  return $array;
}

/**
 * Create a matrix of all the sessions nodes,
 * And the url project.
 *
 * @param $nodes
 *  All the nodes return from the query.
 *
 * @return array
 *  Matrix of all the sessions, and the URL project
 */
function productivity_timewatch_create_sessions_table($node_keys, &$projects, $user_wrapper) {
  $sessions = array();
  $projects['total'] = array(
    'total_minutes' => 0,
  );

  foreach($node_keys as $nid) {
    $wrapper = entity_metadata_wrapper('node', $nid);
    $node_account  =$wrapper->author->value();
    $start_time = $wrapper->field_session_date->value->value();
    $end_time = $wrapper->field_session_date->value2->value();

    $total_time = $end_time - $start_time;
    $total_minutes = floor($total_time / 60);


    $day = date('d', $start_time);

    // Day type (global) or project name.
    if  ($wrapper->field_session_type->label() == 'Regular' || $wrapper->field_session_type->label() == NULL) {
      $day_name = $wrapper->field_project->label();
    }
    else {
      $day_name = $wrapper->field_session_type->label();
    }

    // Retro.
    $retro = FALSE;
    $one_day = 24*60*60;
    if ($wrapper->changed->value() > $end_time + $one_day) {
      $retro = TRUE;
    }


    $sessions[$day][] = array(
      'entry' => l(date('H:i', $start_time), 'node/' . $nid),
      'exit' => date('H:i', $end_time),
      'total' => $total_minutes,
      'project' => $day_name,
      // The source of the data, using time watch or from home (manual).
      'source' => in_array('timewatch', $node_account->roles) ? 'timewatch' : 'manual',
      'retro' => $retro ? t('yes') : t('no'),
    );

    if ($wrapper->field_project->value() != NULL) {
      $pid = $wrapper->field_project->getIdentifier();
    }
    else {
      $pid = $wrapper->field_session_type->label();
      if ($pid == NULL) {
        $day_name = $pid = 'Regular';
        $type = '';
      }
      else {
        $type = t('MOP Madaan');
      }
    }

    if (!isset($projects[$pid])) {
      $projects[$pid] = array(
        'name' => $day_name,
        'type' => $type,
        'retro_count' => '',
        'total_minutes' => 0,
        'actual' => 0,
      );
    }


    // Add current total.
    if ($retro) {
      if (!isset($projects["{$pid}_retro"])) {
        $projects["{$pid}_retro"] = array(
          'name' => $day_name,
          'type' => $type,
          'retro_count' => 'Y',
          'total_minutes' => 0,
          'actual' => 0,
        );
      }
      $projects["{$pid}_retro"]['total_minutes'] += $total_minutes;
    }
    else {
      $projects[$pid]['total_minutes'] += $total_minutes;
    }
    $projects['total']['total_minutes'] += $total_minutes;
  }
  dpm($projects);
  return $sessions;
}

/**
 * Create summary table displayed in footer.
 */
function productivity_timewatch_create_summary_table($projects) {
  // Headers.
  $header = array(
    t('Project'),
    t('Type'),
    t('Retro'),
    t('Total Hours'),
    t('Actual % Employment'),
  );
  $total = $projects['total']['total_minutes'];
  unset($projects['total']);
  // Calc actual %
  foreach($projects as &$project) {
    $project['actual'] = number_format(100 / $total * $project['total_minutes'], 2) . '%';
//    $project['teken'] .= '%';
    $project['total_minutes'] = productivity_timewatch_format_total($project['total_minutes'], TRUE);
  }
  // TODO: Add potential time.
  $summary = $projects;
  $summary[] = array(
    'project' => t('Total time'),
    'type' => '',
    'retro' => '',
    'total' => productivity_timewatch_format_total($total, TRUE),
//    'teken' => '',
    'percent' => '100%',
  );

  return theme('table', array(
    'header' => $header,
    'rows' => $summary,
  ));
}

/**
 * Format hours and minutes to -> hh:mm (dec value in Hours).
 */
function productivity_timewatch_format_total($minutes, $dec = FALSE) {
  $hours = floor($minutes / 60);
  $minutes = floor($minutes % 60);
  if (!$dec) {
    $return = $hours . ':' . str_pad($minutes, 2, '0', STR_PAD_LEFT);
  }
  else {
    $return = number_format($hours + ($minutes / 60), 2);
  }
  return $return;
}