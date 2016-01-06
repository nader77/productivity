<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Monthly Report'),
  'description' => t('Monthly Report.'),
  'category' => t('huji'),
  'hook theme' => 'productivity_monthly_report_content_type_theme',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Render callback.
 */
function productivity_monthly_report_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $type = '';

  $block->module = 'productivity';
  $block->title = '';
  $block->content = theme('productivity_monthly_report', array(
      'tab_header' => productivity_monthly_report_info_render_tab_header(''),
      'department_tabs' => '',
      'entity_id' => '',
    )
  );
  drupal_add_js(array('menu' => $type), 'setting');
  return $block;
}



/**
 * Delegated hook_theme().
 */
function productivity_monthly_report_content_type_theme(&$theme, $plugin) {
  $theme['productivity_monthly_report'] = array(
    'variables' => array(
      'vars' => NULL,
    ),
    'path' => $plugin['path'],
    'template' => 'monthly_report',
  );
}
