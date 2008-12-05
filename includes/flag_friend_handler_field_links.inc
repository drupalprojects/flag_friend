<?php
// $Id$

/**
 * @file
 * Contains the flag friend Ops field handler.
 */

/**
 * Views field handler for the Flag friend operations links (remove/pending/approve/deny).
 *
 * @ingroup views
 */
class flag_friend_handler_field_links extends views_handler_field {
  function render($values) {
    $content_id = $values->uid;
    return flag_friend_create_link('unfriend', $content_id);
  }
}
