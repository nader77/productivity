core = 7.x
api = 2

; Modules
projects[admin_menu][subdir] = "contrib"
projects[admin_menu][version] = "3.x-dev"
; Fix error on clear cache, https://www.drupal.org/node/2502695
projects[admin_menu][patch] = "https://www.drupal.org/files/issues/admin_menu-issetmapfix-2502695-3.patch"

projects[admin_views][subdir] = "contrib"
projects[admin_views][version] = "1.5"

projects[ckeditor][subdir] = "contrib"
projects[ckeditor][version] = "1.x-dev"

projects[content_access][subdir] = "contrib"
projects[content_access][version] = "1.2-beta2"

projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.9"

projects[currency][subdir] = "contrib"
projects[currency][version] = "2.5"

projects[date][subdir] = "contrib"
projects[date][version] = "2.9"

projects[diff][subdir] = "contrib"
projects[diff][version] = "3.2"

projects[entity][subdir] = "contrib"
projects[entity][version] = "1.5"
projects[entity][patch][] = "https://www.drupal.org/files/issues/2264079-entity-wrapper-access-single-entity-reference-2.patch"
projects[entity][patch][] = "https://www.drupal.org/files/issues/2086225-entity-access-check-node-create-3.patch"

projects[entityreference][subdir] = "contrib"
projects[entityreference][version] = "1.1"
projects[entityreference][patch][] = "https://www.drupal.org/files/issues/migrate_multiple_entity_reference-2394725-4.patch"

projects[entityreference_filter][subdir] = "contrib"
projects[entityreference_filter][version] = "1.5"

projects[entityrelationships][subdir] = "contrib"
projects[entityrelationships][download][type] = "git"
projects[entityrelationships][download][url] = "git@github.com:Gizra/entityrelationships.git"

projects[gravatar][subdir] = "contrib"
projects[gravatar][version] = "1.x-dev"

projects[flag][subdir] = "contrib"
projects[flag][version] = "3.7"

projects[features][subdir] = "contrib"
projects[features][version] = "2.7"

projects[file_entity][subdir] = "contrib"
projects[file_entity][version] = "2.x-dev"

projects[interval][subdir] = "contrib"
projects[interval][version] = "1.0"

projects[jquery_update][subdir] = "contrib"
projects[jquery_update][version] = "2.7"

projects[logs_http][subdir] = "contrib"
projects[logs_http][version] = "1.1"

projects[mailsystem][subdir] = "contrib"
projects[mailsystem][version] = "3.x-dev"

projects[message][subdir] = "contrib"
projects[message][version] = "1.10"

projects[message_ui][subdir] = "contrib"
projects[message_ui][version] = "1.4"

projects[message_notify][subdir] = "contrib"
projects[message_notify][version] = "2.5"

projects[message_subscribe][subdir] = "contrib"
projects[message_subscribe][version] = "1.0-rc2"

projects[mimemail][subdir] = "contrib"
projects[mimemail][version] = "1.0-beta4"

projects[module_filter][subdir] = "contrib"
projects[module_filter][version] = "2.0"

projects[money][subdir] = "contrib"
projects[money][version] = "1.x-dev"

projects[multifield][subdir] = "contrib"
projects[multifield][version] = "1.x-dev"
projects[multifield][patch][] = "https://www.drupal.org/files/issues/2041531-23-entity-api-support.patch"

projects[panels][subdir] = "contrib"
projects[panels][version] = "3.5"

projects[pathauto][subdir] = "contrib"
projects[pathauto][version] = "1.3"

projects[restful][subdir] = "contrib"
projects[restful][download][type] = "git"
projects[restful][download][url] = "https://github.com/RESTful-Drupal/restful.git"
projects[restful][download][branch] = "7.x-1.x"
projects[restful][subdir] = "contrib"

projects[smtp][subdir] = "contrib"
projects[smtp][version] = "1.2"

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0"

projects[token][subdir] = "contrib"
projects[token][version] = "1.6"

projects[views][subdir] = "contrib"
projects[views][version] = "3.13"

projects[views_data_export][subdir] = "contrib"
projects[views_data_export][version] = "4.x-dev"

projects[views_bulk_operations][subdir] = "contrib"
projects[views_bulk_operations][version] = "3.3"

projects[views_calc][subdir] = "contrib"
projects[views_calc][version] = "1.1"

; Development
projects[devel][subdir] = "development"
projects[devel][version] = "1.5"

projects[coder][subdir] = "development"
projects[coder][version] = "2.3"

projects[migrate][subdir] = "development"
projects[migrate][version] = "2.8"

projects[migrate_extras][subdir] = "development"
projects[migrate_extras][version] = "2.5"

; Libraries
libraries[dompdf][type] = "libraries"
libraries[dompdf][download][type] = "get"
libraries[dompdf][download][url] = "https://github.com/dompdf/dompdf/releases/download/v0.6.1/dompdf-0.6.1.zip"

; Themes
projects[bootstrap][subdir] = "contrib"
projects[bootstrap][version] = "3.x-dev"
