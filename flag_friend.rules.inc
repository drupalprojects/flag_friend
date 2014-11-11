<?php
/**
 * @file
 * Contains rules functions for Flag Friend.
 */

/**
 * Implements hook_rules_event_info().
 */
function flag_friend_rules_event_info() {
  $items = array(
    'flag_friend_approve' => array(
      'label' => t('Friendship is approved'),
      'group' => t('Flag friend'),
      'variables' => array(
        'approving_user' => array(
          'type' => 'user',
          'label' => t('Approving user'),
        ),
        'requesting_user' => array(
          'type' => 'user',
          'label' => t('Requesting user'),
        ),
      ),
    ),
    'flag_friend_request' => array(
      'label' => t('Friendship is requested'),
      'group' => t('Flag friend'),
      'variables' => array(
        'receiving_user' => array(
          'type' => 'user',
          'label' => t('Receiving user'),
        ),
        'requesting_user' => array(
          'type' => 'user',
          'label' => t('Requesting user'),
        ),
      ),
    ),
    'flag_friend_denied' => array(
      'label' => t('Friend request is denied'),
      'group' => t('Flag friend'),
      'variables' => array(
        'receiving_user' => array(
          'type' => 'user',
          'label' => t('Receiving user'),
        ),
        'requesting_user' => array(
          'type' => 'user',
          'label' => t('Requesting user'),
        ),
      ),
    ),
    'flag_friend_cancelled' => array(
      'label' => t('Friend request is cancelled'),
      'group' => t('Flag friend'),
      'variables' => array(
        'receiving_user' => array(
          'type' => 'user',
          'label' => t('Receiving user'),
        ),
        'requesting_user' => array(
          'type' => 'user',
          'label' => t('Requesting user'),
        ),
      ),
    ),
  );

  return $items;
}
