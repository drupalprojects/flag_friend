CONTENTS OF THIS FILE
=====================

 * Introduction
 * Installation
 * Using Flag Friend
 * Design Decisions


INTRODUCTION
============

Current Maintainer: socketwench

Flag Friend is a lightweight social networking module based on Flag module. The
module provides a "Friend" flag, which users may use to flag their friends.
Included in this module is Flag Friend Access, which enables users to share
their content with their friends.

DEPENDENCIES
============

 * **Flag 7.x-3.x Required.**
 * Views 7.x-3.x. Optional, but highly recommended.
 * Rules 7.x-2.x. Optional.


INSTALLATION
============

Flag Friend is installed like any other Drupal module. Like other Flag modules,
Flag Friend requires brief configuration of the flag prior to use.

1. Download and install the Flag module.
2. Download the module to your sites/SITENAME/modules directory or wherever you
   install contrib modules on your site.
3. Enable the module in Admin > Modules
4. Go to Admin > Structure > Flags and enabled the Friend flag.
5. Under Admin > People > Permissions, grant users the "Flag User entities as
   Friend" and the "Unflag User entities as Friend" permissions.


USING FLAG FRIEND
=================

To mark a user as a friend:

1. Navigate to your friend's user profile page.
2. Click the "add friend" link.

To approve an incoming friend request:

1. Navigate to your profile page.
2. Go to Friends > Friend Requests.
3. Click "approve" or "deny" to approve or deny a friendship request.

To manage friend requests you've made:

1. Navigate to your profile page.
2. Go to Friends > Pending Friends.
3. You may cancel a request by clicking the cancel link.

To view your friends:

1. Navigate to your profile page.
2. Go to Friends > View All Friends.


DESIGN DECISIONS
================

 * The module assumes one and only one Friend flag exists.
 * A friend flagging has only one state at any time.
 * Friendships do not need to be mutual, only approved.