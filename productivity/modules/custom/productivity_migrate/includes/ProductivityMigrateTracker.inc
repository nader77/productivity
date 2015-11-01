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
    array('field_track_hours', 'work length'),
    array('length_unit', 'length unit'),//(hours/days)
    array('field_description', 'work description'),
    array('field_day_type', 'type'),
  );

  /**
   * Configure the object during creation.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->dependencies = array(
      'ProductivityMigrateUser',
      'ProductivityMigrateProject',
    );
    //  date,employee,project,work length,length unit(hours/days),work description
    $field_names = array(
      'field_description',
      'field_day_type',
      'field_track_hours',
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

  }

  function prepare($entity, $row) {
    $wrapper = entity_metadata_wrapper('node', $entity);
    if ($row->length_unit == 'days' || $row->length_unit == 'day') {
      // Multiply by 8 if days.
      $row->field_track_hours *= 8;
    }
    if ($row->length_unit == "" &&  $row->field_track_hours == '1') {
      $row->field_track_hours = 8;
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
