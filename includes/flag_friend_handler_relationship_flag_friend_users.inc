<?php

/**
 * @file
 * Relationship handler joining flag_friend table with specific fid.
 * 
 * Copied from Flag user relationship.
 */

class flag_friend_handler_relationship_flag_friend_users extends views_handler_relationship  {
  function option_definition() {
    $options = parent::option_definition();
    $options['flag'] = array('default' => flag_views_flag_default(NULL));
    $options['required'] = array('default' => 1);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['label']['#description'] .= ' '. t('Including name of the selected flag helps identify this relationship.');

    $form['flag'] = flag_views_flag_config_form('radios', NULL, $this->options['flag']);
    $form['flag']['#title'] = t('Flagged');

    $form['required']['#title'] = t('Include only users in this relationship.');
    $form['required']['#description'] = t('If checked, only users that are in relationship implemented by this flag will be included.');
  }

  function admin_summary() {
    return $this->options['flag'];
  }

  /**
   * Called to implement a relationship in a query.
   */
  function query() {
    $flag = flag_get_flag($this->options['flag']);
    $this->definition['extra'][] = array(
      'field' => 'fid',
      'value' => $flag->fid,
      'numeric' => TRUE,
    );
    parent::query();
  }
  
}
