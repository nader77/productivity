<?php
/**
 * @file
 * productivity_user.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function productivity_user_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_message_type().
 */
function productivity_user_default_message_type() {
  $items = array();
  $items['catch_test_mail'] = entity_import('message_type', '{
    "name" : "catch_test_mail",
    "description" : "Catch test mail",
    "argument_keys" : [ "@content", "@title" ],
    "argument" : [],
    "category" : "message_type",
    "data" : {
      "token options" : { "clear" : 0 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "en",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "Title - @title\\r\\nContent\\r\\n@content",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003ETitle - @title\\u003Cbr \\/\\u003E\\nContent\\u003Cbr \\/\\u003E\\n@content\\u003C\\/p\\u003E\\n"
        }
      ]
    }
  }');
  return $items;
}
