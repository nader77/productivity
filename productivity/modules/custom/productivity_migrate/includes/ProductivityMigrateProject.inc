<?php
/**
 * @file
 * Migrate class to create Productivity content.
 */

/**
 * Class ProductivityDemoCreateProductivityContent
 */
class ProductivityMigrateProject extends ProductivityMigrate {
  public $entityType = 'node';
  public $bundle = 'project';

  /**
   * CSV Column mapping.
   *
   * @var array
   */
  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'Title'),
    array('date_start', 'Date start'),
    array('date_end', 'Date end'),
    array('account', 'Account'),
    array('field_type', 'Type'),
    array('field_rate_type', 'Rate type'),
    array('rate', 'Rate'),
    array('rate_currency', 'Rate Currency'),
    array('scope', 'Scope'),
    array('scope_unit', 'Scope unit'),
    array('field_status', 'Status'),
  );

  /**
   * Configure the object during creation.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->dependencies = array(
      'ProductivityMigrateAccount',
    );

    $field_names = array(
      'field_type',
      'field_rate_type',
      'field_status',
    );
    $this->addSimpleMappings($field_names);

    $this->addFieldMapping('field_date', 'date_start');
    $this->addFieldMapping('field_date:to', 'date_end');
    $this->addFieldMapping('field_date:timezone')
      ->defaultValue('Asia/Jerusalem');


    $this
      ->addFieldMapping('field_account', 'account')
      ->sourceMigration('ProductivityMigrateAccount');

//    $this->addFieldMapping('field_rate:amount', 'rate');
//    $this->addFieldMapping('field_rate:currency', 'rate_currency');

    $this->addFieldMapping('field_scope', 'scope');
    $this->addFieldMapping('field_scope:period', 'scope_unit');
  }


  public function prepare($entity, $current_row) {
    $wrapper = entity_metadata_wrapper('node', $entity);
    $wrapper->field_rate->amount->set($current_row->rate);
    $wrapper->field_rate->currency->set($current_row->rate_currency);
  }
}
