<?php

/**
 * @file
 * Contains ProductivityWorkSessionsResource.
 */

class ProductivityWorkSessionsResource extends \ProductivityEntityBaseNode {

  /**
   * Overrides \ProductivityEntityBaseNode::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['start'] = array(
      'property' => 'field_session_date',
      'sub_property' => 'value',
      'process_callbacks' => array('intval'),
    );

    $public_fields['end'] = array(
      'property' => 'field_session_date',
      'sub_property' => 'value2',
      'process_callbacks' => array('intval'),
    );

    $public_fields['employee'] = array(
      'property' => 'field_employee',
      'sub_property' => 'name',
    );

    $public_fields['project'] = array(
      'property' => 'field_project',
      'resource' => array(
        'project' => array(
          'name' => 'projects',
        ),
      ),
    );

    $public_fields['change_date'] = array(
      'property' => 'changed',
      'process_callbacks' => array('intval'),
    );

    return $public_fields;
  }

  /**
   * Overrides RestfulEntityBase::getEntityFieldQuery.
   *
   * When there's a year and a month defined in the request, Filter projects which their end date is bigger,
   * Which will return all projects that are still active in this time.
   */
  public function getEntityFieldQuery() {
    $query = parent::getEntityFieldQuery();
    $request = $this->getRequest();

    if (empty($request['year']) || empty($request['month'])) {
      return $query;
    }

    $start_time = strtotime(intval($request['year']) . '-' . intval($request['month']) . '-01 00:00:00');
    $end_time = strtotime('+1 month', $start_time);

    $query
      ->fieldCondition('field_session_date', 'value', $start_time, '>=')
      ->fieldCondition('field_session_date', 'value', $end_time, '<=');

    return $query;
  }
}
