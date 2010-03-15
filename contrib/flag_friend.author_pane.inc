<?php
// $Id$

/**
 * @file: Author Pane 2.x module integration for the Flag Friend.
 */

/**
 * Implementation of hook_preprocess_author_pane().
 */
function flag_friend_preprocess_author_pane(&$variables) {
  global $user;
  $account_id = $variables['account']->uid;
  // Author Pane 2.x has "caller" variable to let different modules have their
  // own templates and thus preprocesses. We must check it so we insert link 
  // only when it's needed.  
  $caller = $variables['caller'];
  $supported_callers = variable_get($flag_friend_author_pane_callers, array('advanced_forum', 'advanced_profile'));
  if (empty($caller) || !in_array($caller, $supported_callers)) {
    return;
  }
  // User can have arbitrary number of flags and we can't know which ones need 
  // processing. Simplest thing we can come up with is to include "friend" flag
  // by default since it was supported in 1.x branch.
  $supported_flag = variable_get($flag_friend_author_pane_flag, 'friend');  
  $flag = flag_get_flag($supported_flag);
  if (!$flag) {
    return;
  }
  
  // Accessing the user profile is the only way to be able to see the friend
  // flag out-of-the-box so I feel it's pretty safe to use this permisssion.
  if ($account_id != 0 && user_access('access user profiles') && $user->uid != $account_id) {
    
    $status = flag_friend_relationship_status($flag, $user->uid, $account_id);
    $action = ($flag->is_flagged($account_id)) ? 'unflag' : 'flag';
    // Transform Flag action to a Flag Friend operation.
    $op = _flag_friend_get_op($action, $status);
    if (!$op) {
      return;
    }
    switch ($op) {
      case 'approve':
      case 'request':
        $image_path = $variables['image_path'] . "/buddy-add.png";
        break;
        
      case 'deny':  
      case 'cancel':
      case 'remove':        
        $image_path = $variables['image_path'] . "/buddy-remove.png";
    }
    $link = flag_friend_flag_link($flag, $action, $account_id);
    $variables['flag_friend_link'] = $link;
    
    $image = theme('image', $image_path, $link['title'], $link['attributes']['title'], NULL, FALSE);
    $options = array(
      'query' => drupal_get_destination(),
      'html' => TRUE,
      'attributes'  => $link['attributes'],
    );
    $variables['flag_friend'] = l($image, $link['href'], $options);
  }
}
