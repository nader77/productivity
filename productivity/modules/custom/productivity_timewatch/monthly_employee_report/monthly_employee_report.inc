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
 * Menu callback; Display monthly employee report PDF.
 */
use TijsVerkoyen\CssToInlineStyles\CssToInlineStyles;
function productivity_timewatch_monthly_employee_report_pdf_callback($account, $year, $month) {


  $html = productivity_timewatch_build_report($account, $year, $month);
  if (!$html) {
    return "No Data for this user.";
  }
  // Composer's auto-loading functionality
  require libraries_get_path('dompdf') . "/autoload.inc.php";
  require libraries_get_path('css-to-inline') . "/vendor/autoload.php";

  // Set inline CSS.
  $css1 = drupal_get_path('theme', 'bootstrap_subtheme') . '/bootstrap/css/bootstrap.css';
  $css2 = drupal_get_path('module', 'productivity_timewatch') . '/monthly_employee_report/monthly_employee_report_pdf.css';
  $css = file_get_contents($css1);
  $css .= file_get_contents($css2);
  $cssToInlineStyles = new CssToInlineStyles($html, $css);

  $html = $cssToInlineStyles->convert();

  // Generate PDF.
  $dompdf = new Dompdf\Dompdf();
  $dompdf->setBasePath(url($css, array('absolute' => TRUE)));
  $dompdf->loadHtml($html);
  $dompdf->render();
  $filename = $account->name . "-$year-$month.pdf";
  $pdf_content = $dompdf->output($filename);
  $file = file_save_data($pdf_content, 'public://' . $filename, FILE_EXISTS_REPLACE);
  $http_headers = array(
    'Content-Type' => 'application/pdf',
    'Content-Disposition' => 'attachment; filename="' . $filename . '"',
    'Content-Length' => $file->filesize,
  );
  file_transfer($file->uri, $http_headers);
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
  $variables['employees'] = user_load_multiple(productivity_account_get_employee_uids());
  $variables['current_uid'] = 0;
  $variables['project_title'] = 'Select a project';
  $variables['account'] = '';
  $variables['no_result'] = FALSE;
  $variables['message'] = '';
  $variables['table'] = '';
  $variables['year'] = !empty($year) ? $year : date('Y');
  $variables['month'] = !empty($month) ? $month : date('m', strtotime("-1 month"));
  $variables['pdf_url'] = FALSE;

  // Add to JS settings current Month/Year.

  drupal_add_js(array(
    'report' => array(
      'base_url' => $base_url,
      'pdf_url_start' => url('monthly-employee-report/pdf'),
      'pdf_url_end' => "/$year/$month",
      'year' => $variables['year'],
      'month' => $variables['month'],
      'employees' => $variables['employees'],
    ),
  ), 'setting');

  // No project given, return early.
  if (!$account) {
    $variables['report'] = '';
    return theme('productivity_timewatch_monthly_employee_report', $variables);
  }

  // No working day return early.
  if (!$variables['report'] = productivity_timewatch_build_report($account, $year, $month)) {
    $variables['no_result'] = TRUE;
    $variables['message'] = t('No work done this month.');
  }

  $variables['current_uid'] = $account->uid;
  $variables['pdf_url'] = url('monthly-employee-report/pdf') . "/{$account->uid}/$year/$month";


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
  // Get the skeleton of the full month.
  $summary['potential'] = array(
    'name' => t('Potential'),
    'total_minutes' => 0,
    'actual' => '100%',
  );

  // Default to last day of the month
  $endday =  date('t', strtotime('1.' . $month . '.' . $year));

  // Case employee has stoped working, and we are on the month he stoped.
  if ($account->field_date['und'][0]['value'] != $account->field_date['und'][0]['value2']
    && "$month-$year" == date('n-Y', strtotime($account->field_date['und'][0]['value2']))) {
    $endday = date('j', strtotime($account->field_date['und'][0]['value2']));
    $summary['potential']['name'] = t('Potential (For partial month)');
  }
  // Case we are in the middle of current month, or if employee is leaving in
  // the cuurent month but todays date id before that.
  if ("$month-$year" == date('n-Y') && (!$endday || $endday > date('j'))) {
    $endday = date('j');
    $summary['potential']['name'] = t('Potential (until today)');
  }

  $month_array = productivity_timewatch_build_month_skeleton($month, $year, $summary['potential']['total_minutes'], $endday);
  // Get all sessions for the project.
  $month_array = productivity_timewatch_create_sessions_table($node_keys, $summary, $month_array, $endday);

  $variables_report = array();
  $variables_report['year'] = $year;
  $variables_report['month']= $month;
  $wrapper = entity_metadata_wrapper('user', $account);
  $variables_report['fullname'] = $wrapper->field_full_name->label() ? $wrapper->field_full_name->label() : $account->name;
  $variables_report['date'] = date("F Y", strtotime("$year-$month-01"));

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
  $variables_report['table'] = theme('table', array(
    'header' => $header,
    'rows' => $month_array
  ));

  $variables_report['table_summary'] = productivity_timewatch_create_summary_table($summary);
  // Get all the projects for project input
  return theme('productivity_timewatch_monthly_employee_report_table', $variables_report);
}

