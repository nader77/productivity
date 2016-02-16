<?php

/**
 * Plugin definition.
 *
 * Display the Live Auction Auctioneer Page.
 */
$plugin = array(
  'title' => t('Dashboard'),
  'description' => t('Display Dashboard main content'),
  'category' => t('Productivity'),
  'hook theme' => 'productivity_project_teaser_theme',
);

/**
 * Render callback;  Bidder page.
 */
function productivity_project_teaser_content_type_render($subtype, $conf, $args, $context) {

  //Get list of most relevant project.
  $projects = productivity_project_get_all_projects(9);
  $variables = array();
  $variables['theme_path'] = base_path() . drupal_get_path('theme', 'bootstrap_subtheme');
  $variables['rendered_nodes'] = array();

  foreach($projects as $nid => $title) {
    $node_variables = array();
    $node_variables['title'] = $title;
    $wrapper = entity_metadata_wrapper('node', $nid);
    $node_variables['url'] = l($title, 'node/' . $nid);
    $node_variables['scope'] = productivity_project_get_total_scope($wrapper);
    $node_variables['total_done'] = $wrapper->field_hours->value();

    $variables['rendered_nodes'][] = theme('productivity_project_teaser', $node_variables);
  }

  $variables_header = array();
  $variables_header['due_amount'] = 0;

  $variables['header'] = theme('productivity_project_teaser_header', $variables_header);
  $block = new stdClass();
  $block->module = 'productivity_project';
  $block->title = '';
  $block->content = theme('productivity_project_teaser', $variables);

  return $block;
}

/**
 * Edit form.
 */
function productivity_project_teaser_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Delegated hook_theme().
 */
function productivity_project_teaser_theme(&$theme, $plugin) {
  $theme['productivity_project_teaser'] = array(
    'variables' => array(
    ),
    'path' => $plugin['path'],
    'template' => 'teaser',
  );

  $theme['productivity_project_teaser'] = array(
    'variables' => array(
    ),
    'path' => $plugin['path'],
    'template' => 'dashboard',
  );

  $theme['productivity_project_teaser_header'] = array(
    'variables' => array(
    ),
    'path' => $plugin['path'],
    'template' => 'dashboard_header',
  );

}
