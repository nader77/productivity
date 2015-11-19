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
    );

    $public_fields['end'] = array(
      'property' => 'field_session_date',
      'sub_property' => 'value2',
    );

    $public_fields['employee'] = array(
      'property' => 'field_employee',
      'sub_property' => 'name',
    );

    return $public_fields;
  }
}
