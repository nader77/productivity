<?php

$plugin = array(
  'label' => t('Timewatch punch'),
  'resource' => 'timewatch-punch',
  'name' => 'timewatch_punch__1_0',
  'entity_type' => 'node',
  'bundle' => 'work_session',
  'description' => t('Punch the timewatch'),
  'class' => 'ProductivityTimewatchPunchResource',
  'authentication_types' => TRUE,
);
