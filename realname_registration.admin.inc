<?php
/**
 * @file
 * Admin page callbacks for the realname_registration module.
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

  $field_req = '
<ul>
  <li>' . t('The field name is correct and represents an existing field') . '</li>
  <li>' . t('The field is associated with the') . ' <em>' . t('user') . '</em> ' . t('entity') . '</li>
  <li>' . t('The field is required and displays on the registration form') . '</li>
</ul>
';

  $form['realname_registration_firstname_field'] = array(
    '#type' => 'textfield',
    '#title' => t('First name field'),
    '#default_value' => variable_get('realname_registration_firstname_field'),
    '#description' => t('The name of your first name field. Ensure that:') . $field_req,
    '#required' => TRUE,
  );

  $form['realname_registration_middlename_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Middle name field'),
    '#default_value' => variable_get('realname_registration_middlename_field'),
    '#description' => 
      t('The name of your middle name field. Ensure that:')
      . '<ul>'
      . '<li>' . t('The field name is correct and represents an existing field') . '</li>'
      . '<li>' . t('The field is associated with the') . ' <em>' . t('user') . '</em> ' . t('entity') . '</li>'
      . '</ul>',
  );

  $form['realname_registration_lastname_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name field'),
    '#default_value' => variable_get('realname_registration_lastname_field'),
    '#description' => t('The name of your last name field. Ensure that:') . $field_req,
    '#required' => TRUE,
  );

  $form['realname_registration_format'] = array(
    '#type' => 'radios',
    '#title' => t('Username format'),
    '#description' => t('Select the format in which Realname registration will create new usernames.'),
    '#default_value' => variable_get('realname_registration_format', 0),
    '#options' => array(
      t('First name and last name (e.g., John Smith)'),
      t('First initial and last name (e.g., JSmith)'),
      t('First name, middle name, and last name (e.g., John Jacob Smith)'),
      t('First name, middle initial, and last name (e.g., John J Smith)'),
      t('First initial, middle initial, and last name (e.g., JJSmith)')
    ),
    '#required' => TRUE,
  );

  $form['realname_registration_ucfirst'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force the first letters of the first and last names to uppercase'),
    '#default_value' => variable_get('realname_registration_ucfirst', 1),
    '#description' => t('Ensures that the first letter of the users first name and first letter of the users last name are capitalized.'),
  );

  $form['realname_registration_tolower'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force lowercase'),
    '#default_value' => variable_get('realname_registration_tolower'),
    '#description' => t('Usernames will be created using only lowercase characters.'),
  );

  $form['realname_registration_use_validation'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Realname registration validation'),
    '#default_value' => variable_get('realname_registration_use_validation', 1),
    '#description' => t('Use regex to validate real names (/^[A-ZÀ-ÖØ-öø-ÿ]+$/i)'),
  );

  $form['#validate'][] = 'realname_registration_settings_validate';
  return system_settings_form($form);
}

function realname_registration_settings_validate($form, &$form_state) {
  $err_pretext = t('The field name') . ', <em>';
  $err_req = '</em>, ' . t("you've provided must be required.");
  $err_unknown = '</em>, ' . t("you've provided either does not exist or is not associated with the user entity and bundle.");
  $err_textfield = '</em>, ' . t('must use textfield widget.');

  // Validate the first name field.
  $firstname_instance = field_info_instance('user', $form_state['values']['realname_registration_firstname_field'], 'user');
  if (!isset($firstname_instance)) {
    form_set_error('realname_registration_firstname_field', $err_pretext . $form_state['values']['realname_registration_firstname_field'] . $err_unknown);
  }
  if ($firstname_instance['widget']['type'] != 'text_textfield') {
    form_set_error('realname_registration_firstname_field', $err_pretext . $form_state['values']['realname_registration_firstname_field'] . $err_textfield);
  }
  if ($firstname_instance['required'] != 1) {
    form_set_error('realname_registration_firstname_field', $err_pretext . $form_state['values']['realname_registration_firstname_field'] . $err_req);
  }

  // Validate the middle name field if it is used.
  if (!empty($form_state['values']['realname_registration_middlename_field'])) {
    $middlename_instance = field_info_instance('user', $form_state['values']['realname_registration_middlename_field'], 'user');
    if (!isset($middlename_instance)) {
      form_set_error('realname_registration_middlename_field', $err_pretext . $form_state['values']['realname_registration_middlename_field'] . $err_unknown);
    }
    if ($middlename_instance['widget']['type'] != 'text_textfield') {
      form_set_error('realname_registration_middlename_field', $err_pretext . $form_state['values']['realname_registration_middlename_field'] . $err_textfield);
    }
  }
  else {
    // If there is no middle name field provided, we can't base usernames off the middle initial.
    if ($form_state['values']['realname_registration_format'] == 2 || $form_state['values']['realname_registration_format'] == 3) {
      form_set_error('realname_registration_format', t('A valid middle name field is required for this username format.'));
    }
  }

  // Validate the last name field.
  $lastname_instance = field_info_instance('user', $form_state['values']['realname_registration_lastname_field'], 'user');
  if (!isset($lastname_instance)) {
    form_set_error('realname_registration_lastname_field', $err_pretext . $form_state['values']['realname_registration_lastname_field'] . $err_unknown);
  }
  if ($lastname_instance['widget']['type'] != 'text_textfield') {
    form_set_error('realname_registration_lastname_field', $err_pretext . $form_state['values']['realname_registration_lastname_field'] . $err_textfield);
  }
  if ($lastname_instance['required'] != 1) {
    form_set_error('realname_registration_lastname_field', $err_pretext . $form_state['values']['realname_registration_lastname_field'] . $err_req);
  }
}