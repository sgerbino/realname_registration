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
  <li>The field is required and displays on the registration form</li>
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
    '#options' => array(t('First name and last name separated by a space (e.g., John Smith)'), t('First initial and last name (e.g., JSmith)')),
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
  // Retrieve the user instance and bundle using the field names provided.
  $firstname_instance = field_info_instance('user', $form_state['values']['realname_registration_firstname_field'], 'user');
  $lastname_instance = field_info_instance('user', $form_state['values']['realname_registration_lastname_field'], 'user');

  $err_pretext = 'The field name, <em>';
  $err_req = '</em>, you\'ve provided must be required.';
  $err_unknown = '</em>, you\'ve provided either does not exist or is not associated with the user entity and bundle.';
  $err_textfield = '</em>, must use textfield widget.';
  
  // We must check to see if the provided fields return a valid instance.
  if(!isset($firstname_instance)) {
    form_set_error('realname_registration_firstname_field', t($err_pretext).$form_state['values']['realname_registration_firstname_field'].t($err_unknown));
  }
  if(!isset($lastname_instance)) {
    form_set_error('realname_registration_lastname_field', t($err_pretext).$form_state['values']['realname_registration_lastname_field'].t($err_unknown));
  }
  
  // The widget associated with the field the user has provided should be a text field.
  if($firstname_instance['widget']['type'] != 'text_textfield') {
    form_set_error('realname_registration_firstname_field', t($err_pretext).$form_state['values']['realname_registration_firstname_field'].t($err_textfield));
  }
  if($lastname_instance['widget']['type'] != 'text_textfield') {
    form_set_error('realname_registration_lastname_field', t($err_pretext).$form_state['values']['realname_registration_lastname_field'].t($err_textfield));
  }

  // Because the field is used in creating usernames, it should be required.
  if($firstname_instance['required'] != 1) {
    form_set_error('realname_registration_firstname_field', t($err_pretext).$form_state['values']['realname_registration_firstname_field'].t($err_req));
  }
  if($lastname_instance['required'] != 1) {
    form_set_error('realname_registration_lastname_field', t($err_pretext).$form_state['values']['realname_registration_lastname_field'].t($err_req));
  }
}