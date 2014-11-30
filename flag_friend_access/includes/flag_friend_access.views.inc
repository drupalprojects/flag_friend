<?php
/**
 * @file
 * Provides Flag Friend Access data to Views.
 */

/**
 * Implements hook_views_data().
 */
function flag_friend_access_views_data() {
  $data = array();

  $data['flag_friend_access']['table']['group'] = t('Node: Flag Friend Access');

  // Join the FFA table with the node table.
  $data['flag_friend_access']['table']['join']['node'] = array(
    'left_field' => 'nid',
    'field' => 'nid',
  );

  // We only need the status column, so we bring it in. The 'join' above
  // handles all the SQL joining we need, so we don't need a relationship here.
  $data['flag_friend_access']['status'] = array(
    'title' => t('Friends Only Status'),
    'help' => t('The friends-only status of the node.'),
    'field' => array(
      'handler' => 'flag_friend_access_views_handler_field_status',
    ),
    'filter' => array(
      'handler' => 'flag_friend_access_views_handler_filter_status',
    ),
  );

  return $data;
}
