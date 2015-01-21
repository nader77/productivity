core = 7.x
api = 2

; Modules
projects[admin_menu][subdir] = "contrib"
projects[admin_menu][version] = "3.0-rc4"

projects[admin_views][subdir] = "contrib"
projects[admin_views][version] = "1.2"

projects[ckeditor][subdir] = "contrib"
projects[ckeditor][version] = "1.x-dev"

projects[context][subdir] = "contrib"
projects[context][version] = "3.2"

projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.4"

projects[currency][subdir] = "contrib"
projects[currency][version] = "2.4"

projects[date][subdir] = "contrib"
projects[date][version] = "2.7"

projects[diff][subdir] = "contrib"
projects[diff][version] = "3.2"

projects[entity][subdir] = "contrib"
projects[entity][version] = "1.5"
projects[entity][patch][] = "https://www.drupal.org/files/issues/2264079-entity-wrapper-access-single-entity-reference-2.patch"
projects[entity][patch][] = "https://www.drupal.org/files/issues/2086225-entity-access-check-node-create-3.patch"

projects[entityreference][subdir] = "contrib"
projects[entityreference][version] = "1.1"
projects[entityreference][patch][] = "https://www.drupal.org/files/issues/migrate_multiple_entity_reference-2394725-4.patch"

projects[flag][subdir] = "contrib"
projects[flag][version] = "3.5"

projects[features][subdir] = "contrib"
projects[features][version] = "2.0"

projects[file_entity][subdir] = "contrib"
projects[file_entity][version] = "2.0-beta1"

projects[interval][subdir] = "contrib"
projects[interval][version] = "1.0"

projects[loggly_http][download][type] = "file"
projects[loggly_http][download][url] = "https://github.com/Gizra/loggly_http/archive/7.x-1.x.zip"
projects[loggly_http][subdir] = "contrib"
projects[loggly_http][type] = "module"

projects[mailsystem][subdir] = "contrib"
projects[mailsystem][version] = 2.34

projects[message][subdir] = "contrib"
projects[message][version] = "1.9"

projects[message_notify][subdir] = "contrib"
projects[message_notify][version] = "2.5"

projects[message_subscribe][subdir] = "contrib"
projects[message_subscribe][version] = "1.0-rc2"

projects[mimemail][subdir] = "contrib"
projects[mimemail][version] = "1.0-beta3"

projects[module_filter][subdir] = "contrib"
projects[module_filter][version] = "2.0-alpha2"

projects[money][subdir] = "contrib"
projects[money][version] = "1.x-dev"

projects[panels][subdir] = "contrib"
projects[panels][version] = "3.4"

projects[pathauto][subdir] = "contrib"
projects[pathauto][version] = "1.2"

projects[restful][subdir] = "contrib"
projects[restful][download][type] = "git"
projects[restful][download][url] = "https://github.com/RESTful-Drupal/restful.git"
projects[restful][download][branch] = "7.x-1.x"
projects[restful][subdir] = "contrib"

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0"

projects[token][subdir] = "contrib"
projects[token][version] = "1.5"

projects[views][subdir] = "contrib"
projects[views][version] = "3.7"

projects[views_bulk_operations][subdir] = "contrib"
projects[views_bulk_operations][version] = "3.2"


; Development
projects[devel][subdir] = "development"
projects[devel][version] = "1.5"

projects[coder][subdir] = "development"
projects[coder][version] = "2.3"

projects[migrate][subdir] = "development"
projects[migrate][version] = "2.6"

projects[migrate_extras][subdir] = "development"
projects[migrate_extras][version] = "2.5"

projects[migrate][subdir] = "development"
projects[migrate][version] = 2.5

; Libraries
libraries[dompdf][type] = "libraries"
libraries[dompdf][download][type] = "get"
libraries[dompdf][download][url] = "https://github.com/dompdf/dompdf/releases/download/v0.6.1/dompdf-0.6.1.zip"

; Themes
projects[bootstrap][subdir] = "contrib"
projects[bootstrap][version] = "3.x-dev"
