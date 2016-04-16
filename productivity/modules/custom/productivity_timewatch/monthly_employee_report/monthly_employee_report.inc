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
    drupal_add_css(drupal_get_path('theme', 'bootstrap_subtheme') . '/js/bootstrap-datepicker/css/bootstrap-datepicker.min.css');// Add Datepicker lib.
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
 */
function productivity_timewatch_monthly_employee_report($account = FALSE, $year = FALSE, $month = FALSE) {
  global $base_url;
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


  $variables['employees'] = user_load_multiple(productivity_account_get_employee_uids());
  $variables['current_uid'] = 0;
  $variables['project_title'] = 'Select a project';
  $variables['account'] = '';
  $variables['no_result'] = FALSE;
  $variables['message'] = '';
  $variables['table'] = '';

  drupal_add_js(array(
    'report' => array(
      'base_url' => $base_url,
      'year' => $variables['year'],
      'month' => $variables['month'],
    ),
  ), 'setting');

  // No project given.
  if (!$account) {
    return theme('productivity_timewatch_monthly_employee_report', $variables);
  }

  $wrapper = entity_metadata_wrapper('user', $account);

  $variables['fullname'] = $wrapper->field_full_name->label();

  $node_keys = productivity_timewatch_get_user_sessions($account->uid, $variables['year'], $variables['month']);
  $sessions = array();


  // Summarize Madaan project total.
  $projects =  array();
  if ($node_keys) {
    // Get all issues for the project.
    $sessions = productivity_timewatch_create_issues_table($node_keys, $projects);
  }
  else {
    $variables['no_result'] = TRUE;
    $variables['message'] = t('No work done this month.');
  }

  $variables['theme_path'] = base_path() . drupal_get_path('theme', 'bootstrap_subtheme');

  // Headers.
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

  // Get the skelaton of the full month.
  $month_array = productivity_timewatch_build_month_skeleton($month, $year);
  // Summarize month total.
  $total = array(
    'hours' => 0,
    'minutes' => 0,
  );

  // Build month table with data.
  foreach($month_array as $day => $value) {
    if (isset($sessions[$day])) {
      $day_key = $day;
      $day_total = array(
        'hours' => 0,
        'minutes' => 0,
      );
      foreach ($sessions[$day] as $key => $session) {
        // Second entrance or more for the day.
        if ($key > 0) {
          // If more than one entrance in a day, display total only in last line.
          $month_array[$day_key]['Actual Total inc Missing'] = '';
          $day_key = $day . '_' . $key;
          $month_array[$day_key] = array(
              'Date' => '',
              'Week day' => '',
          );
          $day_total['hours'] += $session['total']['hours'];
          $day_total['minutes'] += $session['total']['minutes'];
          // Change format to display (from array).
          $session['total'] = productivity_timewatch_format_total($session['total']);
        }
        // First entrance of the day.
        else {
          // Init total fo all entrance in that day.
          $day_total['hours'] = $session['total']['hours'];
          $day_total['minutes'] = $session['total']['minutes'];
          // Change format to display (from array).
          $session['total'] = productivity_timewatch_format_total($session['total']);
        }
        $month_array[$day_key] += $session;
        $month_array[$day_key]['all day total'] = productivity_timewatch_format_total($day_total);
        $total['hours'] += $day_total['hours'];
        $total['minutes'] += $day_total['minutes'];
      }
    }
    // Create empty stub for no-data days.
    else {
      $month_array[$day] += array(
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
  ksort($month_array);
  $variables['table'] = theme('table', array(
    'header' => $header,
    'rows' => $month_array
  ));

  $variables['table_summary'] = productivity_timewatch_create_summary_table($account->uid, $projects, $total);

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
    $key = str_pad($day, 2, '0', STR_PAD_LEFT);
    $date_string = format_string("@month/@day/@year", array(
      '@day' => $day,
      '@month' => $month,
      '@year' => $year,
    ));
    $date = strtotime($date_string);
    $array[$key]  = array(
      'Date' => date('d/m/y', $date),
      'Week day' => date('l', $date),
    );
  }
  return $array;
}

/**
 * Create a matrix of all the issues from GitHub nodes,
 * And the url project.
 *
 * @param $nodes
 *  All the nodes return from the query.
 *
 * @return array
 *  Matrix of all the issues, and the URL project
 */
function productivity_timewatch_create_issues_table($node_keys, &$projects) {
  $sessions = array();
  foreach($node_keys as $nid) {
    $wrapper = entity_metadata_wrapper('node', $nid);
    $node_account  =$wrapper->author->value();
    $start_time = $wrapper->field_session_date->value->value();
    $end_time = $wrapper->field_session_date->value2->value();

    $total_time = $end_time - $start_time;
    $total = array(
      'hours' => floor($total_time / 3600),
      'minutes' => floor(($total_time % 3600) / 60),
    );

    $day = date('d', $start_time);

    $today = $sessions[$day][] = array(
      'entry' => l(date('H:i', $start_time), 'node/' . $nid),
      'exit' => date('H:i', $end_time),
      'total' => $total,
      'project' => ($wrapper->field_session_type->label() == 'Regular') ? $wrapper->field_project->label() : $wrapper->field_session_type->label(),
      // The source of the data, using time watch or from home (manual).
      'source' => in_array('timewatch', $node_account->roles) ? 'timewatch' : 'manual',
      'retro' => 'yes',
    );

    if ($wrapper->field_project) {
      $pid = $wrapper->field_project->getIdentifier();
      // Init array.
      if (!isset($projects[$pid])) {
        $projects[$pid] = array(
          'retro_count' => 0,
          'total' => array(
            'hours' => 0,
            'minutes' => 0,
          ),
        );
      }

      // Add current total.
      $projects[$pid]['retro_count'] = $today['retro'] == 'yes' ? +1 : +0;
      $projects[$pid]['total']['hours'] =+ $today['total']['hours'];
      $projects[$pid]['total']['minutes'] += $today['total']['minutes'];
    }
  }
  return $sessions;
}

/**
 * Create summary table displayed in footer.
 */
function productivity_timewatch_create_summary_table($uid, $projects, $total) {
  // Headers.
  $header = array(
    t('Project'),
    t('Type'),
    t('Retro'),
    t('Total Hours'),
    t('% Employment'),
  );

  $user_wrapper = entity_metadata_wrapper('user', $uid);
  $summary = array();
  foreach ($user_wrapper->field_project_madaan as $multifield) {
    $pid = $multifield->field_project->getIdentifier();
    if (!isset($projects[$pid])) {
      $retro = 0;
      $total_display = 0;
    }
    else {
      $retro = $projects[$pid]['retro_count'];
      $total_display = productivity_timewatch_format_total($projects[$pid]['total']);
    }
    $summary[] = array(
      'project' => $multifield->field_project->label(),
      'type' => t('MOP Madaan'),
      'retro' => $retro,
      'total' => $total_display,
      'percent' => $multifield->field_percent_time->value(),
    );
  }

  $summary[] = array(
    'project' => t('Total time'),
    'type' => '',
    'retro' => '',
    'total' => productivity_timewatch_format_total($total, TRUE),
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
function productivity_timewatch_format_total($total, $dec = FALSE) {
  $return = $total['hours'] . ':' . str_pad($total['minutes'], 2, '0', STR_PAD_LEFT);
  if ($dec) {
    $return .= ' (' . number_format($total['hours'] + ($total['minutes'] / 60), 2) . ')';
  }
  return $return;
}