<?php

$plugin = array(
  'label' => t('Projects'),
  'resource' => 'projects',
  'name' => 'projects__1_0',
  'entity_type' => 'node',
  'bundle' => 'project',
  'description' => t('Export the "Project" content type.'),
  'class' => 'ProductivityProjectResource',
  'authentication_types' => TRUE,
);
