<?php

/**
 * Plugin definition.
 *
 * Display the Monthly Report.
 */
$plugin = array(
  'title' => t('Monthly Report'),
  'description' => t('Display monthly_report'),
  'category' => t('Productivity'),
  'hook theme' => 'productivity_monthly_report_theme',
);

/**
 * Render callback;  Bidder page.
 */
function productivity_monthly_report_content_type_render($subtype, $conf, $args, $context) {
  $variables = array();
  $variables['theme_path'] = base_path() . drupal_get_path('theme', 'bootstrap_subtheme');
  $block = new stdClass();
  $block->module = 'productivity_project';
  $block->title = '';
  $block->content = theme('productivity_monthly_report', $variables);

  return $block;
}

/**
 * Delegated hook_theme().
 */
function productivity_monthly_report_theme(&$theme, $plugin) {
  $theme['productivity_monthly_report'] = array(
    'variables' => array(
    ),
    'path' => $plugin['path'],
    'template' => 'teaser',
  );
}
