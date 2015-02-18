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

    return $public_fields;
  }

  /**
   * Overrides RestfulEntityBase::getEntityFieldQuery.
   *
   * When there's a year and a month defined in the request, Filter projects which their end date is bigger,
   * Which will return all projects that are still active in this time.
   */
  public function getEntityFieldQuery() {
    $query = parent::getEntityFieldQuery();
    $request = $this->getRequest();

    if (!empty($request['year']) && !empty($request['month'])) {
      $timestamp =  $request['year'] . '-' . $request['month'] . '-01'. ' 00:00:00';
      $query->fieldCondition('field_date', 'value2', $timestamp, '>=');
    }

    return $query;
  }
}
