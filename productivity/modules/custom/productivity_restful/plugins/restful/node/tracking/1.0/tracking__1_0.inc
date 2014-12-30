<?php

$plugin = array(
  'label' => t('Tracking'),
  'resource' => 'tracking',
  'name' => 'tracking__1_0',
  'entity_type' => 'node',
  'bundle' => 'time_tracking',
  'description' => t('Export the "time tracking" content type.'),
  'class' => 'ProductivityTrackingResource',
  'authentication_types' => TRUE,
);
