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