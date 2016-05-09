<?php
/**
 * @file
 * template.php
 */

/**
 * Node preprocess.
 */
function bootstrap_subtheme_preprocess_node(&$variables) {
  $node = $variables['node'];
  $view_mode = $variables['view_mode'];
  $variables['theme_hook_suggestions'][] = "node__{$node->type}__{$view_mode}";
  $preprocess_function = "bootstrap_subtheme_preprocess_node__{$node->type}__{$view_mode}";
  if (function_exists($preprocess_function)) {
    $preprocess_function($variables);
  }
}

/**
 * Preprocess Project node.
 */
function bootstrap_subtheme_preprocess_node__project__full(&$variables) {
  // use node because wrapper don't work with multifield.
  $node = $variables['node'];
  $wrapper = entity_metadata_wrapper('node', $node);
  $variables['days'] = productivity_project_get_total_days($wrapper->field_hours->value());

  $rows = array();
  $variables['table'] = _bootstrap_subtheme_create_rate_table($node, $wrapper, $rows);
  $variables['recalculate_hours_days_link'] = l(t('Recalculate project\'s hours & days.'), 'recalculate-project-time/' . $node->nid);

  $year = date('Y');
  $month = date('m', strtotime("-1 month"));
  $project_id = $node->nid;
  $variables['monthly_report_link'] = l(t('Monthly report'), "/monthly-report/$project_id/$year/$month");

  // Add charts.
  module_load_include('inc', 'productivity_github', 'productivity_github.table');
  $variables['per_issue_table'] = productivity_github_time_display_tracking_issue_table($project_id, FALSE);

  $chart = productivity_project_get_developer_chart($node);
  $variables['developer_chart'] = drupal_render($chart);

  $chart = _bootstrap_subtheme_get_hours_type_chart($rows);
  $variables['hours_chart'] = drupal_render($chart);

  $variables['total_budget'] = productivity_project_get_total_budget($wrapper);

  $variables['project_scope'] = productivity_project_get_scope($wrapper);

  $display = array('settings' => array('format_type' => 'short'));
  $field = field_view_field('node', $node, 'field_date', $display);
  $variables['project_date_start'] = render($field);

  $fields = array(
    'field_milestone',
    'field_date',
    'field_scope'
  );
  $variables['milestones'] = _bootstrap_subtheme_rendered_field_array($wrapper, $fields);

  $fields = array(
    'field_employee',
    'field_job_type'
  );
  $variables['the_team'] = _bootstrap_subtheme_rendered_field_array($wrapper, $fields);

  $variables['stakeholders'] = _bootstrap_subtheme_stakeholder_markup($wrapper);

}

/**
 * Return field values rendered by their display settings.
 */
function _bootstrap_subtheme_render(&$rows, $key, $entity, $entity_type, $fields) {
  foreach ($fields as $field_name) {
    $rows[$key][$field_name] = field_view_field($entity_type, $entity, $field_name, 'full');
    $rows[$key][$field_name] = render($rows[$key][$field_name]);
  }
}

/**
 * Create the stakeholder table markup.
 */
function _bootstrap_subtheme_stakeholder_markup($wrapper) {
  $header = array(
    'Role',
    'Name',
    'Email address',
    'Phone number'
  );
  $rows = array();
  foreach ($wrapper->field_stakeholder as $key => $stakeholder) {
    $profile = profile2_load_by_user($stakeholder->getIdentifier(), 'stakeholder');
    $profile_wrapper = entity_metadata_wrapper('profile2', $profile);
    $rows[] = array(
      'field_role' => $profile_wrapper->field_role->name->value(),
      'field_name' => $profile_wrapper->field_full_name->value(),
      'field_email' => $stakeholder->mail->value(),
      'field_phone' => $profile_wrapper->field_phone->value()
    );
  }

  return theme('table', ['header' => $header, 'rows' => $rows]);
}

/**
 * Create rendered table from field array.
 */
