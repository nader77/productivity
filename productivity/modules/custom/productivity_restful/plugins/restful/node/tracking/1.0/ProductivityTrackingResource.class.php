<?php

/**
 * @file
 * Contains ProductivityTrackingResource.
 */

class ProductivityTrackingResource extends \ProductivityEntityBaseNode {

  protected $range = 600;


  /**
   * Overrides \RestfulEntityBaseNode::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['day'] = array(
      'property' => 'field_work_date',
      'process_callbacks' => array(
        array($this, 'getDay'),
      ),
    );

    $public_fields['employee'] = array(
      'property' => 'field_employee',
      'sub_property' => 'name',
    );
    $public_fields['projectName'] = array(
      'property' => 'field_project',
      'sub_property' => 'title',
    );
    $public_fields['length'] = array(
      'property' => 'field_work_length',
    );
    $public_fields['type'] = array(
      'property' => 'field_day_type',
    );

    $public_fields['editLink'] = array(
      'property' => 'nid',
      'process_callbacks' => array(
        array($this, 'getLink'),
      ),
    );

    return $public_fields;
  }
  protected function getLink($value) {
    return url('node/' . $value, array('absolute' => TRUE));
  }
  protected function getDay($value) {
    return date('d', $value);
  }

  /**
   * Overrides RestfulEntityBase::getQueryForList().
   *
   * Expose only published nodes.
   */
  public function getQueryForList() {
    $request = $this->getRequest();
    $query = parent::getQueryForList();

    if (empty($request['month']) && !intval($request['month'])) {
      throw new \RestfulBadRequestException('Invalid month given.');
    }

    if (empty($request['year']) && !intval($request['year'])) {
      throw new \RestfulBadRequestException('Invalid year given.');
    }

    $start_timestamp =  $request['year'] . '-' . $request['month'] . '-01'. ' 00:00:00';
    $end_timestamp = date('Y-m-d 00:00:00', strtotime('+1 month', strtotime($start_timestamp)));
    $query->fieldCondition('field_work_date', 'value', $start_timestamp, '>=');
    $query->fieldCondition('field_work_date', 'value', $end_timestamp, '<');

    return $query;
  }
}
