<?php

class ProductivityMigrateTrackingsToWorkSessions extends Migration {

  /**
   * Class constructor.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Copy non-regular time tracking to work session nodes.');

    $this->addFieldMapping('field_employee', 'field_employee_target_id');
    $this->addFieldMapping('field_project', 'field_project_target_id');
    $this->addFieldMapping('field_special_day_name', 'field_description_value');

    $this->addFieldMapping('field_session_date', 'date');
    $this->addFieldMapping('field_session_date:to', 'enddate');
    $this->addFieldMapping('field_session_date:timezone')
      ->defaultValue('Asia/Jerusalem');

    $this->addFieldMapping('field_session_type', 'field_day_type_value');

    // Create a map object for tracking the relationships between source rows.
    $key = array(
      'nid' => array(
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
      ),
    );

    $this->map = new MigrateSQLMap($this->machineName, $key, MigrateDestinationNode::getKeySchema());

    // Fetch all time tracking nodes with type different than 'regular'.
    $query = db_select('node', 'n');
    $query->leftJoin('field_data_field_day_type', 'dt', "dt.entity_type = 'node' AND dt.entity_id = n.nid");
    $query->leftJoin('field_data_field_vacation_type', 'vt', "vt.entity_type = 'node' AND vt.entity_id = n.nid");
    $query->leftJoin('field_data_field_work_date', 'wd', "wd.entity_type = 'node' AND wd.entity_id = n.nid");
    $query->leftJoin('field_data_field_employee', 'e', "e.entity_type = 'node' AND e.entity_id = n.nid");
    $query->leftJoin('field_data_field_description', 'd', "d.entity_type = 'node' AND d.entity_id = n.nid");

    // Left join since some node will not have a project ID.
    $query->leftJoin('field_data_field_project', 'p', "p.entity_type = 'node' AND p.entity_id = n.nid");

    $query
      ->fields('n',  array('nid', 'created','changed'))
      ->fields('dt', array('field_day_type_value'))
      ->fields('vt', array('field_vacation_type_value'))
      ->fields('e',  array('field_employee_target_id'))
      ->fields('p',  array('field_project_target_id'))
      ->fields('wd', array('field_work_date_value'))
      ->fields('d', array('field_description_value'))
      ->condition('dt.field_day_type_value', 'regular', '!=')
      ->condition('n.type', 'time_tracking')
      ->condition('n.status', 1)
      ->orderBy('n.created');

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('work_session');
  }

  public function prepare($row, $entity) {
    $row->stop = 0;
  }
  /**
   * Convert string to taxonomy.
   */
  public function prepareRow($row) {
    // Convert to 9:00am on same day.
    $re = "/(....-..-..) .*/";
    $str = $row->field_work_date_value;
    // Create formated dates for all options.
    $subst = "$1 09:00:00";
    $end_subst = "$1 18:00:00";
    $end_subst_half = "$1 13:30:00";
    $date = preg_replace($re, $subst, $str, 1);
    $end_date = preg_replace($re, $end_subst, $str, 1);
    $end_subst_half = preg_replace($re, $end_subst_half, $str, 1);

    $row->date = $date;
    if ($row->field_vacation_type_value == 'halfday') {
      $row->enddate = $end_subst_half;
    }
    else {
      // Set end time to 18:00.
      $row->enddate = $end_date;
    }
    // Convert type to taxonomy term name.
    $type_term = taxonomy_get_term_by_name($row->field_day_type_value, 'session_types');
    $type_term = reset($type_term);
    $row->field_day_type_value = $type_term->name;

  }

  /**
   * Filter the destiny field ID.
   *
   * @param array $dest_field
   *   The destiny field settings.
   *
   * @return array
   *   The filtered array.
   */
  protected function filterDestid2FromEntityReference($dest_field) {
    $filtered_ids = array();

    if (!empty($dest_field['destid1'])) {
      $filtered_ids = array('destid1' => $dest_field['destid1']);
      if (!empty($dest_field['destid2'])) {
        $filtered_ids['destid2'] = $dest_field['destid2'];
      }
    }
    elseif (is_array($dest_field)) {
      foreach ($dest_field as $key => $dest) {
        $filtered_ids[$key] = array('destid1' => $dest['destid1']);
        if (!empty($dest['destid2'])) {
          $filtered_ids[$key]['destid2'] = $dest['destid2'];
        }
      }
    }

    return $filtered_ids;
  }
}
