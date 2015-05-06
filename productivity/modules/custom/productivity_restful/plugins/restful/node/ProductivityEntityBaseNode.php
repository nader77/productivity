<?php

/**
 * @file
 * Contains \ProductivityEntityBaseNode.
 */

abstract class ProductivityEntityBaseNode extends \RestfulEntityBaseNode {

  /**
   * Overrides \RestfulEntityBaseNode::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    unset($public_fields['self']);

//    if (field_info_instance($this->getEntityType(), OG_AUDIENCE_FIELD, $this->getBundle())) {
//      $public_fields['tracking'] = array(
//        'property' => OG_AUDIENCE_FIELD,
//        'resource' => array(
//          'time_tracking' => array(
//            'name' => 'tracking',
//            'full_view' => FALSE,
//          )
//        ),
//      );
//    }

    return $public_fields;
  }

  /**
   * Process callback, Remove Drupal specific events from the image array.
   *
   * @param array $value
   *   The image array.
   *
   * @return array
   *   A cleaned image array.
   */
  protected function imageProcess($value) {
    if (static::isArrayNumeric($value)) {
      $output = array();
      foreach ($value as $item) {
        $output[] = $this->imageProcess($item);
      }
      return $output;
    }
    return array(
      'id' => $value['fid'],
      'self' => file_create_url($value['uri']),
      'filemime' => $value['filemime'],
      'filesize' => $value['filesize'],
      'width' => $value['width'],
      'height' => $value['height'],
      'styles' => $value['image_styles'],
    );
  }

  /**
   * Limit a query to a certain time span, based on the day or month given in
   * the request.
   *
   * @param $query
   *   An entity field query object to add the work date constrain to.
   * @param $interval
   *   The span length. E.g. "+1 day" or "+1 month".
   *
   * @return array A start timestamp and an end timestamp.
   * A start timestamp and an end timestamp.
   */
  protected function setWorkDateTimeSpan($query, $interval) {
    $request = $this->getRequest();

    $day = isset($request['day']) ? $request['day'] : '01';
    $start_time =  $request['year'] . '-' . $request['month'] . '-' . $day . ' 00:00:00';
    $end_time = date('Y-m-d 00:00:00', strtotime($interval, strtotime($start_time)));

    $query->fieldCondition('field_work_date', 'value', $start_time, '>=');
    $query->fieldCondition('field_work_date', 'value', $end_time, '<');
  }
}
