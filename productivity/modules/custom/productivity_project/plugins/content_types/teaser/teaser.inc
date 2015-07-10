<?php

/**
 * Plugin definition.
 *
 * Display the Live Auction Auctioneer Page.
 */
$plugin = array(
  'title' => t('Project teaser'),
  'description' => t('Display project teaser'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Productivity'),
  'hook theme' => 'productivity_project_teaser_theme',
);

/**
 * Render callback;  Bidder page.
 */
function productivity_project_teaser_content_type_render($subtype, $conf, $args, $context) {

  if (empty($context->data)) {
    return;
  }

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
function cproductivity_project_teaser_theme(&$theme, $plugin) {
  $theme['productivity_project_teaser'] = array(
    'variables' => array(
    ),
    'path' => $plugin['path'],
    'template' => 'teaser',
  );
}
