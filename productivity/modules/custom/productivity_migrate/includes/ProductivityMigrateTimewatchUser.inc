<?php

class ProductivityMigrateTimewatchUser extends Migration {
  public $entityType = 'user';

  /**
   * CSV Columns.
   */
  public $csvColumns = array(
    array('name', 'name'),
    array('mail', 'mail'),
    array('pass', 'pass'),
  );

  /**
   * Configure the object during creation.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->description = t('Import users from CSV file.');
    // Create a map object for tracking the relationships between source rows.
    $key = array(
      'name' => array(
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
      ),
    );
    $this->map = new MigrateSQLMap($this->machineName, $key, MigrateDestinationEntityAPI::getKeySchema('user'));

    // Create a MigrateSource object.
    $csv = drupal_get_path('module', 'productivity_migrate') . '/csv/user/timewatch.csv';

    $this->source = new MigrateSourceCSV($csv, $this->csvColumns, array('header_rows' => 1));
    $this->destination = new MigrateDestinationUser();

    $this->addSimpleMappings(array('name', 'mail', 'pass'));

    $role = user_role_load_by_name('timewatch');
    $this
      ->addFieldMapping('roles')
      ->defaultValue(array($role->rid));
  }
}
