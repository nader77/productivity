<?php

/**
 * @file
 * Contains ProductivityProjectResource.
 */

class ProductivityProjectResource extends \ProductivityEntityBaseNode {


  /**
   * Overrides \RestfulEntityBaseNode::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['id'] = array(
      'property' => 'nid',
    );

    $public_fields['title'] = array(
      'property' => 'title',
    );

    return $public_fields;
  }
}