/**
 * Build monthly array skeleton
 *
 * @param $endday - the last day of the skeleton, if an employee left before the
 *   end of the month of if we are in is the middle of the current month.
 *
 */
function productivity_timewatch_build_month_skeleton($month, $year, &$potentials, $last_day_this_month){
  $globals = productivity_timewatch_get_global_days($year, $month);
  $array = array();

  // Loop into the days of the month.
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
      '01.Date' => date('d/m/y', $date),
      '02.Week day' => $week_day,
      '03.entry' => FALSE,
      '04.exit' => '',
      '05.total' => '',
      '06.project' => t('Day Off'),
      '07.source' => '',
      '08.retro' => 'no',
      '09.all day total' => '',
    );
    // Count potentials hours, no WE and no Holiday days.
    if (!in_array($week_day, array('Friday', 'Saturday')) && !$special_day_name) {
      $potentials += 9 * 60;
    }
    // Label weekends.
    if(in_array($week_day, array('Friday', 'Saturday'))) {
      $array[$key]['06.project'] = t('Weekend');
    }
    // Holidays.
    if ($special_day_name) {
      $special_day_length = ($globals[$day_key]['end'] - $globals[$day_key]['start']);
      $special_day_length_diff =  (9 * 60 * 60) - $special_day_length;
      // Deal with half day holidays.
      if ($special_day_length_diff > 0) {
        $potentials += ($special_day_length_diff / 60);
      }
      $array[$key]['06.project'] = t('@type - !link (@day_length Hours)', array(
        '@type' => $globals[$day_key]['type'],
        '!link' => l($special_day_name, 'node/' . $globals[$day_key]['nid']),
        '@day_length' => productivity_timewatch_format_total($special_day_length / 60),
      ));
      // Remove the FALSE, to print the day.
      $array[$key]['03.entry'] = '-';
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
 * @param $endday - the last day of the skeleton, if an employee left before the
 *   end of the month of if we are in is the middle of the current month.
 *
 * @return array
 *  Matrix of all the sessions, and the URL project
 */
function productivity_timewatch_create_sessions_table($node_keys, &$summary, $month_array, $endday) {
//  $sessions = array();
  $summary['total'] = array(
    'name' => t('Total'),
    'total_minutes' => 0,
    'actual' => '100%',
  );
  $daily_sum = array();
  foreach ($node_keys as $nid) {
    $wrapper = entity_metadata_wrapper('node', $nid);
    $node_account = $wrapper->author->value();
    $start_time = $wrapper->field_session_date->value->value();
    $end_time = $wrapper->field_session_date->value2->value();
    // No end time.
    if (!$end_time) {
      $end_time = $start_time;
    }

    $total_time = $end_time - $start_time;
    $total_minutes = floor($total_time / 60);

    // Day type (Global/Miluim/Regular) or project name (Madaan).
    $retro = FALSE;
    $day_name = $pid = $wrapper->field_session_type->label();
    if ($pid == NULL) {
      $day_name = $pid = 'Regular';
    }

    $madaan = FALSE;
    // Madaan day.
    if ($wrapper->field_project->value() != NULL) {
      $day_name = $wrapper->field_project->label();
      $pid = $wrapper->field_project->getIdentifier();
      $madaan = TRUE;

      // Retro.
      $one_day = 24 * 60 * 60;
      if ($wrapper->changed->value() > $end_time + $one_day && !variable_get('productivity_bypass_retro', TRUE)) {
        $retro = TRUE;
      }
    }

    // Get the proper key to support multiple entrance per day, first occurrence 01_1, second 01_2 ...
    $key = 0;
    $day = date('d', $start_time);

    // Stop at $endday limit.
    if ($endday >= $day) {

      // Create multiple day instances.
      while (TRUE) {
        $day_key = $day . '_' . $key;
        if (isset($month_array[$day_key]) && !$month_array[$day_key]['03.entry']) {
          break;
        }
        if (!isset($month_array[$day_key])) {
          $month_array[$day_key] = array();
          break;
        }
        $key++;
      }


      $month_array[$day_key] = array(
          '03.entry' => l(date('H:i', $start_time), 'node/' . $nid),
          '04.exit' => date('H:i', $end_time),
          '05.total' => productivity_timewatch_format_total($total_minutes),
          '06.project' => $day_name,
          // The source of the data, using time watch or from home (manual).
          '07.source' => in_array('timewatch', $node_account->roles) ? 'timewatch' : 'manual',
          '08.retro' => $retro ? t('yes') : t('no'),
          '09.all day total' => productivity_timewatch_format_total($total_minutes),
        ) + $month_array[$day_key];

      $daily_sum[$day_key] = $total_minutes;
      // Multiple entrance in same day, summarize total day on last day.
      if ($key > 0) {
        // If more than one entrance in a day, display total only in last line.
        $previous_day_key = $day . '_' . ($key - 1);
        $month_array[$day_key]['01.Date'] = $month_array[$previous_day_key]['01.Date'];
        // If previous day was half day holiday.
        if ($month_array[$previous_day_key]['03.entry'] != '-') {
          $month_array[$day_key]['02.Week day'] = t('Re-entry');
        }
        else {
          $month_array[$day_key]['02.Week day'] = $month_array[$previous_day_key]['02.Week day'];
        }
        // Case holiday or global day.
        if (!isset($daily_sum[$previous_day_key])) {
          $daily_sum[$previous_day_key] = 0;
        }
        $month_array[$day_key]['09.all day total'] = productivity_timewatch_format_total($total_minutes + $daily_sum[$previous_day_key]);
        $month_array[$previous_day_key]['09.all day total'] = '';
        $daily_sum[$day_key] += $total_minutes;
      }
      // Sort by key.
      ksort($month_array[$day_key]);

      // Create stub for summary.
      if (!isset($summary[$pid])) {
        $summary[$pid] = array(
          'name' => $day_name,
          'total_minutes' => 0,
          'actual' => 0,
        );
        // Set name for MOP project.
        if ($madaan) {
          $summary[$pid]['name'] .= t(' MOP Madaan');
        }
      }

      // Add current total.
      if ($retro) {
        if (!isset($summary["{$pid}_retro"])) {
          $summary["{$pid}_retro"] = array(
            'name' => $day_name . t(' MOP Madaan - Retro updates'),
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
  }
  // Sort by day.
  ksort($month_array);
  return $month_array;
}

/**
 * Create summary table displayed in footer.
 */
function productivity_timewatch_create_summary_table($summaries) {
  // Headers.
  $header = array(
    t('Project/ Type'),
    t('Total'),
    t('%'),
  );

  $time_off = $summaries['potential']['total_minutes'] - $summaries['total']['total_minutes'];
  // Extra time.
  $label =t('Time off');
  if ($time_off < 0) {
    $label = t('Extra time (Included in Regular time)');
    $time_off *= -1;
  }
  // Undeclared days, this are hours not marked as anything.
  $summaries['time off'] = array(
    'name' => $label,
    'total_minutes' => $time_off,
    'actual' => '100%',
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

  // Move the potential to last.
  $potential = $summaries['potential'];
  unset($summaries['potential']);
  $summaries['potential'] = $potential;


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