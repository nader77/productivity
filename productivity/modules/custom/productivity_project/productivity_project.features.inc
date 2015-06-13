<?php
/**
 * @file
 * productivity_project.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function productivity_project_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_message_type().
 */
function productivity_project_default_message_type() {
  $items = array();
  $items['logged_project_hours'] = entity_import('message_type', '{
    "name" : "logged_project_hours",
    "description" : "Logged hours in a project",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : {
      "token options" : { "clear" : 0 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "Logged hours in @project_name",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003ELogged hours in @project_name\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "Hi Managers,\\r\\nThe project \\u0022@project_name\\u0022 has reached @logged_percentage% of the estimated scope logged on [current-date:medium].\\r\\nThe scope: @project_scope.\\r\\nTotal hours logged:  @project_total_hours.\\r\\nTotal days logged:  @project_total_days.\\r\\n",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EHi Managers,\\u003Cbr \\/\\u003E\\nThe project \\u0022@project_name\\u0022 has reached @logged_percentage% of the estimated scope logged on [current-date:medium].\\u003Cbr \\/\\u003E\\nThe scope: @project_scope.\\u003Cbr \\/\\u003E\\nTotal hours logged:  @project_total_hours.\\u003Cbr \\/\\u003E\\nTotal days logged:  @project_total_days.\\u003C\\/p\\u003E\\n"
        }
      ]
    }
  }');
  return $items;
}

/**
 * Implements hook_node_info().
 */
function productivity_project_node_info() {
  $items = array(
    'project' => array(
      'name' => t('Project'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
