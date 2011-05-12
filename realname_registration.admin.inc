<?php
/**
 * @file
 * Admin page callbacks for the Realname registration module.
 *
 */

/**
 * Form builder;
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function realname_registration_settings_form() {
  $form = array();

  $field_req = "
<ul>
  <li>The field name is correct and represents an existing field</li>
  <li>The field is associated with the <em>user</em> entity</li>
  <li>The field is required</li>
</ul>
";

  $form['realname_registration_firstname_field'] = array(
    '#type' => 'textfield',
    '#title' => t('First name field'),
    '#default_value' => variable_get('realname_registration_firstname_field'),
    '#description' => t("The name of your first name field. Ensure that: ".$field_req),
  );

  $form['realname_registration_lastname_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name field'),
    '#default_value' => variable_get('realname_registration_lastname_field'),
    '#description' => t("The name of your last name field. Ensure that: ".$field_req),
  );

  $form['realname_registration_format'] = array(
    '#type' => 'radios',
    '#title' => t('Username format'),
    '#description' => t('Select the format in which Realname registration will create new usernames.'),
    '#default_value' => variable_get('realname_registration_format', 0),
    '#options' => array(t('First name and last name separated by a space'), t('First initial and last name')),
    '#required' => TRUE,
  );

  $form['realname_registration_tolower'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force lowercase'),
    '#default_value' => variable_get('realname_registration_tolower'),
    '#description' => t("Usernames will be created using only lowercase characters."),
  );

  $form['realname_registration_use_validation'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Realname registration validation'),
    '#default_value' => variable_get('realname_registration_use_validation', 1),
    '#description' => t("Use regex to validate real names (/^[A-ZÀ-ÖØ-öø-ÿ]+$/i)"),
  );

  $form['#validate'][] = 'realname_registration_settings_validate';
  return system_settings_form($form);
}

function realname_registration_settings_validate($form, &$form_state) {
  $lastname_field = variable_get('realname_registration_lastname_field');
  $firstname_field = variable_get('realname_registration_firstname_field');

  $firstname_instance = field_info_instance('user', $firstname_field, 'user');
  $lastname_instance = field_info_instance('user', $lastname_field, 'user');

  $field_error_msg = "
The field name you've supplied either doesn't exist or fails to meet the following requirements:
<ul>
  <li>The field name is correct and represents an existing field</li>
  <li>The field is associated with the <em>user</em> entity</li>
  <li>The field is required</li>
</ul>
";

  if($firstname_instance['required'] != 1) {
    form_set_error('realname_registration_firstname_field', t($field_error_msg));
  }
  if($lastname_instance['required'] != 1) {
    form_set_error('realname_registration_lastname_field', t($field_error_msg));
  }
}