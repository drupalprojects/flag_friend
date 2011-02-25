<?php

/**
 * @file: Activity module integration for the Flag Friend.
 */

/**
 * Implementation of hook_activity_info().
 * 
 * FIXME: May still need work.
 */
function flag_friend_activity_info() {
  $flag = flag_get_flag('friend');
  $info = new stdClass();
  $info->api = 2;
  $info->name = 'flag_friend';
  $info->object_type = 'flag_friend';
  $info->objects = array('requestor' => 'user', 'requestee' => 'flag_friend'); // array keys are the labels
  $info->hooks = array('flag_friend' => array('approve', 'request', 'deny', 'remove'));
  $info->realms = array('flag_friend' => $flag->title);
  return $info;
}

/**
 * Implementation of hook_activity_grants().
 */
function flag_friend_activity_grants($activity) {
  return array(
    'flag_friend' => array($activity->uid), // the id that will be used
  );
}

/**
 * Implementation of hook_activity_access_grants().
 * 
 * FIXME: May still need work like adding $flag object or flag id to the 
 * flag_friend_get_friends() function.
 */
function flag_friend_activity_access_grants($account) {
  $friends = flag_friend_get_friends($account->uid);
  $realm_ids = array();
  if (!empty($friends)) {
    $realm_ids['flag_friend'] = array_keys($friends);
  }
  return $realm_ids;
}
