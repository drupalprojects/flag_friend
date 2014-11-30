<?php
/**
 * @file
 * Contains the FFA status field handler.
 */

/**
 * Provides a field handler for the flag_friend_access.status column.
 */
class flag_friend_access_views_handler_field_status extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['public'] = array(
      'default' => 'Everyone',
      'translatable' => TRUE,
    );

    $options['friends'] = array(
      'default' => 'Only my friends',
      'translatable' => TRUE,
    );

    $options['private'] = array(
      'default' => 'Just me',
      'translatable' => TRUE,
    );

    return $options;
  }

  /**
   * {@inheritdoc}
   */
  function options_form(&$form, &$form_state) {
    $form['public'] = array(
      '#type' => 'textfield',
      '#title' => 'Public status name',
      '#default_value' => $this->options['public'],
    );

    $form['friends'] = array(
      '#type' => 'textfield',
      '#title' => 'Friends-only status name',
      '#default_value' => $this->options['friends'],
    );

    $form['private'] = array(
      '#type' => 'textfield',
      '#title' => 'private status name',
      '#default_value' => $this->options['private'],
    );

    parent::options_form($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  function render($values) {
    $value = $this->get_value($values);

    if (!empty($value)) {
      switch ($value) {
        case '1':
          return filter_xss_admin($this->options['friends']);
          break;

        case '2':
          return filter_xss_admin($this->options['private']);
          break;
      }
    }

    return filter_xss_admin($this->options['public']);
  }
}
