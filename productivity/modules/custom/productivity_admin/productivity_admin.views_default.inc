<?php
/**
 * @file
 * productivity_admin.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function productivity_admin_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'entity_ref_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Entity ref list';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Type */
  $handler->display->display_options['arguments']['type']['id'] = 'type';
  $handler->display->display_options['arguments']['type']['table'] = 'node';
  $handler->display->display_options['arguments']['type']['field'] = 'type';
  $handler->display->display_options['arguments']['type']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['type']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['type']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['type']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['type']['limit'] = '0';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $export['entity_ref_list'] = $view;

  $view = new view();
  $view->name = 'github';
  $view->description = 'Find and manage content.';
  $view->tag = 'admin';
  $view->base_table = 'node';
  $view->human_name = 'Github';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Content';
  $handler->display->display_options['css_class'] = 'admin-views-view';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'menu';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = 50;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'title' => 'title',
    'timestamp' => 'title',
    'changed' => 'changed',
    'field_employee' => 'field_employee',
    'field_github_repository_name' => 'field_github_repository_name',
    'field_issue_id' => 'field_issue_id',
    'field_project' => 'field_project',
    'field_pr_status' => 'field_pr_status',
    'field_work_date' => 'field_work_date',
    'field_github_username' => 'field_github_username',
    'delete_node' => 'edit_node',
    'edit_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = 'changed';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '&nbsp;',
      'empty_column' => 0,
    ),
    'timestamp' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_employee' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_github_repository_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_issue_id' => array(
      'sortable' => 1,
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
    'field_pr_status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_work_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_github_username' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '&emsp;',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = 'No content available.';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: Content: Taxonomy terms on node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'forums' => 0,
    'tags' => 0,
  );
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::node_assign_owner_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Change author',
      'postpone_processing' => 0,
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Delete',
      'postpone_processing' => 0,
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Change value',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
      'postpone_processing' => 0,
    ),
    'action::node_make_sticky_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Stick',
      'postpone_processing' => 0,
    ),
    'action::node_make_unsticky_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Unstick',
      'postpone_processing' => 0,
    ),
    'action::node_promote_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Promote to front page',
      'postpone_processing' => 0,
    ),
    'action::node_publish_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Publish',
      'postpone_processing' => 0,
    ),
    'action::node_unpromote_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Demote from front page',
      'postpone_processing' => 0,
    ),
    'action::node_unpublish_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Unpublish',
      'postpone_processing' => 0,
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: Content: Has new content */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'history';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = '';
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Updated';
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  /* Field: Content: Employee */
  $handler->display->display_options['fields']['field_employee']['id'] = 'field_employee';
  $handler->display->display_options['fields']['field_employee']['table'] = 'field_data_field_employee';
  $handler->display->display_options['fields']['field_employee']['field'] = 'field_employee';
  $handler->display->display_options['fields']['field_employee']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Issue ID */
  $handler->display->display_options['fields']['field_issue_id']['id'] = 'field_issue_id';
  $handler->display->display_options['fields']['field_issue_id']['table'] = 'field_data_field_issue_id';
  $handler->display->display_options['fields']['field_issue_id']['field'] = 'field_issue_id';
  $handler->display->display_options['fields']['field_issue_id']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Github Project ID */
  $handler->display->display_options['fields']['field_github_project_id']['id'] = 'field_github_project_id';
  $handler->display->display_options['fields']['field_github_project_id']['table'] = 'field_data_field_github_project_id';
  $handler->display->display_options['fields']['field_github_project_id']['field'] = 'field_github_project_id';
  /* Field: Content: Time Estimate */
  $handler->display->display_options['fields']['field_time_estimate']['id'] = 'field_time_estimate';
  $handler->display->display_options['fields']['field_time_estimate']['table'] = 'field_data_field_time_estimate';
  $handler->display->display_options['fields']['field_time_estimate']['field'] = 'field_time_estimate';
  $handler->display->display_options['fields']['field_time_estimate']['settings'] = array(
    'thousand_separator' => '',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Project */
  $handler->display->display_options['fields']['field_project']['id'] = 'field_project';
  $handler->display->display_options['fields']['field_project']['table'] = 'field_data_field_project';
  $handler->display->display_options['fields']['field_project']['field'] = 'field_project';
  $handler->display->display_options['fields']['field_project']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Pull request status */
  $handler->display->display_options['fields']['field_pr_status']['id'] = 'field_pr_status';
  $handler->display->display_options['fields']['field_pr_status']['table'] = 'field_data_field_pr_status';
  $handler->display->display_options['fields']['field_pr_status']['field'] = 'field_pr_status';
  /* Field: Content: Work date */
  $handler->display->display_options['fields']['field_work_date']['id'] = 'field_work_date';
  $handler->display->display_options['fields']['field_work_date']['table'] = 'field_data_field_work_date';
  $handler->display->display_options['fields']['field_work_date']['field'] = 'field_work_date';
  $handler->display->display_options['fields']['field_work_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['label'] = '';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Operations';
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember'] = TRUE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'github_issue' => 'github_issue',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['remember'] = TRUE;
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['group'] = 1;
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Author';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'author';
  $handler->display->display_options['filters']['uid']['expose']['remember'] = TRUE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 'All';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Published';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember'] = TRUE;
  /* Filter criterion: Content: Project (field_project) (reference filter) */
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['id'] = 'field_project_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['table'] = 'field_data_field_project';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['field'] = 'field_project_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['group'] = 1;
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['operator_id'] = 'field_project_target_id_entityreference_filter_op';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['label'] = 'Project';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['operator'] = 'field_project_target_id_entityreference_filter_op';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['identifier'] = 'field_project_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['reference_display'] = 'entity_ref_list:entityreference_1';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['reference_arguments'] = 'project';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'admin/content/github';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Github';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['github'] = $view;

  $view = new view();
  $view->name = 'project_monthly_report';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Project monthly report';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Project monthly report';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer nodes';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'nid' => 'nid',
    'field_work_date' => 'field_work_date',
    'field_track_hours' => 'field_track_hours',
    'field_description' => 'field_description',
    'field_issues_logs' => 'field_issues_logs',
    'field_employee' => 'field_employee',
  );
  $handler->display->display_options['style_options']['default'] = 'field_work_date';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_work_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_track_hours' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_description' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_issues_logs' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_employee' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: Content: Work date */
  $handler->display->display_options['fields']['field_work_date']['id'] = 'field_work_date';
  $handler->display->display_options['fields']['field_work_date']['table'] = 'field_data_field_work_date';
  $handler->display->display_options['fields']['field_work_date']['field'] = 'field_work_date';
  $handler->display->display_options['fields']['field_work_date']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_work_date']['alter']['path'] = 'node/[nid]';
  $handler->display->display_options['fields']['field_work_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: Hours */
  $handler->display->display_options['fields']['field_track_hours']['id'] = 'field_track_hours';
  $handler->display->display_options['fields']['field_track_hours']['table'] = 'field_data_field_track_hours';
  $handler->display->display_options['fields']['field_track_hours']['field'] = 'field_track_hours';
  $handler->display->display_options['fields']['field_track_hours']['settings'] = array(
    'thousand_separator' => ' ',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Description */
  $handler->display->display_options['fields']['field_description']['id'] = 'field_description';
  $handler->display->display_options['fields']['field_description']['table'] = 'field_data_field_description';
  $handler->display->display_options['fields']['field_description']['field'] = 'field_description';
  /* Field: Content: Issues logs */
  $handler->display->display_options['fields']['field_issues_logs']['id'] = 'field_issues_logs';
  $handler->display->display_options['fields']['field_issues_logs']['table'] = 'field_data_field_issues_logs';
  $handler->display->display_options['fields']['field_issues_logs']['field'] = 'field_issues_logs';
  $handler->display->display_options['fields']['field_issues_logs']['click_sort_column'] = 'field_github_issue_target_id';
  $handler->display->display_options['fields']['field_issues_logs']['settings'] = array(
    'view_mode' => 'default',
  );
  $handler->display->display_options['fields']['field_issues_logs']['delta_offset'] = '0';
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['row_clickable'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          'time_tracking::field_employee' => 'time_tracking::field_employee',
        ),
      ),
    ),
  );
  /* Field: Content: Employee */
  $handler->display->display_options['fields']['field_employee']['id'] = 'field_employee';
  $handler->display->display_options['fields']['field_employee']['table'] = 'field_data_field_employee';
  $handler->display->display_options['fields']['field_employee']['field'] = 'field_employee';
  $handler->display->display_options['fields']['field_employee']['label'] = 'Developer';
  $handler->display->display_options['fields']['field_employee']['settings'] = array(
    'link' => 0,
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
    'time_tracking' => 'time_tracking',
  );
  /* Filter criterion: Content: Project (field_project) (reference filter) */
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['id'] = 'field_project_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['table'] = 'field_data_field_project';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['field'] = 'field_project_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['operator_id'] = 'field_project_target_id_entityreference_filter_op';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['label'] = 'Project';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['operator'] = 'field_project_target_id_entityreference_filter_op';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['identifier'] = 'field_project_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['required'] = TRUE;
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['hide_empty_filter'] = FALSE;
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['reference_display'] = 'entity_ref_list:entityreference_1';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['reference_arguments'] = 'project';
  /* Filter criterion: Content: Day type (field_day_type) */
  $handler->display->display_options['filters']['field_day_type_value']['id'] = 'field_day_type_value';
  $handler->display->display_options['filters']['field_day_type_value']['table'] = 'field_data_field_day_type';
  $handler->display->display_options['filters']['field_day_type_value']['field'] = 'field_day_type_value';
  $handler->display->display_options['filters']['field_day_type_value']['value'] = array(
    'regular' => 'regular',
  );
  /* Filter criterion: Content: Work date (field_work_date) */
  $handler->display->display_options['filters']['field_work_date_value']['id'] = 'field_work_date_value';
  $handler->display->display_options['filters']['field_work_date_value']['table'] = 'field_data_field_work_date';
  $handler->display->display_options['filters']['field_work_date_value']['field'] = 'field_work_date_value';
  $handler->display->display_options['filters']['field_work_date_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_work_date_value']['expose']['operator_id'] = 'field_work_date_value_op';
  $handler->display->display_options['filters']['field_work_date_value']['expose']['label'] = 'Month';
  $handler->display->display_options['filters']['field_work_date_value']['expose']['operator'] = 'field_work_date_value_op';
  $handler->display->display_options['filters']['field_work_date_value']['expose']['identifier'] = 'field_work_date_value';
  $handler->display->display_options['filters']['field_work_date_value']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_work_date_value']['expose']['remember_roles'] = array(
    2 => '2',
    3 => '3',
    1 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_work_date_value']['granularity'] = 'month';
  /* Filter criterion: Content: Issues logs (field_issues_logs:field_issue_type_value) */
  $handler->display->display_options['filters']['field_issues_logs_field_issue_type_value']['id'] = 'field_issues_logs_field_issue_type_value';
  $handler->display->display_options['filters']['field_issues_logs_field_issue_type_value']['table'] = 'field_data_field_issues_logs';
  $handler->display->display_options['filters']['field_issues_logs_field_issue_type_value']['field'] = 'field_issues_logs_field_issue_type_value';
  $handler->display->display_options['filters']['field_issues_logs_field_issue_type_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_issues_logs_field_issue_type_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_issues_logs_field_issue_type_value']['expose']['operator_id'] = 'field_issues_logs_field_issue_type_value_op';
  $handler->display->display_options['filters']['field_issues_logs_field_issue_type_value']['expose']['label'] = 'Issue type';
  $handler->display->display_options['filters']['field_issues_logs_field_issue_type_value']['expose']['description'] = 'dev, qa, management, designer, non_billable, review';
  $handler->display->display_options['filters']['field_issues_logs_field_issue_type_value']['expose']['operator'] = 'field_issues_logs_field_issue_type_value_op';
  $handler->display->display_options['filters']['field_issues_logs_field_issue_type_value']['expose']['identifier'] = 'field_issues_logs_field_issue_type_value';
  $handler->display->display_options['filters']['field_issues_logs_field_issue_type_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/content/project-monthly-report';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Monthly report';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export XLS */
  $handler = $view->new_display('views_data_export', 'Data export XLS', 'views_data_export_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'admin/tracking/export-doc';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $export['project_monthly_report'] = $view;

  $view = new view();
  $view->name = 'projects';
  $view->description = 'Find and manage content.';
  $view->tag = 'admin';
  $view->base_table = 'node';
  $view->human_name = 'Projects';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Content';
  $handler->display->display_options['css_class'] = 'admin-views-view';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'menu';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = 50;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'title' => 'title',
    'timestamp' => 'title',
    'changed' => 'changed',
    'field_account' => 'field_account',
    'field_github_repository_name' => 'field_github_repository_name',
    'field_project' => 'field_project',
    'field_rate' => 'field_rate',
    'field_rate_type' => 'field_rate_type',
    'field_scope' => 'field_scope',
    'field_status' => 'field_status',
    'field_type' => 'field_type',
    'field_date' => 'field_date',
    'edit_node' => 'edit_node',
    'delete_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = 'changed';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '&nbsp;',
      'empty_column' => 0,
    ),
    'timestamp' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_account' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_github_repository_name' => array(
      'sortable' => 1,
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
    'field_rate' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rate_type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_scope' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '&emsp;',
      'empty_column' => 0,
    ),
    'delete_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = 'No content available.';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: Content: Taxonomy terms on node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'forums' => 0,
    'tags' => 0,
  );
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::node_assign_owner_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Change author',
      'postpone_processing' => 0,
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Delete',
      'postpone_processing' => 0,
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Change value',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
      'postpone_processing' => 0,
    ),
    'action::node_make_sticky_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Stick',
      'postpone_processing' => 0,
    ),
    'action::node_make_unsticky_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Unstick',
      'postpone_processing' => 0,
    ),
    'action::node_promote_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Promote to front page',
      'postpone_processing' => 0,
    ),
    'action::node_publish_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Publish',
      'postpone_processing' => 0,
    ),
    'action::node_unpromote_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Demote from front page',
      'postpone_processing' => 0,
    ),
    'action::node_unpublish_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Unpublish',
      'postpone_processing' => 0,
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: Content: Has new content */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'history';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = '';
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Updated';
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  /* Field: Content: Account */
  $handler->display->display_options['fields']['field_account']['id'] = 'field_account';
  $handler->display->display_options['fields']['field_account']['table'] = 'field_data_field_account';
  $handler->display->display_options['fields']['field_account']['field'] = 'field_account';
  $handler->display->display_options['fields']['field_account']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Github repository name */
  $handler->display->display_options['fields']['field_github_repository_name']['id'] = 'field_github_repository_name';
  $handler->display->display_options['fields']['field_github_repository_name']['table'] = 'field_data_field_github_repository_name';
  $handler->display->display_options['fields']['field_github_repository_name']['field'] = 'field_github_repository_name';
  /* Field: Content: Project */
  $handler->display->display_options['fields']['field_project']['id'] = 'field_project';
  $handler->display->display_options['fields']['field_project']['table'] = 'field_data_field_project';
  $handler->display->display_options['fields']['field_project']['field'] = 'field_project';
  $handler->display->display_options['fields']['field_project']['settings'] = array(
    'link' => 0,
  );
  /* Field: Field: Rate */
  $handler->display->display_options['fields']['field_rate']['id'] = 'field_rate';
  $handler->display->display_options['fields']['field_rate']['table'] = 'field_data_field_rate';
  $handler->display->display_options['fields']['field_rate']['field'] = 'field_rate';
  $handler->display->display_options['fields']['field_rate']['click_sort_column'] = 'amount';
  /* Field: Field: Rate type */
  $handler->display->display_options['fields']['field_rate_type']['id'] = 'field_rate_type';
  $handler->display->display_options['fields']['field_rate_type']['table'] = 'field_data_field_rate_type';
  $handler->display->display_options['fields']['field_rate_type']['field'] = 'field_rate_type';
  /* Field: Field: Scope */
  $handler->display->display_options['fields']['field_scope']['id'] = 'field_scope';
  $handler->display->display_options['fields']['field_scope']['table'] = 'field_data_field_scope';
  $handler->display->display_options['fields']['field_scope']['field'] = 'field_scope';
  $handler->display->display_options['fields']['field_scope']['click_sort_column'] = 'interval';
  /* Field: Content: Status */
  $handler->display->display_options['fields']['field_status']['id'] = 'field_status';
  $handler->display->display_options['fields']['field_status']['table'] = 'field_data_field_status';
  $handler->display->display_options['fields']['field_status']['field'] = 'field_status';
  /* Field: Content: Type */
  $handler->display->display_options['fields']['field_type']['id'] = 'field_type';
  $handler->display->display_options['fields']['field_type']['table'] = 'field_data_field_type';
  $handler->display->display_options['fields']['field_type']['field'] = 'field_type';
  /* Field: Field: Date */
  $handler->display->display_options['fields']['field_date']['id'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['table'] = 'field_data_field_date';
  $handler->display->display_options['fields']['field_date']['field'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Field: Total hours */
  $handler->display->display_options['fields']['field_hours']['id'] = 'field_hours';
  $handler->display->display_options['fields']['field_hours']['table'] = 'field_data_field_hours';
  $handler->display->display_options['fields']['field_hours']['field'] = 'field_hours';
  $handler->display->display_options['fields']['field_hours']['settings'] = array(
    'thousand_separator' => ',',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Operations';
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['label'] = '';
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember'] = TRUE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'project' => 'project',
  );
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['remember'] = TRUE;
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Author';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'author';
  $handler->display->display_options['filters']['uid']['expose']['remember'] = TRUE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 'All';
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Published';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember'] = TRUE;
  /* Filter criterion: Taxonomy term: Vocabulary */
  $handler->display->display_options['filters']['vid']['id'] = 'vid';
  $handler->display->display_options['filters']['vid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['vid']['field'] = 'vid';
  $handler->display->display_options['filters']['vid']['relationship'] = 'term_node_tid';
  $handler->display->display_options['filters']['vid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['vid']['expose']['operator_id'] = 'vid_op';
  $handler->display->display_options['filters']['vid']['expose']['label'] = 'Vocabulary';
  $handler->display->display_options['filters']['vid']['expose']['operator'] = 'vid_op';
  $handler->display->display_options['filters']['vid']['expose']['identifier'] = 'vid';
  $handler->display->display_options['filters']['vid']['expose']['remember'] = TRUE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'admin/content/projects';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Projects';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['projects'] = $view;

  $view = new view();
  $view->name = 'tracking';
  $view->description = 'Find and manage content.';
  $view->tag = 'admin';
  $view->base_table = 'node';
  $view->human_name = 'Tracking';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Content';
  $handler->display->display_options['css_class'] = 'admin-views-view';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'menu';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = 50;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'title' => 'title',
    'timestamp' => 'title',
    'changed' => 'changed',
    'field_project' => 'field_project',
    'field_date' => 'field_date',
    'edit_node' => 'edit_node',
    'delete_node' => 'edit_node',
    'field_day_type' => 'field_day_type',
    'field_employee' => 'field_employee',
    'field_track_hours' => 'field_track_hours',
    'field_work_length' => 'field_work_length',
  );
  $handler->display->display_options['style_options']['default'] = 'changed';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '&nbsp;',
      'empty_column' => 0,
    ),
    'timestamp' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
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
    'field_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '&emsp;',
      'empty_column' => 0,
    ),
    'delete_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_day_type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_employee' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_track_hours' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_work_length' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<a href="/node/add/time-tracking">Add time tracking</a>';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = 'No content available.';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: Content: Taxonomy terms on node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'forums' => 0,
    'tags' => 0,
  );
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::node_assign_owner_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Change author',
      'postpone_processing' => 0,
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Delete',
      'postpone_processing' => 0,
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Change value',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
      'postpone_processing' => 0,
    ),
    'action::node_make_sticky_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Stick',
      'postpone_processing' => 0,
    ),
    'action::node_make_unsticky_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Unstick',
      'postpone_processing' => 0,
    ),
    'action::node_promote_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Promote to front page',
      'postpone_processing' => 0,
    ),
    'action::node_publish_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Publish',
      'postpone_processing' => 0,
    ),
    'action::node_unpromote_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Demote from front page',
      'postpone_processing' => 0,
    ),
    'action::node_unpublish_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Unpublish',
      'postpone_processing' => 0,
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: Content: Has new content */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'history';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = '';
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Updated';
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  /* Field: Content: Project */
  $handler->display->display_options['fields']['field_project']['id'] = 'field_project';
  $handler->display->display_options['fields']['field_project']['table'] = 'field_data_field_project';
  $handler->display->display_options['fields']['field_project']['field'] = 'field_project';
  $handler->display->display_options['fields']['field_project']['settings'] = array(
    'link' => 0,
  );
  /* Field: Field: Date */
  $handler->display->display_options['fields']['field_date']['id'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['table'] = 'field_data_field_date';
  $handler->display->display_options['fields']['field_date']['field'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Operations';
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['label'] = '';
  /* Field: Content: Day type */
  $handler->display->display_options['fields']['field_day_type']['id'] = 'field_day_type';
  $handler->display->display_options['fields']['field_day_type']['table'] = 'field_data_field_day_type';
  $handler->display->display_options['fields']['field_day_type']['field'] = 'field_day_type';
  /* Field: Content: Employee */
  $handler->display->display_options['fields']['field_employee']['id'] = 'field_employee';
  $handler->display->display_options['fields']['field_employee']['table'] = 'field_data_field_employee';
  $handler->display->display_options['fields']['field_employee']['field'] = 'field_employee';
  $handler->display->display_options['fields']['field_employee']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Hours */
  $handler->display->display_options['fields']['field_track_hours']['id'] = 'field_track_hours';
  $handler->display->display_options['fields']['field_track_hours']['table'] = 'field_data_field_track_hours';
  $handler->display->display_options['fields']['field_track_hours']['field'] = 'field_track_hours';
  $handler->display->display_options['fields']['field_track_hours']['settings'] = array(
    'thousand_separator' => ' ',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember'] = TRUE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'time_tracking' => 'time_tracking',
  );
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['remember'] = TRUE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 'All';
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Published';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember'] = TRUE;
  /* Filter criterion: Content: Project (field_project) */
  $handler->display->display_options['filters']['field_project_target_id']['id'] = 'field_project_target_id';
  $handler->display->display_options['filters']['field_project_target_id']['table'] = 'field_data_field_project';
  $handler->display->display_options['filters']['field_project_target_id']['field'] = 'field_project_target_id';
  $handler->display->display_options['filters']['field_project_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_project_target_id']['expose']['operator_id'] = 'field_project_target_id_op';
  $handler->display->display_options['filters']['field_project_target_id']['expose']['label'] = 'Project (field_project)';
  $handler->display->display_options['filters']['field_project_target_id']['expose']['operator'] = 'field_project_target_id_op';
  $handler->display->display_options['filters']['field_project_target_id']['expose']['identifier'] = 'field_project_target_id';
  $handler->display->display_options['filters']['field_project_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Content: Day type (field_day_type) */
  $handler->display->display_options['filters']['field_day_type_value']['id'] = 'field_day_type_value';
  $handler->display->display_options['filters']['field_day_type_value']['table'] = 'field_data_field_day_type';
  $handler->display->display_options['filters']['field_day_type_value']['field'] = 'field_day_type_value';
  $handler->display->display_options['filters']['field_day_type_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_day_type_value']['expose']['operator_id'] = 'field_day_type_value_op';
  $handler->display->display_options['filters']['field_day_type_value']['expose']['label'] = 'Day type (field_day_type)';
  $handler->display->display_options['filters']['field_day_type_value']['expose']['operator'] = 'field_day_type_value_op';
  $handler->display->display_options['filters']['field_day_type_value']['expose']['identifier'] = 'field_day_type_value';
  $handler->display->display_options['filters']['field_day_type_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember'] = TRUE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'time_tracking' => 'time_tracking',
  );
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['remember'] = TRUE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 'All';
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Published';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember'] = TRUE;
  /* Filter criterion: Content: Day type (field_day_type) */
  $handler->display->display_options['filters']['field_day_type_value']['id'] = 'field_day_type_value';
  $handler->display->display_options['filters']['field_day_type_value']['table'] = 'field_data_field_day_type';
  $handler->display->display_options['filters']['field_day_type_value']['field'] = 'field_day_type_value';
  $handler->display->display_options['filters']['field_day_type_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_day_type_value']['expose']['operator_id'] = 'field_day_type_value_op';
  $handler->display->display_options['filters']['field_day_type_value']['expose']['label'] = 'Day type';
  $handler->display->display_options['filters']['field_day_type_value']['expose']['operator'] = 'field_day_type_value_op';
  $handler->display->display_options['filters']['field_day_type_value']['expose']['identifier'] = 'field_day_type_value';
  $handler->display->display_options['filters']['field_day_type_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Content: Project (field_project) (reference filter) */
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['id'] = 'field_project_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['table'] = 'field_data_field_project';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['field'] = 'field_project_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['operator_id'] = 'field_project_target_id_entityreference_filter_op';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['label'] = 'Project';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['operator'] = 'field_project_target_id_entityreference_filter_op';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['identifier'] = 'field_project_target_id_entityreference_filter';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['reference_display'] = 'entity_ref_list:entityreference_1';
  $handler->display->display_options['filters']['field_project_target_id_entityreference_filter']['reference_arguments'] = 'project';
  $handler->display->display_options['path'] = 'admin/content/tracking';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Tracking';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['tracking'] = $view;

  return $export;
}
