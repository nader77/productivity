<?php

class ProductivityMigrateTrackingsToWorkSessions extends Migration {

  /**
   * Class constructor.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Copy non-regular time trackings to work session nodes.');

    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('field_employee', 'field_employee_target_id');
    $this->addFieldMapping('field_project', 'field_project_target_id');

    $this->addFieldMapping('field_session_date', 'date');
    $this->addFieldMapping('field_session_date:to', 'date');
    $this->addFieldMapping('field_session_date:timezone')
      ->defaultValue('Asia/Jerusalem');

    $this->addFieldMapping('field_session_type', 'field_day_type');
    $this->addFieldMapping('field_session_type:create_term')
      ->defaultValue(TRUE);
    $this->addFieldMapping('field_session_type:ignore_case')
      ->defaultValue(TRUE);

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
    $raw_query = "SELECT node.nid, node.created, node.changed, dt.field_day_type_value AS day_type, DATE_FORMAT(wd.field_work_date_value, '%Y-%m-%d') AS 'date', node.uid, e.field_employee_target_id AS employee_uid
              FROM node
              INNER JOIN field_data_field_day_type dt ON dt.entity_type = 'node' AND dt.entity_id = node.nid
              INNER JOIN field_data_field_work_date wd ON wd.entity_type = 'node' AND wd.entity_id = node.nid
              LEFT JOIN field_data_field_employee e ON e.entity_type = 'node' AND e.entity_id = node.nid
              WHERE type = 'time_tracking'
              AND field_day_type_value != 'regular'
              AND node.status = 1
              ORDER BY 'date'";

    $query = db_select('node', 'n');
    $query->innerJoin('field_data_field_day_type', 'dt', "dt.entity_type = 'node' AND dt.entity_id = n.nid");
    $query->innerJoin('field_data_field_work_date', 'wd', "wd.entity_type = 'node' AND wd.entity_id = n.nid");
    $query->innerJoin('field_data_field_employee', 'e', "e.entity_type = 'node' AND e.entity_id = n.nid");

    // Left join since some node will not have a project ID.
    $query->leftJoin('field_data_field_project', 'p', "p.entity_type = 'node' AND p.entity_id = n.nid");

    $query
      ->fields('n',  array('nid', 'created','changed'))
      ->fields('dt', array('field_day_type_value'))
      ->fields('e',  array('field_employee_target_id'))
      ->fields('p',  array('field_project_target_id'))
      ->fields('wd', array('field_work_date_value'))
      ->condition('dt.field_day_type_value', 'regular', '!=')
      ->condition('n.type', 'time_tracking')
      ->condition('n.status', 1)
      ->orderBy('n.created');

    $this->source = new MigrateSourceSQL($query);

    $this->destination = new MigrateDestinationNode('work_session');
  }

  /**
   *
   */
  public function prepareRow($row) {

    $row->date = $row->field_work_date_value;//str_replace('-','.', substr($row->field_work_date_value, 0, strpos($row->field_work_date_value, ' ')));

    print_r(get_object_vars($row));
//    echo "--------------fooooooooooo-------------";

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
