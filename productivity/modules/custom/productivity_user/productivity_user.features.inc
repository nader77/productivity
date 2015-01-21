<?php
/**
 * @file
 * productivity_user.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function productivity_user_ctools_plugin_api() {
  list($module, $api) = func_get_args();
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
    "message_text" : { "en" : [
        {
          "value" : "\\u003Cp\\u003E@title\\u003C\\/p\\u003E\\r\\n",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E@title\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Cp\\u003EID: @id\\u003C\\/p\\u003E\\r\\n\\r\\n\\u003Cp\\u003ETo: @to\\u003C\\/p\\u003E\\r\\n\\r\\n\\u003Cp\\u003EFrom: @from\\u003C\\/p\\u003E\\r\\n\\r\\n\\u003Cp\\u003E@content\\u003C\\/p\\u003E\\r\\n",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003EID: @id\\u003C\\/p\\u003E\\n\\u003Cp\\u003ETo: @to\\u003C\\/p\\u003E\\n\\u003Cp\\u003EFrom: @from\\u003C\\/p\\u003E\\n\\u003Cp\\u003E@content\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  return $items;
}
