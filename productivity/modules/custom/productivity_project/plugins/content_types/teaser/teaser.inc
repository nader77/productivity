<?php

/**
 * Plugin definition.
 *
 * Display the Live Auction Auctioneer Page.
 */
$plugin = array(
  'title' => t('Project teaser'),
  'description' => t('Display project teaser'),
  'category' => t('Productivity'),
  'hook theme' => 'productivity_project_teaser_theme',
);

/**
 * Render callback;  Bidder page.
 */
function productivity_project_teaser_content_type_render($subtype, $conf, $args, $context) {
  $variables = array();
  $variables['theme_path'] = base_path() . drupal_get_path('theme', 'bootstrap_subtheme');
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
}
