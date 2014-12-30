<?php
/**
 * @file
 * productivity_mailgun.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function productivity_mailgun_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_message_type().
 */
function productivity_mailgun_default_message_type() {
  $items = array();
  $items['mailgun_incoming_mail'] = entity_import('message_type', '{
    "name" : "mailgun_incoming_mail",
    "description" : "MailGun incoming mail",
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
          "value" : "@text",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E@text\\u003C\\/p\\u003E\\n"
        }
      ]
    }
  }');
  return $items;
}
