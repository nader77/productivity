<?php

/**
 * Class ProductivityMigrateSessionTypes
 */
class ProductivityMigrateSessionTypes extends ProductivityMigrate {

  public $entityType = 'taxonomy_term';
  public $bundle = 'session_types';

  protected $extraCsvColumns = array(
    array('full_day', 'Full day'),
  );

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_full_day', 'full_day');
  }

  /**
   * Set the regular session type as the default one.
   */
  public function complete($term) {
    if ($term->name == 'Regular') {
      variable_set('productivity_timewatch_default_session_type_tid', $term->tid);
    }
  }
}
