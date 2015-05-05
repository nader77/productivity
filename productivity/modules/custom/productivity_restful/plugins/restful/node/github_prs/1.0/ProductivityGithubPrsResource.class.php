<?php

/**
 * @file
 * Contains ProductivityGithubPrsResource.
 */

class ProductivityGithubPrsResource extends \ProductivityEntityBaseNode {

  /**
   * Overrides \RestfulEntityBaseNode::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['issueId'] = array('property' => 'field_issue_id');

    return $public_fields;
  }


  /**
   * Overrides RestfulEntityBase::getQueryForList().
   */
  public function getEntityFieldQuery() {
    $request = $this->getRequest();
    // Validate parameters.
    foreach (array('day', 'month', 'year', 'project_id') as $required_field) {
      if (empty($request[$required_field]) && !intval($request[$required_field])) {
        throw new \RestfulBadRequestException(t('Invalid @field', array('@field' => $required_field)));
      }
      $request[$required_field] = intval($request[$required_field]);
    }

    $query = parent::getEntityFieldQuery();

    // Filter day.
    $start_timestamp =  $request['year'] . '-' . $request['month'] . '-' . $request['day'] . ' 00:00:00';
    $end_timestamp = date('Y-m-d 00:00:00', strtotime('+1 day', strtotime($start_timestamp)));
    $query->fieldCondition('field_work_date', 'value', $start_timestamp, '>=');
    $query->fieldCondition('field_work_date', 'value', $end_timestamp, '<');

    // Filter project.
    $query->fieldCondition('field_project', 'target_id', $request['project_id']);

    // Filter employee.
    if (!$account = user_load_by_name(check_plain($request['employee']))) {
      throw new \RestfulBadRequestException(t('Invalid username'));
    }
    $query->fieldCondition('field_employee', 'target_id', $account->uid);

    return $query;
  }

}
