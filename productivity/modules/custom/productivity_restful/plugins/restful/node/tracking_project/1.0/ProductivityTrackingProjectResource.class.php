<?php

/**
 * @file
 * Contains ProductivityTrackingResource.
 */

class ProductivityTrackingProjectResource extends \ProductivityEntityBaseNode {

  // Range is counting number of user/month.
  protected $range = 100;


  /**
   * Overrides \RestfulEntityBaseNode::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['projectID'] = array(
      'property' => 'nid',
    );

    $public_fields['totalTracking'] = array(
      'callback' => array($this, 'totalTracking')
    );

    return $public_fields;
  }

  /**
   * Static callback, total time.
   */
  function totalTracking($wrapper) {
    $request = $this->getRequest();

    return productivity_time_tracking_total_hours($wrapper->getIdentifier(), $request, $this->getAccount());
  }

  /**
   * Overrides RestfulEntityBase::getQueryForList().
   */
  public function getEntityFieldQuery() {
    $request = $this->getRequest();
    $query = parent::getEntityFieldQuery();

    if (empty($request['month']) && !intval($request['month'])) {
      throw new \RestfulBadRequestException('Invalid month given.');
    }

    if (empty($request['year']) && !intval($request['year'])) {
      throw new \RestfulBadRequestException('Invalid year given.');
    }
    $start_time =  $request['year'] . '-' . $request['month'] . '-01'. ' 00:00:00';
    $end_time = date('Y-m-d 00:00:00', strtotime('+1 month', strtotime($start_time)));

    $query->fieldCondition('field_date', 'value2', $start_time, '<=');

    return $query;
  }
}
