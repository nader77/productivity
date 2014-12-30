<?php
/**
 * @file
 * Migrate class to create Productivity content.
 */

/**
 * Class ProductivityDemoCreateProductivityContent
 */
class ProductivityMigrateTracker extends ProductivityMigrate {
  public $entityType = 'node';
  public $bundle = 'time_tracking';

  /**
   * CSV Column mapping.
   *
   * @var array
   */
  public $csvColumns = array(
    array('id', 'ID'),
    array('field_work_date', 'date'),
    array('employee', 'employee'),
    array('project', 'project'),
    array('work_length', 'work length'),
    array('length_unit', 'length unit'),//(hours/days)
    array('field_description', 'work description'),
    array('field_day_type', 'type'),
  );

  /**
   * Configure the object during creation.
   */
  public function __construct() {
    parent::__construct();

    $this->dependencies = array(
      'ProductivityMigrateUser',
      'ProductivityMigrateProject',
    );
    //  date,employee,project,work length,length unit(hours/days),work description
    $field_names = array(
      'field_description',
      'field_day_type',
    );
    $this->addSimpleMappings($field_names);

    $this->addFieldMapping('field_work_date', 'field_work_date');
    $this->addFieldMapping('field_work_date:timezone')
      ->defaultValue('Asia/Jerusalem');


    $this
      ->addFieldMapping('field_employee', 'employee')
      ->sourceMigration('ProductivityMigrateUser');

    $this
      ->addFieldMapping('field_project', 'project')
      ->sourceMigration('ProductivityMigrateProject');

    $this->addFieldMapping('field_work_length', 'work_length');
    $this->addFieldMapping('field_work_length:period', 'length_unit');
  }

  function prepare($entity, $row) {
    $wrapper = entity_metadata_wrapper('node', $entity);
    if (!$wrapper->field_work_length->value() || $wrapper->field_work_length->interval->value() == "") {
      // Prevent error on save when field is empty.
      $entity->field_work_length['und'][0]['interval'] = '0';
      $entity->field_work_length['und'][0]['period'] = 'hour';
    }
    if (!$wrapper->field_employee->value()) {
      // Prevent error on save when field is empty.
      unset($entity->field_employee);
    }
    if (!$wrapper->field_project->value()) {
      // Prevent error on save when field is empty.
      unset($entity->field_project);
    }
  }
}
