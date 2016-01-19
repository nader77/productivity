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
    $this->setPushDateTime($query);

    // Filter employee.
    if (!$account = user_load_by_name($request['employee'])) {
      throw new \RestfulBadRequestException(format_string('Invalid employee username: @username.', array('@username' => $request['employee'])));
    }
    $query->fieldCondition('field_employee', 'target_id', $account->uid);


    // Get only pull requests.
    $query->fieldCondition('field_github_content_type', 'value', 'pull_request');

    return $query;
  }

  /**
   * Limit the push date to a certain day.
   *
   * @param $query
   *   An entity field query object to add the work date constraint to.
   */
  protected function setPushDateTime($query) {
    $request = $this->getRequest();

    // Set the work day from 00:00:00 to 23:59:59 to get all PRs in between.
    $work_day = array(
      $request['year'] . '-' . $request['month'] . '-' . $request['day'] . ' 00:00:00',
      $request['year'] . '-' . $request['month'] . '-' . $request['day'] . ' 23:59:59',
    );

    $query->fieldCondition('field_push_date', 'value', $work_day, 'BETWEEN');
  }
}
