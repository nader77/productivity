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

    if (field_info_field('og_user_node')) {
      $public_fields['tracking'] = array(
        'property' => 'og_user_node',
        'resource' => array(
          'tracking' => 'tracking',
        ),
      );
    }

    $public_fields['roles'] = array(
      'property' => 'roles',
      'process_callbacks' => array(
        array($this, 'rolesProcess'),
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
   * Process callback, get titles for user's roles.
   */
  public function rolesProcess($rolesID) {
    global $user;

    $roles = array();
    foreach ($rolesID as $roleID) {
      $roles[$roleID] = $user->roles[$roleID];
    }

    return $roles;
  }
}
