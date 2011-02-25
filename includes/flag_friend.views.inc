<?php

/**
 * @file flag_friend.views.inc
 *
 * Provide Flag Friend data to Views.
 */

/**
 * Implementation of hook_views_handlers().
 */
function flag_friend_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'flag_friend') .'/includes',
    ),
    'handlers' => array(
      'flag_friend_handler_argument_apachesolr_friend' => array(
        'parent' => 'apachesolr_views_handler_argument',
      ),
      'flag_friend_handler_field_links' => array(
        'parent' => 'views_handler_field',
      ),
      'flag_friend_handler_filter_flag' => array(
        'parent' => 'views_handler_filter_many_to_one',
        'file' => 'flag_friend_handler_filters.inc',
      ),
      'flag_friend_handler_relationship_flag_friend_users' => array(
        'parent' => 'views_handler_relationship',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_plugins().
 */
function flag_friend_views_plugins() {
  return array(
    'argument validator' => array(
      'flag_friend_user_current' => array(
        'title' => t('User is current'),
        'handler' => 'flag_friend_plugin_argument_validate_user_current',
        'path' => drupal_get_path('module', 'flag_friend') . '/includes',
      ),
      'flag_friend_user_current_admin' => array(
        'title' => t('User is current or admin'),
        'handler' => 'flag_friend_plugin_argument_validate_user_current_admin',
        'path' => drupal_get_path('module', 'flag_friend') . '/includes',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_data().
 */
function flag_friend_views_data() {
  $data = array();

  // flag_friend table.
  $data['flag_friend']['table']['group'] = t('Flag friend');
  $data['flag_friend']['table']['join'] = array();
  
  // Arguments.
  // Provide terminating user to a view.  
  $data['flag_friend']['uid'] = array(
    'title' => t('Flag Friend users'),
    'argument' => array(
      'help' => t('Users in a Flag Friend relationship with UID argument'),
      'handler' => 'views_handler_argument_numeric',
    ),
    'relationship' => array(
      'help' => t('Provide users that are Flag Friend relationship parties'),
      'label' => t('flag friend party'),
      'base' => 'users',
      'base field' => 'uid',
      'relationship field' => 'uid',
    )
  );
  
  // Filter for relationship type.
  $data['flag_friend']['fid'] = array(     
    'title' => t('Relationship'),
    'help' => t('Filter using specific combination of user flags (relationships).'),
    'filter' => array(
      'handler' => 'flag_friend_handler_filter_flag',
      'numeric' => TRUE,
    ),
  );
  // field, sort, filter, argument
  $data['flag_friend']['created'] = array(
    'title' => t('Relationship created time'),
    'help' => t('Display the time the relationship was approved.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );

  // flag_friend_message table
  $data['flag_friend_message']['table']['group'] = t('Flag friend');
  $data['flag_friend_message']['table']['join'] = array(
    'flag_content' => array(
      'left_field' => 'fcid',
      'field' => 'fcid',
    ),
  );
  // message field
  $data['flag_friend_message']['message'] = array(
    'title' => t('Message'),
    'help' => t('Display the message for any friend flags. Only useful for a list of pending friend requests.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => FALSE,
    ),
  );    
  return $data;
}

/**
 * Implementation of hook_views_data_alter().
 */
function flag_friend_views_data_alter(&$data) {
  if (module_exists('apachesolr_views')) {
    $data['apachesolr']['friends'] = array(
      'title' => t('Friends of'),
      'help' => t('Retrieve the friends of the user id given.'),
      'argument' => array(
        'handler' => 'flag_friend_handler_argument_apachesolr_friend',
        'field' => 'uid',
      ),
    );
  }
  
  // Attach argument to the Flag module table. We could move this to the Flag 
  // module's own Views integration, since it could benefit to all Flag users.
  $data['flag_content']['flag_uid'] = array(
    'group' => t('Flag friend'),
    'title' => t('Users flagged by'),
    'help' => t('Users flagged by argument'),
    'real field' => 'uid',
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  // Attach deny link to the Flag module table so it's available without joining
  // the flag_friend table. 
  $data['flag_content']['deny_user'] = array(
    'group' => t('Flag friend'),
    'title' => t('Deny link'),
    'help' => t('"Deny incoming relationship request" link'),
    'real field' => 'uid', 
    'field' => array(
      'handler' => 'flag_friend_handler_field_links',
    ),
  );
  
  // Fid must present in a JOIN criteria so we need custom relationship to join
  // flag_friend table properly.
  $data['users']['flag_friend_users'] = array(
    'group' => t('Flag friend'),
    'title' => t('Flag Friend users'),
    'help' => t('Users which participate in a Flag Friend relationship.'),
    'relationship' => array(
      'handler' => 'flag_friend_handler_relationship_flag_friend_users',
      'label' => t('flag friend users'),
      'base' => 'flag_friend',
      'base field' => 'friend_uid',
      'relationship field' => 'uid',
    ),
  );
}
