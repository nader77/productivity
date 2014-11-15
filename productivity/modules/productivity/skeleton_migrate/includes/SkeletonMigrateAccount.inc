<?php
/**
 * @file
 * Migrate class to create Skeleton content.
 */

/**
 * Class SkeletonDemoCreateSkeletonContent
 */
class SkeletonMigrateAccount extends SkeletonMigrate {
  public $entityType = 'node';
  public $bundle = 'account';

  /**
   * CSV Column mapping.
   *
   * @var array
   */
  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'Title'),
  );

  /**
   * Configure the object during creation.
   */
  public function __construct() {
    parent::__construct();

  }

}
