<?php
/**
 * @file
 * productivity_time_tracking.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function productivity_time_tracking_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'monthly_report_per_project';
  $page->task = 'page';
  $page->admin_title = 'Monthly report per project';
  $page->admin_description = '';
  $page->path = 'admin/monthly-report/%node/!year/!month';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'perm',
        'settings' => array(
          'perm' => 'administer nodes',
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array();
  $page->arguments = array(
    'node' => array(
      'id' => 1,
      'identifier' => 'Node: ID',
      'name' => 'entity_id:node',
      'settings' => array(),
    ),
    'year' => array(
      'id' => 1,
      'identifier' => 'String',
      'name' => 'string',
      'settings' => array(
        'use_tail' => 0,
      ),
    ),
    'month' => array(
      'id' => 2,
      'identifier' => 'String 2',
      'name' => 'string',
      'settings' => array(
        'use_tail' => 0,
      ),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_monthly_report_per_project__panel';
  $handler->task = 'page';
  $handler->subtask = 'monthly_report_per_project';
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
    'name' => 'panel',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'project' => 'project',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'dc935670-e9d4-4c83-ab98-c4ea1931f0c2';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-68b24f6c-d4b8-4876-9539-c0503fe09c4d';
    $pane->panel = 'middle';
    $pane->type = 'monthly_report';
    $pane->subtype = 'monthly_report';
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
    $pane->uuid = '68b24f6c-d4b8-4876-9539-c0503fe09c4d';
    $display->content['new-68b24f6c-d4b8-4876-9539-c0503fe09c4d'] = $pane;
    $display->panels['middle'][0] = 'new-68b24f6c-d4b8-4876-9539-c0503fe09c4d';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['monthly_report_per_project'] = $page;

  return $pages;

}
