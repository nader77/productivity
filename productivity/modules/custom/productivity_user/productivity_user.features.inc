<?php
/**
 * @file
 * productivity_user.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function productivity_user_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "multifield" && $api == "multifield") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function productivity_user_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
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

/**
 * Implements hook_default_profile2_type().
 */
function productivity_user_default_profile2_type() {
  $items = array();
  $items['main'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "main",
    "label" : "Main profile",
    "weight" : "0",
    "data" : { "registration" : true, "use_page" : true }
  }');
  $items['stakeholder'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "stakeholder",
    "label" : "stakeholder",
    "weight" : "0",
    "data" : { "registration" : 0, "use_page" : 1 }
  }');
  return $items;
}
