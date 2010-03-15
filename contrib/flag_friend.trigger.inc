<?php
// $Id$

/**
 * @file: Trigger module integration for the Flag Friend.
 */

/**
 * Implementation of hook_hook_info().
 *
 * Provide some triggers so that actions can be performed at various stages.
 */
function flag_friend_hook_info() {
  return array(
    'flag_friend' => array(
      'flag_friend' => array(
        'approve' => array(
          'runs when' => t("A user approves another's relationship request."),
        ),
        'request' => array(
          'runs when' => t("A user requested another's relationship."),
        ),
        'deny' => array(
          'runs when' => t("A user denies another's relationship request."),
        ),
        'remove' => array(
          'runs when' => t("A user cancels relationship with another user."),
        ),
      ),
    ),
  );
}

/**
 * Implementation of hook_trigger_name().
 * 
 * FIXME: May still need work.
 */
function flag_friend_flag_friend($op, $friend, $user, $flag) {
  if (function_exists('_trigger_get_hook_aids')) {
    $aids = _trigger_get_hook_aids('flag_friend', $op);
  
    switch ($op) {
      // in this case, the users performing the operations are flipped
      case 'deny':
        $user->friend = $friend;
        $context = array(
          'hook' => 'flag_friend',
          'op' => $op,
          'user' => $friend,
          'flag_friend' => $user,
          'flag' => $flag,
        );
        break;
      // these are normal
      case 'approve':
      case 'request':
      case 'remove':
      case 'cancel':
        $friend->friend = $user;
        $context = array(
          'hook' => 'flag_friend',
          'op' => $op,
          'user' => $user,
          'flag_friend' => $friend,
          'flag' => $flag,
        );
        break;
    }
    if ($aids) {
      actions_do(array_keys($aids), $friend, $context);
    }
  }
}
