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

    $public_fields['projectName'] = array(
      'property' => 'field_project',
      'sub_property' => 'title',
    );

    $public_fields['projectID'] = array(
      'property' => 'field_project',
      'sub_property' => 'nid',
    );

    $public_fields['lengthHours'] = array(
      'property' => 'field_track_hours',
      'process_callbacks' => array(
        array($this, 'imageProcess'),
      ),
    );

    $public_fields['lengthDays'] = array(
      'property' => 'field_track_hours',
    );

    return $public_fields;
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

    return $query;
  }
}
