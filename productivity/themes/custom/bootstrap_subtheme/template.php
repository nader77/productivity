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

function bootstrap_subtheme_preprocess_node__project__full(&$variables) {
  $content = &$variables['content'];
  module_load_include('inc','productivity_github', 'productivity_github.table');
  $content['per_issue_table'] = productivity_github_time_display_tracking_issue_table($variables['nid'], FALSE);
}
