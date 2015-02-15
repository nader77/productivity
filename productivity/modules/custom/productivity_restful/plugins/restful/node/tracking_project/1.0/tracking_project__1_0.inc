<?php

$plugin = array(
  'label' => t('Tracking Project'),
  'resource' => 'tracking-project',
  'name' => 'tracking_project__1_0',
  'entity_type' => 'node',
  'bundle' => 'project',
  'description' => t('Get tracking summary per project.'),
  'class' => 'ProductivityTrackingProjectResource',
  'authentication_types' => TRUE,
);
