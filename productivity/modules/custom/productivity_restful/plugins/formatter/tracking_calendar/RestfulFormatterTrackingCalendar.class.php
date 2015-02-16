<?php

/**
 * @file
 * Contains RestfulFormatterJson.
 */

class RestfulFormatterTrackingCalendar extends \RestfulFormatterBase implements \RestfulFormatterInterface {

  /**
   * Content Type
   *
   * @var string
   */
  protected $contentType = 'application/json; charset=utf-8';

  /**
   * {@inheritdoc}
   */
  public function prepare(array $data) {
    // If we're returning an error then set the content type to
    // 'application/problem+json; charset=utf-8'.
    if (!empty($data['status']) && floor($data['status'] / 100) != 2) {
      $this->contentType = 'application/problem+json; charset=utf-8';
      return $data;
    }

    $output = array('data' => $this->arrangeByDate($data));

    if (!empty($this->handler)) {
      if (
        method_exists($this->handler, 'getTotalCount') &&
        method_exists($this->handler, 'isListRequest') &&
        $this->handler->isListRequest()
      ) {
        // Get the total number of items for the current request without pagination.
        $output['count'] = $this->handler->getTotalCount();
      }
      if (method_exists($this->handler, 'additionalHateoas')) {
        $output = array_merge($output, $this->handler->additionalHateoas());
      }

      // Add HATEOAS to the output.
      $this->addHateoas($output);
    }

    return $output;
  }

  private function arrangeByDate(array $data) {
    // Build an associative array by day.
    $request = $this->handler->getRequest();
    $method = $this->handler->getMethod();
    // For update and create just alter the single element.
    if ($method != 'GET') {
      if ($data[0]['type'] != 'regular') {
        $data[0]['projectName'] = $data[0]['type'];
        $data[0]['length'] = strtoupper(substr($data[0]['type'], 0, 1));
      }
      if ($method == 'POST') {
        $data[0]['new'] = true;
      }
      return $data;
    }

    // If globals return early.
    if (!empty($request['global'])) {
      return $data;
    }

    // Multiple user data format.
    if (empty($request['employee'])) {
      $uids = $this->handler->getUserInPager();
      $user_load = user_load_multiple($uids);
      $users = array();
      foreach ($user_load as $user_loaded) {
        $users[] = $user_loaded->name;
      }
    }
    else {
      // Single user request.
      $users = array($request['employee']);
    }

    // Global days
    $month = $request['month'];
    $year = $request['year'];
    $last_day_this_month  = date('t', strtotime('1.' . $month . '.' . $year));
    $assoc_globals = productivity_time_tracking_get_global_days($month, $year);

    // Build skeleton of array, on item per day.
    $new_data = array();
    foreach ($users as $employee) {
      $new_data[$employee]  = array();
      // Go over days of the month.
      for ($i = 1; $i <= $last_day_this_month; $i++) {
        // Add leading zeros.
        $key = str_pad($i, 2, '0', STR_PAD_LEFT);
        $new_data[$employee][$key]  = array();

        // Mark weekends.
        $week_day = date( "w", strtotime($i . '.' . $month . '.' . $year));

        // If Friday or Saturday.
        if (in_array($week_day, array(5, 6))) {
          $day_item = array(
            'id' => 'new',
            'type' => 'weekend',
            'day' => $key,
            'length' => 'W',
            'projectName' => 'Weekend',
            'employee' => $employee,
          );
          // Add item for weekend.
          $new_data[$employee][$key][] = $day_item;
        }

        // Add global day to user sqeleton.
        if (isset($assoc_globals[$key])) {
          $assoc_globals[$key]['employee'] = $employee;
          $new_data[$employee][$key][] = $assoc_globals[$key];
        }
      }
    }

    // Save regular (non global) tracking days.
    foreach ($data as $day) {
      // Non regular days, display special info.
      if ($day['type'] != 'regular') {
        // Don't change Global days.
        $day['projectName'] = $day['type'];
        $day['length'] = strtoupper(substr($day['type'], 0, 1));
      }
      $key = $day['day'];
      $new_data[$day['employee']][$key][] = $day;
    }

    // Fill empty days with create new stub template.
    foreach ($new_data as $employee => &$row) {
      foreach ($row as $key => &$empty_day) {
        if (empty($empty_day)) {
          $empty_day[] = array(
            // Set id to new to get the proper link on angular.
            'id' => 'new',
            'type' => 'empty',
            'day' => (string) $key,
            'length' => 'E',
            'projectName' => 'Empty!',
            'employee' => $employee,
          );
        }
      }
    }
    // Multiple users.
    if (empty($request['employee'])) {
      return $new_data;
    }
    else {
      // Return single user.
      return $new_data[$request['employee']];
    }
  }

    /**
   * Add HATEOAS links to list of item.
   *
   * @param $data
   *   The data array after initial massaging.
   */
  protected function addHateoas(array &$data) {
    if (!$this->handler) {
      return;
    }
    $request = $this->handler->getRequest();

    // Get self link.
    $data['self'] = array(
      'title' => 'Self',
      'href' => $this->handler->versionedUrl($this->handler->getPath()),
    );

    $page = !empty($request['page']) ? $request['page'] : 1;

    if ($page > 1) {
      $request['page'] = $page - 1;
      $data['previous'] = array(
        'title' => 'Previous',
        'href' => $this->handler->getUrl($request),
      );
    }

    // We know that there are more pages if the total count is bigger than the
    // number of items of the current request plus the number of items in
    // previous pages.
    $items_per_page = $this->handler->getRange();
    $previous_items = ($page - 1) * $items_per_page;
    if (isset($data['count']) && $data['count'] > count($data['data']) + $previous_items) {
      $request['page'] = $page + 1;
      $data['next'] = array(
        'title' => 'Next',
        'href' => $this->handler->getUrl($request),
      );
    }

  }

  /**
   * {@inheritdoc}
   */
  public function render(array $structured_data) {
    return drupal_json_encode($structured_data);
  }

  /**
   * {@inheritdoc}
   */
  public function getContentTypeHeader() {
    return $this->contentType;
  }
}

