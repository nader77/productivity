<?php
/**
 * @file
 * productivity_time_tracking.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function productivity_time_tracking_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_message_type().
 */
function productivity_time_tracking_default_message_type() {
  $items = array();
  $items['mail_reminder'] = entity_import('message_type', '{
    "name" : "mail_reminder",
    "description" : "Mail reminder",
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
          "value" : "Hi [message:user:name]!\\r\\n\\r\\nPlease track your work  \\u003Ca href=\\u0022http:\\/\\/productivity.gizra.com\\/#\\/tracking\\/[message:user:name]\\/[current-date:yesterday]\\/new\\u0022\\u003E here \\u003C\\/a\\u003E.",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EHi [message:user:name]!\\u003C\\/p\\u003E\\n\\u003Cp\\u003EPlease track your work  \\u003Ca href=\\u0022http:\\/\\/productivity.gizra.com\\/#\\/tracking\\/[message:user:name]\\/[current-date:yesterday]\\/new\\u0022\\u003E here \\u003C\\/a\\u003E.\\u003C\\/p\\u003E\\n"
        }
      ]
    }
  }');
  return $items;
}

/**
 * Implements hook_node_info().
 */
function productivity_time_tracking_node_info() {
  $items = array(
    'time_tracking' => array(
      'name' => t('Time tracking'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
