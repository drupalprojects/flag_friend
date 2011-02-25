<?php

/**
 * @file: Token module integration for the Flag Friend.
 */

/**
 * Implementation of hook_token_list().
 */
function flag_friend_token_list($type = 'all') {
  if ($type == 'flag_friend') {
    $tokens = array();
    $tokens['flag_friend'] = array(
      'requestor' => t('The name of the user who originally made the request. For removal event the name of the user performing the removal.'),
      'requestee' => t('The name of the user who originally received the request. For removal event the name of the user being removed.'),
      'requestor-uid' => t("Requestor's ID."),
      'requestee-uid' => t("Requestee's ID."),
      'requestor-url' => t("The URL of the requestor's profile page."),
      'requestee-url' => t("The URL of the requestee's profile page.")
    );
    return $tokens;
  }
}

/**
 * Implementation of hook_token_values().
 */
function flag_friend_token_values($type, $object = NULL, $options = array()) {
  if (($type == 'flag_friend') && !empty($object)) {
    $data = array();
    $data['requestor'] = $object->friend->name;
    $data['requestee'] = $object->name;
    $data['requestor-uid'] = $object->friend->uid;
    $data['requestee-uid'] = $object->uid;
    $data['requestor-url'] = base_path().drupal_get_path_alias('user/'.$object->friend->uid);
    $data['requestee-url'] = base_path().drupal_get_path_alias('user/'.$object->uid);
    return $data;
  }
}
