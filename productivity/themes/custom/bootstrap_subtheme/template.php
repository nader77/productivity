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
  if (!empty($node->field_table_rate['und'])) {

    // Insert all the Table Rate multifield to an array by field,
    foreach ($wrapper->field_table_rate as $key => $rate) {

      $fields = array(
        'field_issue_type',
        'field_scope',
        'field_rate',
        'field_rate_type',
        'field_hours',
      );

      foreach ($fields as $field_name) {
        $rows[$key][$field_name] = field_view_field('multifield', $rate->value(), $field_name, 'full');
        $rows[$key][$field_name] = render($rows[$key][$field_name]);
      }
      // Add days.
      $rows[$key]['days'] = productivity_project_get_total_days($rate->field_hours->value());
      $rows[$key]['recalculate'] = l(t('Recalculate'), 'recalculate-project-time/' . $node->nid . '/' . $rate->field_issue_type->value());
    }
  }

  $header = array('Type', 'Total Scope', 'Rate', 'Rate Type', 'Hours', 'Days', 'actions');
  $table = theme('table', array('header' => $header, 'rows' => $rows ));

  $variables['table'] = $table;
  $variables['recalculate_hours_days_link'] = l(t('Recalculate project\'s hours & days.'), 'recalculate-project-time/' . $node->nid);

  module_load_include('inc','productivity_github', 'productivity_github.table');
  $variables['per_issue_table'] = productivity_github_time_display_tracking_issue_table($variables['nid'], FALSE);

  $chart = productivity_project_get_developer_chart($node);
  $variables['developer_chart'] = drupal_render($chart);

  $chart = _bootstrap_subtheme_get_hours_type_chart($rows);
  $variables['hours_chart'] = drupal_render($chart);
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
  foreach($rows as $row) {
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
