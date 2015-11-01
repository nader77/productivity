<?php

/**
 * @file
 * Contains ProductivityTrackingResource.
 */

class ProductivityTrackingResource extends \ProductivityEntityBaseNode {

  // Range is counting number of user/month.
  protected $range = 25;


  /**
   * Overrides \ProductivityEntityBaseNode::publicFieldsInfo().
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
    );

    $public_fields['type'] = array(
      'property' => 'field_day_type',
    );

    $public_fields['description'] = array(
      'property' => 'field_description',
    );

    $public_fields['issues'] = array(
      'property' => 'field_issues_logs',
      'process_callbacks' => array(
        array($this, 'getIssues'),
      ),
    );

    $public_fields['editLink'] = array(
      'property' => 'nid',
      'process_callbacks' => array(
        array($this, 'getLink'),
      ),
    );

    $public_fields['status'] = array(
      'property' => 'status',
    );

    return $public_fields;
  }

  /**
   *  Get a list of issues.
   *
   * Each time-tracking node has multiple issues, each one contains reference
   * to the GitHub issue node, label, time and type.
   *
   * @param $value
   *  The list of issues and the fields of each one.
   *
   * @return array
   *  Clean list of issues.
   */
  protected function getIssues($value) {
    $issues = array();
    foreach ($value as $issue) {
      // We cannot use `wrapper` on the sub-fields of a multi-field.
      $issues[] = array(
        'issue' => $issue->field_github_issue[LANGUAGE_NONE][0]['target_id'],
        'label' => $issue->field_issue_label[LANGUAGE_NONE][0]['value'],
        'type' => $issue->field_issue_type[LANGUAGE_NONE][0]['value'],
        // Need to convert the value to a decimal number to be accepted by the
        // HTML5 input field.
        'time' => (float) number_format($issue->field_time_spent[LANGUAGE_NONE][0]['value'], 2),
      );
    }

    return $issues;
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
    $request = $this->getRequest();
    $query = new EntityFieldQuery();
    $uids = productivity_user_get_active_uids($request['month'], $request['year']);

    $query->entityCondition('entity_type', 'user');
    if ($uids) {
      // Load active users for the date that have developer or QA job type.
      $query->propertyCondition('uid', $uids, 'IN');
    }
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
    $global_day = array('holiday', 'funday', 'holiday', 'special');
    if (!empty($request['global'])) {
      $query->fieldCondition('field_day_type', 'value', $global_day, 'IN');
    }
    else {
      $query->fieldCondition('field_day_type', 'value', $global_day, 'NOT IN');
    }

    $this->setWorkDateTimeSpan($query, '+1 month');

    if (!empty($request['employee'])) {
      $user_by_name = user_load_by_name($request['employee']);
      if (!$user_by_name) {
        throw new \RestfulBadRequestException('Invalid username given.');
      }
      $query->fieldCondition('field_employee', 'target_id', $user_by_name->uid);
    }

    return $query;
  }

  /**
   * Set properties of the entity based on the request, and save the entity.
   * Override the base function until the issue is fix
   * https://github.com/RESTful-Drupal/restful/pull/379/
   */
  protected function setPropertyValues(EntityMetadataWrapper $wrapper, $null_missing_fields = FALSE) {
    $request = $this->getRequest();
    if (($request['type'] == 'regular') && (!isset($request['issues']) || empty($request['issues']))) {
      throw new \RestfulBadRequestException('At least one issue should be added.');
    }

    $wrapper->field_work_date->set($request['date']);
    $wrapper->field_day_type->set($request['type']);
    $wrapper->field_employee->set(user_load_by_name($request['employee']));

    if ($request['type'] == 'regular') {
      if (empty($request['length'])) {
        throw new \RestfulBadRequestException('Invalid length given.');
      }

      $wrapper->field_project->set($request['projectID']);
      $wrapper->field_track_hours->set($request['length']);

      $field_issues = array();
      // Mandatory fields in each issue logged in any given "time-tracking".
      $mandatory_fields = array(
        'label',
        'time',
        'type',
      );
      foreach ($request['issues'] as $issue) {
        // Check that none of the required variables for each issue is missing.
        foreach ($mandatory_fields as $field_name) {
          if (!$issue[$field_name]) {
            throw new \RestfulBadRequestException("Please fill the $field_name in all the issues.");
          }
        }
        // Cannot use the `wrapper` on the sub-fields of a multi-field.
        $field_issues[] = array(
          'field_github_issue' => array(LANGUAGE_NONE => array(array('target_id' => $issue['issue']))),
          'field_issue_label' => array(LANGUAGE_NONE => array(array('value' => $issue['label']))),
          'field_issue_type' => array(LANGUAGE_NONE => array(array('value' => $issue['type']))),
          'field_time_spent' => array(LANGUAGE_NONE => array(array('value' => $issue['time']))),
        );
      }

      $wrapper->field_issues_logs->set($field_issues);
    }

    // Change status if it's sent with the request.
    if (isset($request['status'])) {
      $wrapper->status->set($request['status']);
    }

    // Allow changing the entity just before it's saved. For example, setting
    // the author of the node entity.
    $this->entityPreSave($wrapper);

    $this->entityValidate($wrapper);

    $wrapper->save();
  }
}
