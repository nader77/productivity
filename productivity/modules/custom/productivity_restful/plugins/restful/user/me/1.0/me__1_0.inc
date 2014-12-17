<?php

$plugin = array(
  'label' => t('Me'),
  'description' => t('Export the "User" entity of the current user.'),
  'resource' => 'me',
  'class' => 'ProductivityMeResource',
  'entity_type' => 'user',
  'bundle' => 'user',
  'authentication_types' => TRUE,
);
