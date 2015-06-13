<?php

$plugin = array(
  'label' => t('Github prs'),
  'resource' => 'github-prs',
  'name' => 'github_prs__1_0',
  'entity_type' => 'node',
  'bundle' => 'github_issue',
  'description' => t('Export the "Github PR" content type.'),
  'class' => 'ProductivityGithubPrsResource',
  'authentication_types' => TRUE,
);
