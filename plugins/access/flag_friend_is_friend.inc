<?php

/**
 * @file
 * Ctools access plugin to provide access/visibility depending of flag friend 
 * relationship status between two user contexts.
 */

/**
 * Implement specially named hook_ctools_access().
 */
function flag_friend_flag_friend_is_friend_ctools_access() {
  return array(
    'title' => t("User: Flag friend relationship"),
    'description' => t('Compare the current user and logged in user flag friend status.'),
    'callback' => 'flag_friend_flag_friend_is_friend_access_check',
    'default' => array(
      'is_friend' => 1,
    ),
    'settings form' => 'flag_friend_flag_friend_is_friend_settings',
    'summary' => 'flag_friend_flag_friend_is_friend_ctools_access_summary',
    'required context' => array(
      new ctools_context_required(t('First User'), 'user'),
      new ctools_context_required(t("Second User"), 'user')
    ),
  );
}

/**
 * Settings form for the 'by perm' access plugin
 */

function flag_friend_flag_friend_is_friend_settings(&$form, &$form_state, $conf) {
  $form['settings']['helptext'] = array(
    '#type' => 'markup',
    '#value' => '<div>'. t('Grant access based on flag_friend status between the two user contexts.') .'<br \>'. t('Note that this will NOT grant access if both users are the same.') . '</div>',
  );
  $form['settings']['flag'] = array(
    '#type' => 'select',
    '#title' => t('Relationship flag'),
    '#options' => flag_friend_get_flags('names'),
    '#default_value' => $conf['flag'],
  );
  $form['settings']['is_friend'] = array(
    '#type' => 'radios',
    '#title' => t('Grant access if both users are'),
    '#options' => array(1 => t('in relationship'), 0 => t('not in relationship')),
    '#default_value' => $conf['is_friend'],
  );
}


/**
 * Check for access.
 */
function flag_friend_flag_friend_is_friend_access_check($conf, $context) {
  if (empty($context) || count($context) != 2 || empty($context[0]->data) || empty($context[1]->data)) {
    return FALSE;
  }
  $uid1 = $context[0]->data->uid;
  $uid2 = $context[1]->data->uid;

  // No need to check friend status if it's the same user
  if ($uid1 != $uid2) {
    $flag = flag_get_flag($conf['flag']);
    $status = flag_friend_relationship_status($flag, $uid1, $uid2);
    $result = ($status === FLAG_FRIEND_RELATIONSHIP);
    return $conf['is_friend'] == 1 ? $result : !$result;
  }
  return FALSE;
}

/**
 * Describe an instance of this plugin.
 */
function flag_friend_flag_friend_is_friend_ctools_access_summary($conf, $context) {
  $comparison = !empty($conf['is_friend']) ? t('is in relationship with') : t('is not in relationship with');

  return t('@id1 @comp @id2', array('@comp' => $comparison, '@id1' => $context[0]->identifier, '@id2' => $context[1]->identifier));
}
