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

    return $public_fields;
  }


  /**
   * Overrides RestfulEntityBase::getQueryForList().
   */
  public function getQueryForList() {
    $request = $this->getRequest();
    // Validate parameters.
    foreach (array('day', 'month', 'year', 'project_id') as $required_field) {
      if (empty($request[$required_field])) {
        throw new \RestfulBadRequestException(format_string('Missing required parameter @field.', array('@field' => $required_field)));
      }
      if (intval($request[$required_field]) != $request[$required_field]) {
        throw new \RestfulBadRequestException(format_string('Wrong value for @field, expected integer.', array('@field' => $required_field)));
      }

      // Make sure the integer values are cleaned.
      $request[$required_field] = intval($request[$required_field]);
    }

    $query = parent::getQueryForList();

    // Filter day.
    $this->setWorkDateTimeSpan($query, '+1 day');

    // Filter project.
    $query->fieldCondition('field_project', 'target_id', $request['project_id']);

    // Filter employee.
    if (!$account = user_load_by_name($request['employee'])) {
      throw new \RestfulBadRequestException(format_string('Invalid employee username: @username.', array('@username' => $request['employee'])));
    }
    $query->fieldCondition('field_employee', 'target_id', $account->uid);

    return $query;
  }

}