function _bootstrap_subtheme_rendered_field_array($wrapper, $fields) {
  $header = array_fill(0, 2, NULL);
  $rows = array();
  foreach ($wrapper->field_internal_team as $key => $member) {
    _bootstrap_subtheme_render($rows, $key, $member->value(), 'multifield', $fields);
  }

  return theme('table', ['header' => $header, 'rows' => $rows]);
}

/**
 * Create a rendered table with all rate date.
 */
function _bootstrap_subtheme_create_rate_table($node, $wrapper, &$rows) {
  if (!empty($node->field_table_rate['und'])) {
    // Insert all the Table Rate multifield to an array by field,
    foreach ($wrapper->field_table_rate as $key => $rate) {

      $fields = array(
        'field_issue_type',
        'field_scope',
        'field_rate',
        'field_rate_type',
        'field_hours',
        'field_issue_type_label'
      );
      _bootstrap_subtheme_render($rows, $key, $rate->value(), 'multifield', $fields);

      // Add days.
      $rows[$key]['days'] = productivity_project_get_total_days($rate->field_hours->value());
      $rows[$key]['recalculate'] = l(t('Recalculate'), 'recalculate-project-time/' . $node->nid . '/' . $rate->field_issue_type->value());

      // Override work type titles.
      $rows[$key]['field_issue_type'] = empty($rows[$key]['field_issue_type_label']) ? $rows[$key]['field_issue_type'] : $rows[$key]['field_issue_type_label'];
      unset($rows[$key]['field_issue_type_label']);
    }
  }

  $header = array(
    'Type',
    'Total Scope',
    'Rate',
    'Rate Type',
    'Hours',
    'Days',
    'actions'
  );

  return theme('table', array('header' => $header, 'rows' => $rows));
}

/**
 * HTML preprocess.
 */
function bootstrap_subtheme_preprocess_html(&$variables) {
  // Add ng-app="plApp" attribute to the body tag.
  $variables['attributes_array']['ng-app'] = 'productivityApp';
  $variables['body_attributes_array']['class'][] = 'pace-done';
  $variables['theme_path'] = base_path() . drupal_get_path('theme', 'bootstrap_subtheme');

}

function bootstrap_subtheme_preprocess_page(&$variables) {
  $variables['theme_path'] = base_path() . drupal_get_path('theme', 'bootstrap_subtheme');
  $menu = menu_get_item();
  $variables['path'] = $menu['path'];
}

/**
 * Implements hook_element_info_alter().
 *
 * Remove bootstrap's textfield processing to avoid having the "form-control"
 * class on textfields - It adds some hard-to-reset CSS.
 */
function bootstrap_subtheme_element_info_alter(&$elements) {
  foreach ($elements['textfield']['#process'] as $delta => $callback) {
    if ($callback == '_bootstrap_process_input') {
      unset($elements['textfield']['#process'][$delta]);
    }
  }
}

/**
 * Get a chart render array from the calculated rows when displaying a project.
 *
 * @param $rows
 *   Rows from the "Hours by type" table.
 *
 * @return Array
 *   Pre-rendered array for a pie chart.
 */
function _bootstrap_subtheme_get_hours_type_chart($rows) {
  $types = array();
  $hours = array();
  foreach ($rows as $row) {
    $types[] = strip_tags($row['field_issue_type']);
    $hours[] = floatval(strip_tags($row['field_hours']));
  }

  $chart = array(
    '#type' => 'chart',
    '#title' => t('Hours by type'),
    '#chart_type' => 'pie',
    '#chart_library' => 'highcharts',
    '#legend_position' => 'right',
    '#data_labels' => FALSE,
    '#tooltips' => TRUE,
  );

  $chart['pie_data'] = array(
    '#type' => 'chart_data',
    '#title' => t('type'),
    '#labels' => $types,
    '#data' => $hours,
  );

  $chart_container['chart'] = $chart;

  return $chart_container;
}
