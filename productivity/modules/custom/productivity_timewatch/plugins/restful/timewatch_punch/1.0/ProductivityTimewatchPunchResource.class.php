<?php

/**
 * @file
 * Contains ProductivityTimewatchPunchResource.
 */

class ProductivityTimewatchPunchResource extends \ProductivityEntityBaseNode {


  /**
   * Create a new session or update an open session.
   */
  public function createEntity() {
    $request = $this->getRequest();

    $account = $this->getAccount();
    if (!node_access('create', 'work_session', $account)) {
      throw new RestfulForbiddenException('You do not have access to create work sessions.');
    }

    if (empty($request['pincode'])) {
      throw new \RestfulBadRequestException('Pincode is required');
    }

    $uid = productivity_session_get_uid_by_pincode($request['pincode']);
    if (!$uid) {
      throw new \RestfulBadRequestException('Wrong pincode');
    }
    $employee_account = user_load($uid);

    // Find an existing session with no end date.
    $query = new EntityFieldQuery();
    $result = $query
      ->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'work_session')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->fieldCondition('field_employee', 'target_id', $uid)
      ->fieldCondition('field_session_date', 'value2', NULL)
      ->range(0, 1)
      ->execute();

    if (empty($result['node'])) {
      // When there's no open session, create a new one.
      $values = array(
        'type' => 'work_session',
        'uid' => $account->uid,
        'status' => NODE_PUBLISHED,
        'title' => format_string('@date - @user', array('@date' => date('d/m/y'), '@user' => $employee_account->name)),
      );
      $node = entity_create('node', $values);
      $wrapper = entity_metadata_wrapper('node', $node);
      $wrapper->field_employee->set($uid);
      $wrapper->field_session_date->value->set(REQUEST_TIME);
      $action = 'entered';
    }
    else {
      // Otherwise set the end date of the open session.
      $wrapper = entity_metadata_wrapper('node', key($result['node']));
      $wrapper->field_session_date->value2->set(REQUEST_TIME);
      $action = 'left';
    }

    $wrapper->save();

    return array(
      'employee' => $employee_account->name,
      'action' => $action,
    );
  }
}
