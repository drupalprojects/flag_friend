<?php
/**
 * @file
 * Contains the Flag Friend Access views status filter.
 */

class flag_friend_access_views_handler_filter_status extends views_handler_filter {
  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  function value_form(&$form, &$form_state) {
    parent::value_form($form, $form_state);

    $form['value'] = array(
      '#type' => 'radios',
      '#title' => t('Friend Access Status'),
      '#options' => array(
        FLAG_FRIEND_ACCESS_PUBLIC => t('Public'),
        FLAG_FRIEND_ACCESS_FRIENDS_ONLY => t('Friends Only'),
        FLAG_FRIEND_ACCESS_PRIVATE => t('Private'),
      ),
      '#default_value' => FLAG_FRIEND_ACCESS_PUBLIC,
    );
  }
}
