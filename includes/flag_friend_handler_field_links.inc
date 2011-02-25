<?php

/**
 * @file
 * Contains the flag friend Ops field handler.
 */

/**
 * Views field handler for the Flag friend "deny" operations link.
 *
 * @ingroup views
 */
class flag_friend_handler_field_links extends views_handler_field {
  /**
   * Returns the flag object associated with our field.
   *
   * A field is in some relationship. This function reaches out for this
   * relationship and reads its 'flag' option, which holds the flag name.
   */
  function get_flag() {
    $flag_name = $this->view->relationship[$this->options['relationship']]->options['flag'];
    return flag_get_flag($flag_name);
  }

  /**
   * Return the the relationship we're linked to. That is, the alias for its
   * table (which is suitbale for use with the various methods of the 'query'
   * object).
   */
  function get_parent_relationship() {
    $parent = $this->view->relationship[$this->options['relationship']]->options['relationship'];
    if (!$parent || $parent == 'none') {
      return NULL; // Base query table.
    }
    else {
      return $this->view->relationship[$parent]->alias;
    }
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['link_type'] = array('default' => '');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['link_type'] = array(
      '#type' => 'radios',
      '#title' => t('Link type'),
      '#options' => array('' => t('Use flag link settings')) + _flag_link_type_options(),
      '#default_value' => $this->options['link_type'],
    );
  }
  
  
  /**
   * Render "deny incoming relationship request" link.
   * 
   * TODO: Add access check in pre_render() like Flag's module "ops" field.
   */   
  function render($values) {
    global $user;
    if ($this->view->args[0] == $user->uid) {
      $flag = $this->get_flag();
      $content_id = $values->uid;
      // what's the status?
      $status = flag_friend_relationship_status($flag, $user->uid, $content_id);
      if ($status == FLAG_FRIEND_APPROVAL) {
        return $flag->theme('deny', $content_id);
      }
    }
  }
}
