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
 * Menu callback; Display monthly employee report.
 */
function productivity_timewatch_monthly_employee_report_multiple_callback() {
  
  
  return productivity_timewatch_monthly_employee_report();
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

  // Initialize variables.
  $variables['date'] = date("F Y", strtotime("$year-$month-01"));
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
      'year' => !empty($year) ? $year : date('Y'),
      'month' => !empty($month) ? $month : date('m', strtotime("-1 month")),
    ),
  ), 'setting');

  // No project given, return early.
  if (!$account) {
    $variables['fullname']  = '';
    $variables['report'] = '';
    return theme('productivity_timewatch_monthly_employee_report', $variables);
  }

  $wrapper = entity_metadata_wrapper('user', $account);
  $variables['fullname'] = $wrapper->field_full_name->label();


  // No working day return early.
  if (!$variables['report'] = productivity_timewatch_build_report($account, $year, $month)) {
    $variables['no_result'] = TRUE;
    $variables['message'] = t('No work done this month.');
  }

  $variables['current_uid'] = $account->uid;


  return theme('productivity_timewatch_monthly_employee_report', $variables);
}

/**
 * Build table report with summary.
 */
function productivity_timewatch_build_report($account, $year, $month){
  // Get all nodes for the current month.
  $node_keys = productivity_timewatch_get_user_sessions($account->uid, $year, $month);

  // No working day return early.
  if (!$node_keys) {
    return FALSE;
  }

  $summary =  array();
  // Get all sessions for the project.
  $sessions = productivity_timewatch_create_sessions_table($node_keys, $summary);
  // Main table headers.
  $header = array(
    t('Date'),
    t('Week day'),
    t('Entry'),
    t('Exit'),
    t('Total'),
    t('Project/ Type'),
    t('Source'),
    t('Retro'),
    t('All day Total'),
  );

  // Get the skeleton of the full month.
  $summary['potential'] = array(
    'name' => t('Potential'),
    'type' => '',
    'retro_count' => '',
    'total_minutes' => 0,
    'actual' => '100%',
  );
  $month_array = productivity_timewatch_build_month_skeleton($month, $year, $summary['potential']['total_minutes']);
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
  $variables_report = array();
  $variables_report['year'] = $year;
  $variables_report['month']= $month;
  $variables_report['username']= $account->name;
  $variables_report['table'] = theme('table', array(
    'header' => $header,
    'rows' => $array_table
  ));

  $variables_report['table_summary'] = productivity_timewatch_create_summary_table($summary);
  // Get all the projects for project input
  return theme('productivity_timewatch_monthly_employee_report_table', $variables_report);
}

/**
 * Build monthly array skeleton
 */
function productivity_timewatch_build_month_skeleton($month, $year, &$potentials){
  $globals = productivity_timewatch_get_global_days($year, $month);
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
    $week_day =  date('l', $date);
    // Special day, holiday or funday.
    $special_day_name = isset($globals[$day_key]) ? $globals[$day_key]['label'] : FALSE;
    $array[$key]  = array(
      'day' => $day_key,
      'Date' => date('d/m/y', $date),
      'Week day' => $week_day,
    );
    // Count potentials hours, no WE and no Holiday days.
    if (!in_array($week_day, array('Friday', 'Saturday')) && !$special_day_name) {
      $potentials += 9 * 60;
    }
    // Holidays.
    if ($special_day_name) {
      $special_day_length = ($globals[$day_key]['end'] - $globals[$day_key]['start']);
      $special_day_length_diff =  (9 * 60 * 60) - $special_day_length;
      // Deal with half day holidays.
      if ($special_day_length_diff > 0) {
        $potentials += ($special_day_length_diff / 60);
      }
      $array[$key]['Week day'] = t('@week_day - !link (@day_length Hours)', array(
        '@week_day' => $week_day,
        '!link' => l($special_day_name, 'node/' . $globals[$day_key]['nid']),
        '@day_length' => productivity_timewatch_format_total($special_day_length / 60),
      ));
    }
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
function productivity_timewatch_create_sessions_table($node_keys, &$summary) {
  $sessions = array();
  $summary['total'] = array(
    'name' => t('Total time'),
    'type' => '',
    'retro_count' => '',
    'total_minutes' => 0,
    'actual' => '100%',
  );

  foreach($node_keys as $nid) {
    $wrapper = entity_metadata_wrapper('node', $nid);
    $node_account  =$wrapper->author->value();
    $start_time = $wrapper->field_session_date->value->value();
    $end_time = $wrapper->field_session_date->value2->value();

    $total_time = $end_time - $start_time;
    $total_minutes = floor($total_time / 60);


    $day = date('d', $start_time);

    // Day type (Global/Miluim/Regular) or project name (Madaan).
    $retro = FALSE;
    $type = '';
    $day_name = $pid = $wrapper->field_session_type->label();
    if ($pid == NULL) {
      $day_name = $pid = 'Regular';
    }

    // Madaan day.
    if ($wrapper->field_project->value() != NULL) {
      $day_name = $wrapper->field_project->label();
      $pid = $wrapper->field_project->getIdentifier();
      $type = t('MOP Madaan');

      // Retro.
      $one_day = 24*60*60;
      if ($wrapper->changed->value() > $end_time + $one_day) {
        $retro = TRUE;
      }
    }

    // Create row for day.
    $sessions[$day][] = array(
      'entry' => l(date('H:i', $start_time), 'node/' . $nid),
      'exit' => date('H:i', $end_time),
      'total' => $total_minutes,
      'project' => $day_name,
      // The source of the data, using time watch or from home (manual).
      'source' => in_array('timewatch', $node_account->roles) ? 'timewatch' : 'manual',
      'retro' => $retro ? t('yes') : t('no'),
    );

    // Create stub for summary.
    if (!isset($summary[$pid])) {
      $summary[$pid] = array(
        'name' => $day_name,
        'type' => $type,
        'retro_count' => '',
        'total_minutes' => 0,
        'actual' => 0,
      );
    }


    // Add current total.
    if ($retro) {
      if (!isset($summary["{$pid}_retro"])) {
        $summary["{$pid}_retro"] = array(
          'name' => $day_name,
          'type' => $type,
          'retro_count' => 'Y',
          'total_minutes' => 0,
          'actual' => 0,
        );
      }
      $summary["{$pid}_retro"]['total_minutes'] += $total_minutes;
    }
    else {
      $summary[$pid]['total_minutes'] += $total_minutes;
    }
    $summary['total']['total_minutes'] += $total_minutes;
  }
  return $sessions;
}

/**
 * Create summary table displayed in footer.
 */
function productivity_timewatch_create_summary_table($summaries) {
  // Headers.
  $header = array(
    t('Project/ Type'),
    t('Type'),
    t('Retro'),
    t('Total Hours'),
    t('Actual % Employment'),
  );
  $total = $summaries['potential']['total_minutes'];
  // Calc actual %
  foreach($summaries as &$summary) {
    $summary['actual'] = number_format(100 / $total * $summary['total_minutes'], 2) . '%';
    $summary['total_minutes'] = productivity_timewatch_format_total($summary['total_minutes'], TRUE);
  }
  // Move the Total to last.
  $total = $summaries['total'];
  unset($summaries['total']);
  $summaries['total'] = $total;

  return theme('table', array(
    'header' => $header,
    'rows' => $summaries,
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