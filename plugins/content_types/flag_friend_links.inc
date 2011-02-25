<?php

/**
 * @file
 * Panel content type that exposes flag friend links for adding friends,
 * removing them or show the cancel link after request friendship.
 */

/**
 * Callback function to supply a list of content types.
 */
function flag_friend_flag_friend_links_ctools_content_types() {
  return array(
    'single' => TRUE,
    'title' => t('Flag Friend Links'),
    'description' => t('Flag Friend Links for adding / removing friends'),
    'required context' => new ctools_context_required(t('User'), 'user'),
    'category' => t('Miscellaneous'),
    'defaults' => array('flag' => ''),
  );
}

/**
 * Render the unread messages content type.
 */
function flag_friend_flag_friend_links_content_type_render($subtype, $conf, $panel_args, $context) {
  if (!empty($context) && empty($context->data)) {
    return;
  }
  // $context in this case is a user context, so we can get the user object
  // from it and put it into $account.

  $account = isset($context->data) ? drupal_clone($context->data) : NULL;
  // Make a new empty "block" which will be a Pane you can add to your Panel.
  $block = new stdClass();
  if ($account) {
    $block->title = t("Flag friend links");
    $flag = flag_get_flag($conf['flag']);
    $status = flag_friend_relationship_status($flag, $GLOBALS['user']->uid, $account->uid);
    $block->content = flag_create_link($flag->name, $account->uid);
    if ($status == FLAG_FRIEND_APPROVAL) {
      $block->content .= $flag->theme('deny', $account->uid);
    }
  }
  else {
    // If somehow the user context is empty, this is a fallback message but
    // that should never happen.
    $block->content = t("Flag friend links not available");
  }
  return $block;
}


/**
 * Plugin edit form.
 */
function flag_friend_flag_friend_links_content_type_edit_form(&$form, &$form_state) {
  $conf = $form_state['conf'];
  $form['flag'] = array(
    '#type' => 'select',
    '#title' => t('Relationship flag'),
    '#options' => flag_friend_get_flags('names'),
    '#default_value' => $conf['flag'],
  );
}

function flag_friend_flag_friend_links_content_type_edit_form_submit(&$form, &$form_state) {
  // For each part of the form defined in the 'defaults' array set when you
  // defined the content type, copy the value from the form into the array
  // of items to be saved. We don't ever want to use
  // $form_state['conf'] = $form_state['values'] because values contains
  // buttons, form id and other items we don't want stored. CTools will handle
  // the actual form submission.
  if (is_array($form_state['plugin']['defaults'])) {
    foreach (array_keys($form_state['plugin']['defaults']) as $key) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

function flag_friend_flag_friend_links_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" flag friend links', array('@s' => $context->identifier));
}
