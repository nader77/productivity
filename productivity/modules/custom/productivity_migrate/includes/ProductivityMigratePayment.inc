<?php
/**
 * @file
 * Migrate class to create Productivity content.
 */

/**
 * Class ProductivityMigratePayment
 */
class ProductivityMigratePayment extends ProductivityMigrate {
  public $entityType = 'node';
  public $bundle = 'payment';

  /**
   * CSV Column mapping.
   *
   * @var array
   */
  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'Title'),
    array('field_project', 'project'),
    array('amount', 'amount'),
    array('currency', 'currency'),
    array('field_date_expected', 'Date expected'),
    array('field_date_actual', 'Date actual'),
  );

  /**
   * Configure the object during creation.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->dependencies = array(
      'ProductivityMigrateProject',
    );


    $this->addFieldMapping('field_date_expected', 'field_date_expected');
    $this->addFieldMapping('field_date_expected:timezone')
      ->defaultValue('Asia/Jerusalem');

    $this->addFieldMapping('field_date_actual', 'field_date_actual');
    $this->addFieldMapping('field_date_actual:timezone')
      ->defaultValue('Asia/Jerusalem');


    $this
      ->addFieldMapping('field_project', 'field_project')
      ->sourceMigration('ProductivityMigrateProject');

  }


  public function prepare($entity, $current_row) {
    $wrapper = entity_metadata_wrapper('node', $entity);
    $wrapper->field_amount->amount->set($current_row->amount);
    $wrapper->field_amount->currency->set($current_row->currency);
  }
}
