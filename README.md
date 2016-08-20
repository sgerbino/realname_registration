# Realname registration
Create usernames based on a persons real name, and save those values as user fields.

Tommy Lee Jones &rarr; TLJones

The Realname registration module is a solution for forcing professional usernames that are based on a persons real name. The _Username_ on the registration form is replaced with _First name_, _Middle name_ (optional), and _Last name_ 
fields created and provided by the site builder. The first name, middle name, and last name are preserved in the defined fields, where it is later tokenized for further use.
## Module features

## Configurations
* Use your pre-existing first, middle and last name fields
* A choice of username format
* Force the first letter of last name, middle name, and first name to be capitalized.
* Force the actual username to be lower case. _(This has no effect on the first, middle, and last name field values)_
* Use regex to validate real names

### Integrations
* Profile2 integration (`7.x-2.x`)
* Content profile integration (`6.x-2.x`)

### Tokens
Realname registration provides the following tokens;

* First name &amp; first initial
* Middle name &amp; middle initial
* Last name &amp; last initial

## Recommended modules

* [Profile2](http://drupal.org/project/profile2): Store users real names in profile2 entities, rather than the core profile module. (`7.x-2.x`)
* [Content profile](http://drupal.org/project/content_profile): Store users real names in profile node, rather than the core profile module. (`6.x-2.x`)
* [Realname](http://drupal.org/project/realname): Customize the output of usernames while keeping their login credentials based on their real name.
* [Token](http://drupal.org/project/token): Utilize your users names and initials as tokens.

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

