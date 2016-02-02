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
  }

  /**
   * Save the multifield data.
   */
  public function prepare($node, $current_row) {
    // Update scope type to be hard coded dev
    $node->field_table_rate[LANGUAGE_NONE][0]['field_issue_type'][LANGUAGE_NONE][0]['value'] = 'dev';
    // Update scope interval from global scope interval
    $node->field_table_rate[LANGUAGE_NONE][0]['field_scope'][LANGUAGE_NONE][0]['interval'] = $current_row->scope;
    // Update scope period from global scope period
    $node->field_table_rate[LANGUAGE_NONE][0]['field_scope'][LANGUAGE_NONE][0]['period'] = $current_row->scope_unit;
    // Update scope rate amount from global rate amount
    $node->field_table_rate[LANGUAGE_NONE][0]['field_rate'][LANGUAGE_NONE][0]['amount'] = $current_row->rate;
    // Update scope rate currency from global rate currency
    $node->field_table_rate[LANGUAGE_NONE][0]['field_rate'][LANGUAGE_NONE][0]['currency'] =$current_row->rate_currency;

    $node->field_table_rate[LANGUAGE_NONE][0]['field_rate_type'][LANGUAGE_NONE][0]['value'] =$current_row->field_rate_type;
  }
}
