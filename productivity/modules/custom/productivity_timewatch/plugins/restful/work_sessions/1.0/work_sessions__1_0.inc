<?php

$plugin = array(
  'label' => t('Work sessions'),
  'resource' => 'work-sessions',
  'name' => 'work_sessions__1_0',
  'entity_type' => 'node',
  'bundle' => 'work_session',
  'description' => t('Work sessions endpoint.'),
  'class' => 'ProductivityWorkSessionsResource',
  'authentication_types' => TRUE,
);
