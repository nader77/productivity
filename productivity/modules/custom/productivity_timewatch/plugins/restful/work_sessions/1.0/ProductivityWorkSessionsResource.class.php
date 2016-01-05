<?php

/**
 * @file
 * Contains ProductivityWorkSessionsResource.
 */

class ProductivityWorkSessionsResource extends \ProductivityEntityBaseNode {

  /**
   * Overrides \RestfulDataProviderEFQ::controllersInfo().
   */
  public static function controllersInfo() {
    return array(
      '' => array(
        \RestfulInterface::POST => 'createOrUpdateWorkSession',
      ),
    );
  }

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

    return $public_fields;
  }

  /**
   * Create a new session or update an open session.
   */
  public function createOrUpdateWorkSession($uid = NULL) {
    $request = $this->getRequest();

    if (!$uid) {
      $account = $this->getAccount();

      if (!user_access('create work_session content')) {
        throw new RestfulForbiddenException('No punch access.');
      }

      $uid = $account->uid;
    }

    $project_node = NULL;
    if (!empty($request['project'])) {
      $project_node = node_load(intval($request['project']));
      if (!$project_node || $project_node->type != 'project') {
        throw new \RestfulBadRequestException(format_string('Invalid project ID #@project', array('@project' => $request['project'])));
      }
    }

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
      );
      $node = entity_create('node', $values);
      $wrapper = entity_metadata_wrapper('node', $node);
      $wrapper->field_employee->set($uid);
      $wrapper->field_session_date->value->set(REQUEST_TIME);
      if ($project_node) {
        $wrapper->field_project->set($project_node->nid);
      }
    }
    else {
      // Otherwise set the end date of the open session.
      $wrapper = entity_metadata_wrapper('node', key($result['node']));
      $wrapper->field_session_date->value2->set(REQUEST_TIME);
    }

    $wrapper->save();

    return $this->viewEntity($wrapper->getIdentifier());
  }
}
