<h3>Project summary</h3>
Create usernames based on a persons real name, and save those values as user fields.

Tommy Lee Jones &rarr; TLJones

The Realname registration module is a solution for forcing professional usernames that are based on a persons real name. The <em>Username</em> on the registration form is replaced with <em>First name</em>, <em>Middle name</em> (optional), and <em>Last name</em> 
fields created and provided by the site builder. The first name, middle name, and last name are preserved in the defined fields, where it is later tokenized for further use.
<h3>Module features</h3>
<dl>
<dt>Configurations</dt>
<dd>
<ul>
<li>Use your pre-existing first, middle and last name fields</li>
<li>A choice of username format</li>
<li>Force the first letter of last name, middle name, and first name to be capitalized.</li>
<li>Force the actual username to be lower case. <em>(This has no effect on the first, middle, and last name field values)</em>
<li>Use regex to validate real names</li>
</ul>
<dt><strong>Integrations</strong><dt>
<dd><ul>
<li>Profile2 integration (<code>7.x-2.x</code>)</li>
<li>Content profile integration (<code>6.x-2.x</code>)</li>
</dd></ul>
</dd>
<dt><strong>Tokens</strong><dt>
<dd>Realname registration provides the following tokens;
<ul>
  <li>First name &amp; first initial</li>
  <li>Middle name &amp; middle initial</li>
  <li>Last name &amp; last initial</li>
</ul>
</dd>
</dl>
<h3>Recommended modules</h3>
<ul>
<li><a href="http://drupal.org/project/profile2">Profile2</a>: Store users real names in profile2 entities, rather than the core profile module. (<code>7.x-2.x</code>)</li>
<li><a href="http://drupal.org/project/content_profile">Content profile</a>: Store users real names in profile node, rather than the core profile module. (<code>6.x-2.x</code>)</li>
<li><a href="http://drupal.org/project/realname">Realname</a>: Customize the output of usernames while keeping their login credentials based on their real name.</li>
<li><a href="http://drupal.org/project/token">Token</a>: Utilize your users names and initials as tokens.</li>
</ul>
<h3>Getting involved</h3>
<ul>
<li>Test out development releases and post any bugs or feature requests in the <a href="http://drupal.org/project/issues/realname_registration?status=All&categories=All" target="_blank">issue queue</a></li>
<li>Write a review for this module on <a href="http://drupalmodules.com/module/realname-registration" target="_blank">drupalmodules.com</a></li>
<li>Help translate this module at <a href="http://localize.drupal.org/translate/projects/realname_registration" target="_blank">localize.drupal.org</a></li>
</ul>

## Installation
To use this module, you will first need to add name fields to user profiles,
and then configure this module to use them to generate a Drupal user name (the
internal "machine name"). Fields can be added using the contrib module
Profile2, or with the core profile fields. You will need at least two fields
for the first and last name, and optionally a third field for a middle name.
Each field used must be mandatory and be include on the user registration
form.

If you delete these fields, or change them to no longer be required and
included on the user registration form, you will need to also update the
settings for this module to choose new fields.

You may also be interested in using the Realname module, which controls how
usernames are displayed publicly, which is a related but independent use case
to the one addressed by this module.

To add core profile fields:
Home » Administration » Configuration » People » Account settings » Manage fields
(/admin/config/people/accounts/fields)

To add Profile2 fields::
Home » Administration » Structure » Profile types
(/admin/structure/profiles)
Edit the profile type you wish to use and ensure that "Show during user
account registration" is selected, then select "manage fields" for that type
and add new required fields.

To tell this module which fields to use for first, middle, and last names:
Home » Administration » Configuration » People » Realname Registration
/admin/config/people/realname_registration

If the field you've selected is from a Profile2 profile type, you will need to
indicate that, and enter the machine name of the profile type (such as "main"
for the default profile type).

The "Create new account" form at /user/register and the "Add user" form at
/admin/people/create will now present the configured fields instead of the core
username field.  The username will be determined automatically based on the
rules selected on this module's configuration page.

TODO
====

Higher priority:
 - show available field and profile type options as a dropdown box instead of
   making users type the machine name!
 - check for username length during form validation
 - provide option to update existing usernames when names are updated
 - improve how strings with placeholders are translated

Lower priority:
 - provide an action to bulk update existing usernames when
   realname_registration is enabled or its configuration has changed
 - handle multiple middle names
 - integrate with the name module
 - handle the case where name fields are translated (do people really do this?)

