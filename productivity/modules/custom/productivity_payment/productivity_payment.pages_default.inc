<?php
/**
 * @file
 * productivity_payment.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function productivity_payment_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'payments';
  $page->task = 'page';
  $page->admin_title = 'Payments';
  $page->admin_description = '';
  $page->path = 'payments';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'perm',
        'settings' => array(
          'perm' => 'project admin',
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_payments_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'payments';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'dashboard';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'left' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '815073fb-afb3-4f02-b215-e68ea1fc148d';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-264e3cb9-82ba-464e-9acf-bca2e20f8f17';
    $pane->panel = 'left';
    $pane->type = 'views_panes';
    $pane->subtype = 'payments-panel_pane_2';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '264e3cb9-82ba-464e-9acf-bca2e20f8f17';
    $display->content['new-264e3cb9-82ba-464e-9acf-bca2e20f8f17'] = $pane;
    $display->panels['left'][0] = 'new-264e3cb9-82ba-464e-9acf-bca2e20f8f17';
    $pane = new stdClass();
    $pane->pid = 'new-68a8d365-4c8f-451e-a782-34113737a9b7';
    $pane->panel = 'top';
    $pane->type = 'views_panes';
    $pane->subtype = 'payments-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '68a8d365-4c8f-451e-a782-34113737a9b7';
    $display->content['new-68a8d365-4c8f-451e-a782-34113737a9b7'] = $pane;
    $display->panels['top'][0] = 'new-68a8d365-4c8f-451e-a782-34113737a9b7';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['payments'] = $page;

  return $pages;

}
