<?php
/**
 * Created by PhpStorm.
 * User: bricelenfant
 * Date: 12/13/14
 * Time: 11:38 PM
 */


// CSV Output
$csv =  drupal_get_path('module', 'productivity_migrate') . '/script/time_tracking_2014.csv';
$fp = fopen($csv, 'w');
// Add CSV header.
fputcsv($fp, array(
    'id',
    'date',
    'employee',
    'project',
    'work amount',
    'unit',
    'work description',
    'type',
  )
);

// Scan directory for ll CSVs.
$url =  drupal_get_path('module', 'productivity_migrate') . '/script/2014';
$files = array_diff(scandir($url), array('..', '.'));

foreach($files as $file) {
  drush_print('processing ' . $file);
  $csvData = file_get_contents($url . '/' . $file);
  $year = '2014';

  $lines = explode(PHP_EOL, $csvData);
  $tracking = array();
  foreach ($lines as $line) {
    $tracking[] = str_getcsv($line);
  }
  $header = array_shift($tracking);

  $projects = array();
  $max = count($header);
  for ($i = 1; $i < $max; $i+=2) {
    $projects[$header[$i]] = array(
      'unit' => $header[$i+1],
      'column' => $i,
      'name' => $header[$i],
      'tracking' => array(),
    );
  }

  $max_row = count($tracking);
  $results =array();
  // Get daily data
  foreach ($projects as &$project) {
    for ($i = 0; $i < $max_row; $i++) {
      $interval =  (double) trim($tracking[$i][$project['column']]);

      // If interval is number and not zero.
      if (!is_numeric($interval) ||  !$interval) {
        continue;
      }

      $developers = explode('|', $tracking[$i][$project['column']+1]);
      $daily_avg = 1;
      if ($project['unit'] == 'hour') {
        $daily_avg = 8;
      }
      $developers_count = count($developers);
      // Case developer is empty, set unknown as default.
      // Save foreach developer.
      foreach ($developers as $key => $developer) {
        // if we 3 developer and 20 hours, give 8h to first 2 and 4h to last.
        if ($interval >= $daily_avg) {
          $daily_interval = $daily_avg;
          $interval-= $daily_avg;
        }
        else {
          $daily_interval = $interval;
        }
        // Create all metadats.
        $date = $tracking[$i][0] . '.' . $header[0] . '.' . $year;
        $results[] = array(
          //id,date,employee,project,work amount,amount unit(hours/days),work description
          'id' => $date . '-' . $developer . '-' . $project['name'],
          'date' => $date,
          'employee' => $developer,
          'project' => $project['name'],
          'work amount' => $daily_interval,
          'unit' => $project['unit'],
          'work description' => '',
          'type' => 'regular',
          '' => '',
        );
      }
    }
  }


  foreach ($results as $result) {
    fputcsv($fp, $result);
  }

}
fclose($fp);
