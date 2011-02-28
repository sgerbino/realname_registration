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

  $form['realname_registration_format'] = array(
    '#type' => 'radios',
    '#title' => t('Username format'),
    '#description' => t('Select the format in which Realname registration will create new usernames.'),
    '#default_value' => variable_get('realname_registration_format', 'Firstname and lastname separated by a space'),
    '#options' => array(t('Firstname and lastname separated by a space'), t('First initial and lastname')),
    '#required' => TRUE,
  );

  $form['realname_registration_tolower'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force lowercase'),
    '#default_value' => variable_get('realname_registration_tolower'),
    '#description' => t("Usernames will be created using only lowercase characters."),
  );

  return system_settings_form($form);
}