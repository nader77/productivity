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
  'hook theme' => 'productivity_project_dashboard_theme',
);

/**
 * Render callback.
 */
function productivity_project_dashboard_content_type_render($subtype, $conf, $args, $context) {

  //Get list of most relevant project.
  $projects = productivity_project_get_all_projects(9);
  $variables = array();
  $variables['theme_path'] = base_path() . drupal_get_path('theme', 'bootstrap_subtheme');
  $variables['rendered_nodes'] = array();

  $block = new stdClass();
  $block->module = 'productivity_project';
  $block->title = '';

  if (empty($projects)) {
    // No projects to render.
    $block->content = t('No projects to view.');
    return $block;
  }

  foreach($projects as $nid => $title) {
    $node_variables = array();
    $node_variables['title'] = $title;
    $wrapper = entity_metadata_wrapper('node', $nid);
    $node_variables['link'] = l($title, 'node/' . $nid);
    $node_variables['url'] = url('node/' . $nid);
    $node_variables['scope'] = productivity_project_get_total_scope($wrapper);
    $node_variables['total_done'] = $wrapper->field_hours->value();
    // TODO: Make this more accurate removing non-billable and so.
    $node_variables['percent_done'] = 0;
    if ($node_variables['scope'] != 0) {
      $node_variables['percent_done'] = 100 / $node_variables['scope'] * $node_variables['total_done'];
    }

    $project_teams = $wrapper->field_team_leads->value();
    $node_variables['teams'] = array();
    foreach($project_teams as $team_user) {
      $node_variables['teams'][$team_user->uid] = array();
      $node_variables['teams'][$team_user->uid]['name'] = $team_user->name;
      $node_variables['teams'][$team_user->uid]['pic'] = 'http://www.gravatar.com/avatar/' . md5(strtolower(trim($team_user->mail))) . '.jpg';
    }

    $variables['rendered_nodes'][] = theme('productivity_project_teaser', $node_variables);
  }

  $variables_header = array();
  $variables_header['due_amount'] = 0;

  $variables['header'] = theme('productivity_project_dashboard_header', $variables_header);
  $block->content = theme('productivity_project_dashboard', $variables);

  return $block;
}

/**
 * Edit form.
 */
function productivity_project_dashboard_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Delegated hook_theme().
 */
function productivity_project_dashboard_theme(&$theme, $plugin) {
  $theme['productivity_project_teaser'] = array(
    'variables' => array(
    ),
    'path' => $plugin['path'],
    'template' => 'teaser',
  );

  $theme['productivity_project_dashboard'] = array(
    'variables' => array(
    ),
    'path' => $plugin['path'],
    'template' => 'dashboard',
  );

  $theme['productivity_project_dashboard_header'] = array(
    'variables' => array(
    ),
    'path' => $plugin['path'],
    'template' => 'dashboard_header',
  );

}
