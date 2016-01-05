<?php

/**
 * @file
 * Contains ProductivityTimewatchPunchResource.
 */

class ProductivityTimewatchPunchResource extends \ProductivityWorkSessionsResource {

  /**
   * Create a new session or update an open session according to the given
   * pincode.
   */
  public function createOrUpdateWorkSession() {
    $request = $this->getRequest();

    if (!user_access('timewatch punch')) {
      throw new RestfulForbiddenException('No punch access.');
    }

    if (empty($request['pincode'])) {
      throw new \RestfulBadRequestException('Pincode is required');
    }

    $uid = productivity_timewatch_get_uid_by_pincode($request['pincode']);
    if (!$uid) {
      throw new \RestfulBadRequestException('Wrong pincode');
    }

    parent::createOrUpdateWorkSession($uid);
  }
}
