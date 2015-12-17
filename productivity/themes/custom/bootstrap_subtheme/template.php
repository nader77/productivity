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

  if ($node->type == 'project' && node_access('update', $node)) {

    // Insert all the Table Rate multifield to an array by field,
    // use node because wrapper don't work with multifield.
    $rows = array();
    foreach ($node->field_table_rate['und'] as $index=>$item) {
      $rows[$index]['field_issue_type'] = $item['field_issue_type']['und']['0']['value'];
      $rows[$index]['field_scope_time'] = $item['field_scope']['und']['0']['interval'];
      $rows[$index]['field_type_rate'] = $item['field_type_rate']['und']['0']['amount'];
      $rows[$index]['field_hours'] = $item['field_hours']['und']['0']['value'];
      $rows[$index]['field_days'] = $item['field_days']['und']['0']['value'];
    }

    $header = array('Type', 'Scope', 'Rate', 'Hours', 'Days');
    $table = theme('table', array('header' => $header, 'rows' => $rows ));

    $variables['table'] = $table;
    $variables['recalculate_hours_days_link'] = l(t('Recalculate project\'s hours & days.'), url('recalculate-project-time/' . $node->nid, array('absolute' => TRUE)));
  }
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
