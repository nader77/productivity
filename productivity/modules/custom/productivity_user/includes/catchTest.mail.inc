<?php

/**
* A mail sending implementation that captures sent messages to a message type.
*
* This class is for running tests or for development.
*/
class CatchTestMailSystem extends DefaultMailSystem implements MailSystemInterface {
  /**
   * Accept an e-mail message and store it in a message.
   *
   * @param $message
   *   An e-mail message.
   */
  public function mail(array $message) {
    // Check if message is a message type already, then no need to create the
    // message, since we have a copy of it already.
    if ($message['module'] != 'message_notify') {
      $message_mail = message_create('catch_test_mail', array(
        'arguments' => array(
          '@id' => $message['id'],
          '@to' => $message['to'],
          '@from' => $message['from'],
          '@title' => $message['subject'],
          '@content' => $message['body'],
        )
      ));

      $wrapper = entity_metadata_wrapper('message', $message_mail);
      $wrapper->save();
    }
    return TRUE;
  }
}

