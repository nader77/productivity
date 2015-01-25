<?php

/**
 * @file
 * Contains ProductivityTrackingResource.
 */

class ProductivityTrackingResource extends \ProductivityEntityBaseNode {

  // Range is counting number of user/month.
  protected $range = 25;


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

    $public_fields['date'] = array(
      'property' => 'field_work_date',
    );

    $public_fields['employee'] = array(
      'property' => 'field_employee',
      'sub_property' => 'name',
    );

    $public_fields['projectName'] = array(
      'property' => 'field_project',
      'sub_property' => 'title',
    );

    $public_fields['projectID'] = array(
      'property' => 'field_project',
      'sub_property' => 'nid',
    );

    $public_fields['length'] = array(
      'property' => 'field_track_hours',
      'sub_property' => 'interval',
      'init_field' => TRUE,
    );

    $public_fields['type'] = array(
      'property' => 'field_day_type',
    );

    $public_fields['description'] = array(
      'property' => 'field_description',
    );

    $public_fields['editLink'] = array(
      'property' => 'nid',
      'process_callbacks' => array(
        array($this, 'getLink'),
      ),
    );

    return $public_fields;
  }

  /**
   * Get edit link to node.
   * @param $value
   * @return string
   */
  protected function getLink($value) {
    return url('node/' . $value, array('absolute' => TRUE));
  }

  /**
   * Return the day date clean.
   * @param $value
   * @return bool|string
   */
  protected function getDay($value) {
    return date('d', $value);
  }

  /**
   * Override the count query.
   * {@inheritdoc}
   */
  public function getQueryCount() {
    $query = $this->getUserQuery();
    $query->addTag('restful_count');
    return $query->count();
  }

  /**
   * Get base query for pager and count functions.
   * @return EntityFieldQuery
   */
  protected function getUserQuery() {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'user')
    // Don't get admin user.
      ->propertyCondition('uid', array(0, 1), 'NOT IN');

    // TODO: We need to add a condition to get only active user for the month
    // request. ie. The time the employee was working at the company.
    return $query;
  }

  /**
   * Get users in pager.
   */
  public function getUserInPager() {
    list($offset, $range) = $this->parseRequestForListPagination();

    // Get list of user to get for the current pager.
    $user_query = $this->getUserQuery();
    $user_query->range($offset, $range);
    $result = $user_query->execute();

    if (empty($result['user'])) {
      throw new \RestfulBadRequestException('No item in the given pager.');
    }

    return array_keys($result['user']);
  }

  /**
   * @param EntityFieldQuery $query
   */
  protected function queryForListPagination(\EntityFieldQuery $query) {
    $request = $this->getRequest();
    // No need for pager when returning a single employee data, or globals.
    if (!empty($request['employee']) || !empty($request['global'])) {
      return;
    }
    // Get only the users for the current pager.
    $query->fieldCondition('field_employee', 'target_id', $this->getUserInPager(), 'IN');
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
    $global_day = array('holiday', 'funday', 'holiday', 'special');
    if (!empty($request['global'])) {
      $query->fieldCondition('field_day_type', 'value', $global_day, 'IN');
    }
    else {
      $query->fieldCondition('field_day_type', 'value', $global_day, 'NOT IN');
    }

    if (!empty($request['employee'])) {
      $user_by_name = user_load_by_name($request['employee']);
      if (!$user_by_name) {
        throw new \RestfulBadRequestException('Invalid username given.');
      }
      $query->fieldCondition('field_employee', 'target_id', $user_by_name->uid);
    }

    $start_timestamp =  $request['year'] . '-' . $request['month'] . '-01'. ' 00:00:00';
    $end_timestamp = date('Y-m-d 00:00:00', strtotime('+1 month', strtotime($start_timestamp)));
    $query->fieldCondition('field_work_date', 'value', $start_timestamp, '>=');
    $query->fieldCondition('field_work_date', 'value', $end_timestamp, '<');

    return $query;
  }

  /**
   * Set properties of the entity based on the request, and save the entity.
   * Override the base function until the issue is fix
   * https://github.com/RESTful-Drupal/restful/pull/379/
   */
  protected function setPropertyValues(EntityMetadataWrapper $wrapper, $null_missing_fields = FALSE) {
    $request = $this->getRequest();

    $wrapper->field_work_date->set($request['date']);
    $wrapper->field_day_type->set($request['type']);
    $wrapper->field_employee->set(user_load_by_name($request['employee']));

    if ($request['type'] == 'regular') {
      $wrapper->field_project->set($request['projectID']);
      $wrapper->field_description->set($request['description']);
      $wrapper->field_track_hours->set($request['length']);
    }

    // Allow changing the entity just before it's saved. For example, setting
    // the author of the node entity.
    $this->entityPreSave($wrapper);

    $this->entityValidate($wrapper);

    $wrapper->save();
  }
}
