<?php
/**
 * @file
 * Migrate class to create Productivity content.
 */

/**
 * Class ProductivityMigrateGithubIssue
 */
class ProductivityMigrateGithubIssue extends ProductivityMigrate {
  public $entityType = 'node';
  public $bundle = 'github_issue';

  /**
   * CSV Column mapping.
   *
   * @var array
   */
  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'Title'),
    array('body', 'Description'),
    array('field_github_project_id', 'GitHub Project ID'),
    array('field_issue_id', 'Issue ID'),
    array('field_push_date', 'Push Date'),
    array('field_employee', 'Employee'),
    array('field_project', 'Project'),
    array('field_time_estimate', 'Time Estimate'),
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

    $field_names = array(
      'body',
      'field_github_project_id',
      'field_issue_id',
      'field_push_date',
      'field_pr_status',
      'field_time_estimate',
    );
    $this->addSimpleMappings($field_names);

    $this
      ->addFieldMapping('field_employee', 'field_employee')
      ->sourceMigration('ProductivityMigrateUser');

    $this
      ->addFieldMapping('field_project', 'field_project')
      ->sourceMigration('ProductivityMigrateProject');
  }
}
