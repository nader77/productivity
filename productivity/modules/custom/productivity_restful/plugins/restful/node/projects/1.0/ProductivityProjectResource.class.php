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

    $public_fields['name'] = array(
      'property' => 'title',
    );
    return $public_fields;
  }
}
