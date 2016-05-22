<?php
/**
 * @file
 * productivity_payment.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function productivity_payment_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'payments';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Payments';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Payed';
  $handler->display->display_options['css_class'] = 'main-box';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_project',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_project' => 'field_project',
    'field_amount' => 'field_amount',
    'field_date_expected' => 'field_date_expected',
    'field_date_actual' => 'field_date_actual',
  );
  $handler->display->display_options['style_options']['default'] = 'field_date_expected';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_project' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_amount' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_date_expected' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_date_actual' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Field: Project */
  $handler->display->display_options['fields']['field_project']['id'] = 'field_project';
  $handler->display->display_options['fields']['field_project']['table'] = 'field_data_field_project';
  $handler->display->display_options['fields']['field_project']['field'] = 'field_project';
  $handler->display->display_options['fields']['field_project']['settings'] = array(
    'link' => 1,
  );
  /* Field: Content: Amount */
  $handler->display->display_options['fields']['field_amount']['id'] = 'field_amount';
  $handler->display->display_options['fields']['field_amount']['table'] = 'field_data_field_amount';
  $handler->display->display_options['fields']['field_amount']['field'] = 'field_amount';
  $handler->display->display_options['fields']['field_amount']['click_sort_column'] = 'amount';
  /* Field: Content: Date expected */
  $handler->display->display_options['fields']['field_date_expected']['id'] = 'field_date_expected';
  $handler->display->display_options['fields']['field_date_expected']['table'] = 'field_data_field_date_expected';
  $handler->display->display_options['fields']['field_date_expected']['field'] = 'field_date_expected';
  $handler->display->display_options['fields']['field_date_expected']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Date actual */
  $handler->display->display_options['fields']['field_date_actual']['id'] = 'field_date_actual';
  $handler->display->display_options['fields']['field_date_actual']['table'] = 'field_data_field_date_actual';
  $handler->display->display_options['fields']['field_date_actual']['field'] = 'field_date_actual';
  $handler->display->display_options['fields']['field_date_actual']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'payment' => 'payment',
  );
  /* Filter criterion: Content: Date actual (field_date_actual) */
  $handler->display->display_options['filters']['field_date_actual_value']['id'] = 'field_date_actual_value';
  $handler->display->display_options['filters']['field_date_actual_value']['table'] = 'field_data_field_date_actual';
  $handler->display->display_options['filters']['field_date_actual_value']['field'] = 'field_date_actual_value';
  $handler->display->display_options['filters']['field_date_actual_value']['operator'] = 'empty';
  $handler->display->display_options['filters']['field_date_actual_value']['expose']['operator_id'] = 'field_date_actual_value_op';
  $handler->display->display_options['filters']['field_date_actual_value']['expose']['label'] = 'Date actual (field_date_actual)';
  $handler->display->display_options['filters']['field_date_actual_value']['expose']['operator'] = 'field_date_actual_value_op';
  $handler->display->display_options['filters']['field_date_actual_value']['expose']['identifier'] = 'field_date_actual_value';
  $handler->display->display_options['filters']['field_date_actual_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_date_actual_value']['form_type'] = 'date_text';

  /* Display: Unpayed */
  $handler = $view->new_display('panel_pane', 'Unpayed', 'panel_pane_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'UnPayed';

  /* Display: Payed */
  $handler = $view->new_display('panel_pane', 'Payed', 'panel_pane_2');
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'payment' => 'payment',
  );
  /* Filter criterion: Content: Date actual (field_date_actual) */
  $handler->display->display_options['filters']['field_date_actual_value']['id'] = 'field_date_actual_value';
  $handler->display->display_options['filters']['field_date_actual_value']['table'] = 'field_data_field_date_actual';
  $handler->display->display_options['filters']['field_date_actual_value']['field'] = 'field_date_actual_value';
  $handler->display->display_options['filters']['field_date_actual_value']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_date_actual_value']['expose']['operator_id'] = 'field_date_actual_value_op';
  $handler->display->display_options['filters']['field_date_actual_value']['expose']['label'] = 'Date actual (field_date_actual)';
  $handler->display->display_options['filters']['field_date_actual_value']['expose']['operator'] = 'field_date_actual_value_op';
  $handler->display->display_options['filters']['field_date_actual_value']['expose']['identifier'] = 'field_date_actual_value';
  $handler->display->display_options['filters']['field_date_actual_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_date_actual_value']['form_type'] = 'date_text';
  $export['payments'] = $view;

  return $export;
}
