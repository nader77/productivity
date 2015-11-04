<?php

/**
 * @file
 * Contains ProductivityGithubPrsResource.
 */

class ProductivityGithubPrsResource extends \ProductivityEntityBaseNode {

  /**
   * Overrides \ProductivityEntityBaseNode::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['issue'] = array('property' => 'field_issue_id');

    $public_fields['project'] = array(
      'property' => 'field_project',
      'resource' => array(
        'project' => array(
          'name' => 'projects',
          'full_view' => FALSE,
        ),
      ),
    );

    return $public_fields;
  }


  /**
   * Overrides RestfulEntityBase::getQueryForList().
   */
  public function getQueryForList() {
    $request = $this->getRequest();
    // Validate parameters.
    foreach (array('day', 'month', 'year') as $required_field) {
      if (empty($request[$required_field])) {
        throw new \RestfulBadRequestException(format_string('Missing required parameter @field.', array('@field' => $required_field)));
      }
      if (!intval($request[$required_field])) {
        throw new \RestfulBadRequestException(format_string('Wrong value for @field, expected integer.', array('@field' => $required_field)));
      }

      // Make sure the integer values are cleaned.
      $request[$required_field] = intval($request[$required_field]);
    }

    $query = parent::getQueryForList();

    // Filter day.
    $this->setPushDateTimeSpan($query, '+1 day');

    // Filter employee.
    if (!$account = user_load_by_name($request['employee'])) {
      throw new \RestfulBadRequestException(format_string('Invalid employee username: @username.', array('@username' => $request['employee'])));
    }
    $query->fieldCondition('field_employee', 'target_id', $account->uid);

    return $query;
  }

  /**
   * Limit the work date to a certain time span, based on the day or month given
   * in the request.
   *
   * @param $query
   *   An entity field query object to add the work date constraint to.
   * @param $interval
   *   The span length. E.g. "+1 day" or "+1 month".
   *
   * @return array
   *   A start timestamp and an end timestamp.
   */
  protected function setPushDateTimeSpan($query, $interval) {
    list($start_time, $end_time) = $this->getTimeSpan($interval);

    $query->fieldCondition('field_push_date', 'value', $start_time, '>=');
    $query->fieldCondition('field_push_date', 'value', $end_time, '<');
  }
}
