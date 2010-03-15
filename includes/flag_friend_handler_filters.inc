<?php
// $Id$

/**
 * Filter handler allowing to filter by flags (Flag Friend relationship types).
 */

class flag_friend_handler_filter_flag extends views_handler_filter_many_to_one {
  function construct() {
    parent::construct();
    $this->value_title = t('Options');
    
    $flags = flag_get_flags('user');
    $options = array();
    foreach ($flags as $flag) {
      $options[$flag->fid] = $flag->get_title();
    }
    $this->value_options = $options;
  }
}
