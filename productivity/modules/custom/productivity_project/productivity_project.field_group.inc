<?php
/**
 * @file
 * productivity_project.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function productivity_project_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_deprecated|node|project|form';
  $field_group->group_name = 'group_deprecated';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'project';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Deprecated',
    'weight' => '15',
    'children' => array(
      0 => 'field_days',
      1 => 'field_rate',
      2 => 'field_rate_type',
      3 => 'field_scope',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Deprecated',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-deprecated field-group-fieldset',
        'description' => 'Do not use those fileds, they will be deleted soon.',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $field_groups['group_deprecated|node|project|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Deprecated');

  return $field_groups;
}
