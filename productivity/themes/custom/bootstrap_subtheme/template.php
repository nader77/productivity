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

function bootstrap_subtheme_preprocess_node__project__full(&$variables) {
  $variables['tracking'] = productivity_time_tracking_total_hours($variables['nid']);
}

/**
 * HTML preprocess.
 */
function bootstrap_subtheme_preprocess_html(&$variables) {
  // Add ng-app="plApp" attribute to the body tag.
  $variables['attributes_array']['ng-app'] = 'productivityApp';
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
