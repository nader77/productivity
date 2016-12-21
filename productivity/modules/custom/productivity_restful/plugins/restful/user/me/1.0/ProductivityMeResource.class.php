<?php

/**
 * @file
 * Contains ProductivityMeResource.
 */

class ProductivityMeResource extends \RestfulEntityBaseUser {

  /**
   * Overrides \RestfulEntityBase::controllers.
   */
  protected $controllers = array(
    '' => array(
      \RestfulInterface::GET => 'viewEntity',
    ),
  );

  /**
   * Overrides \RestfulEntityBaseUser::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    unset($public_fields['self']);

    $public_fields['github_username'] = array(
      'property' => 'field_github_username',
    );

    $public_fields['roles'] = array(
      'property' => 'roles',
      'process_callbacks' => array(
        array($this, 'getRolesNames'),
      ),
    );


    if (field_info_field('og_user_node')) {
      $public_fields['tracking'] = array(
        'property' => 'og_user_node',
        'resource' => array(
          'tracking' => 'tracking',
        ),
      );
    }

    $public_fields['github_access_token'] = array(
      'property' => 'field_github_access_token',
      'access_callbacks' => array(
        array($this, 'accessGithubAccessToken'),
      ),
    );

    return $public_fields;
  }

  /**
   * Overrides \RestfulEntityBase::viewEntity().
   *
   * Always return the current user.
   */
  public function viewEntity($entity_id) {
    $account = $this->getAccount();
    return array(parent::viewEntity($account->uid));
  }

  /**
   * @todo: Allow access to the SSH private key only with a crypted key.
   */
  protected function accessGithubAccessToken($op, $public_field_name, \EntityMetadataWrapper $property_wrapper, \EntityMetadataWrapper $wrapper) {
    $request = $this->getRequest();
    return !empty($request['github_access_token']) ? \RestfulInterface::ACCESS_ALLOW : \RestfulInterface::ACCESS_DENY;
  }

  /**
   * Get the names of user's roles.
   *
   * @param $values
   *  The roles IDs.
   *
   * @return array
   *  The roles names.
   */
  protected function getRolesNames($values) {
    $roles_name = array();
    foreach ($values as $role_id) {
      $roles_name[] = user_role_load($role_id)->name;
    }

    return $roles_name;
  }
}
