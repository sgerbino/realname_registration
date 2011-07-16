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

  // If the content_profile module doesn't exist we must make sure these values are reset.
  if (!module_exists('content_profile_registration')) {
    variable_set('realname_registration_use_content_profile_firstname_field', 0);
    variable_set('realname_registration_content_profile_firstname_field_node', 0);
    variable_set('realname_registration_use_content_profile_middlename_field', 0);
    variable_set('realname_registration_content_profile_middlename_field_node', 0);
    variable_set('realname_registration_use_content_profile_lastname_field', 0);
    variable_set('realname_registration_content_profile_lastname_field_node', 0);
  }
  
  $field_req = '<ul><li>'
  . t('The field name is correct and represents an existing profile field') . '</li><li>'
  . t('The field is required and displays on the registration form') . '</li></ul>';

  $form['realname_registration_firstname_field'] = array(
    '#type' => 'textfield',
    '#title' => t('First name field'),
    '#required' => TRUE,
    '#default_value' => variable_get('realname_registration_firstname_field', ''),
    '#description' => t('The name of your first name field. Ensure that:') . $field_req,
  );

  if (module_exists('content_profile_registration')) {
    $form['realname_registration_use_content_profile_firstname_field'] = array(
        '#type' => 'checkbox',
        '#title' => t('Use the content profile module to store your first names.'),
        '#default_value' => variable_get('realname_registration_use_content_profile_firstname_field', 0),
        '#description' => t('When this checkbox is checked, Realname registration will use content profile fields to store first names.'),
    );
    $form['realname_registration_content_profile_firstname_field_node'] = array(
      '#type' => 'value',
      '#value' => variable_get('realname_registration_content_profile_firstname_field_node', ''),
    );
  }

  $form['realname_registration_middlename_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Middle name field'),
    '#default_value' => variable_get('realname_registration_middlename_field', ''),
    '#description' => t('The name of your middle name field. Ensure that:') . '<ul><li>'
      . t('The field name is correct and represents an existing profile field') . '</li><li>'
      . t('The field is displayed on the registration form') . '</li></ul>',
  );

  if (module_exists('content_profile_registration')) {
    $form['realname_registration_use_content_profile_middlename_field'] = array(
        '#type' => 'checkbox',
        '#title' => t('Use the content profile module to store your middle names.'),
        '#default_value' => variable_get('realname_registration_use_content_profile_middlename_field', 0),
        '#description' => t('When this checkbox is checked, Realname registration will use content profile fields to store middle names.'),
    );
    $form['realname_registration_content_profile_middlename_field_node'] = array(
      '#type' => 'value',
      '#value' => variable_get('realname_registration_content_profile_middlename_field_node', ''),
    );
  }

  $form['realname_registration_lastname_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name field'),
    '#required' => TRUE,
    '#default_value' => variable_get('realname_registration_lastname_field',''),
    '#description' => t('The name of your last name field. Ensure that:') . $field_req,
  );

  if (module_exists('content_profile_registration')) {
    $form['realname_registration_use_content_profile_lastname_field'] = array(
        '#type' => 'checkbox',
        '#title' => t('Use the content profile module to store your last names.'),
        '#default_value' => variable_get('realname_registration_use_content_profile_lastname_field', 0),
        '#description' => t('When this checkbox is checked, Realname registration will use content profile fields to store last names.'),
    );
    $form['realname_registration_content_profile_lastname_field_node'] = array(
      '#type' => 'value',
      '#value' => variable_get('realname_registration_content_profile_lastname_field_node', ''),
    );
  }

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
    '#description' => t("Ensures that the first letter of the users first name, middle name, and last name are capitalized."),
  );

  $form['realname_registration_tolower'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force lowercase'),
    '#default_value' => variable_get('realname_registration_tolower', 1),
    '#description' => t("Usernames will be created using only lowercase characters."),
  );

  $form['realname_registration_use_validation'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Realname registration validation'),
    '#default_value' => variable_get('realname_registration_use_validation', 1),
    '#description' => t('Use regex to validate real names (/^[A-ZÀ-ÖØ-öø-ÿ -]+$/i)'),
  );

  $form['#validate'][] = 'realname_registration_settings_validate';
  return system_settings_form($form);
}

function realname_registration_settings_validate($form, &$form_state) {
  $err_pretext = t('The field name') . ', <em>';
  $err_register = '</em>, ' . t("you've provided must be displayed on the registration form.");
  $err_req = '</em>, ' . t("you've provided must be required.");
  $err_unknown = '</em>, ' . t("you've provided either does not exist or is not a profile field.");
  $err_textfield = '</em>, ' . t('must use textfield widget.');
  
  // Validation for the first name field.
  if ($form_state['values']['realname_registration_use_content_profile_firstname_field'] == 0 ) {
    $firstname_field = db_fetch_object(db_query("SELECT type, required, register FROM {profile_fields} WHERE name = '%s'", $form_state['values']['realname_registration_firstname_field']));
    if (empty($firstname_field)) {
      form_set_error('realname_registration_firstname_field', $err_pretext . $form_state['values']['realname_registration_firstname_field'] . $err_unknown);
    }
    if ($firstname_field->type != 'textfield') {
      form_set_error('realname_registration_firstname_field', $err_pretext . $form_state['values']['realname_registration_firstname_field'] . $err_textfield);
    }
    if ($firstname_field->required != 1) {
      form_set_error('realname_registration_firstname_field', $err_pretext . $form_state['values']['realname_registration_firstname_field'] . $err_req);
    }
    if ($firstname_field->register != 1) {
      form_set_error('realname_registration_firstname_field', $err_pretext . $form_state['values']['realname_registration_firstname_field'] . $err_register);
    }
  }
  else {
    $sql = "SELECT i.field_name, i.type_name, i.widget_type, c.required "
    . "FROM {content_node_field_instance} AS i "
    . "LEFT JOIN {content_node_field} AS c "
    . "ON i.field_name = c.field_name "
    . "WHERE i.field_name = '%s'";
    $firstname_field = db_fetch_object(db_query($sql, $form_state['values']['realname_registration_firstname_field']));
    if (empty($firstname_field)) {
      form_set_error('realname_registration_firstname_field', $err_pretext . $form_state['values']['realname_registration_firstname_field'] . $err_unknown);
    }
    if ($firstname_field->widget_type != 'text_textfield') {
      form_set_error('realname_registration_firstname_field', $err_pretext . $form_state['values']['realname_registration_firstname_field'] . $err_textfield);
    }
    if ($firstname_field->required != 1) {
      form_set_error('realname_registration_firstname_field', $err_pretext . $form_state['values']['realname_registration_firstname_field'] . $err_req);
    }
    $types = array_keys(content_profile_get_types('names', 'registration_use'));
    $match = FALSE;
    foreach ($types as $type) {
      if ($type == $firstname_field->type_name) {
        $match = TRUE;
        $form_state['values']['realname_registration_content_profile_firstname_field_node'] = $type;
      }
    }
    if (!$match) {
      form_set_error('realname_registration_firstname_field', $err_pretext . $form_state['values']['realname_registration_firstname_field'] . $err_register);
    }
  }
  
  // Validation for the middle name field.
  if (!empty($form_state['values']['realname_registration_middlename_field'])) {
    if ($form_state['values']['realname_registration_use_content_profile_middlename_field'] == 0) {
      $middlename_field = db_fetch_object(db_query("SELECT type, required, register FROM {profile_fields} WHERE name = '%s'", $form_state['values']['realname_registration_middlename_field']));
      if (empty($middlename_field)) {
        form_set_error('realname_registration_middlename_field', $err_pretext . $form_state['values']['realname_registration_middlename_field'] . $err_unknown);
      }
      if ($middlename_field->type != 'textfield') {
        form_set_error('realname_registration_middlename_field', $err_pretext . $form_state['values']['realname_registration_middlename_field'] . $err_textfield);
      }
      if ($middlename_field->register != 1) {
        form_set_error('realname_registration_middlename_field', $err_pretext . $form_state['values']['realname_registration_middlename_field'] . $err_register);
      }
    }
    else {
      $sql = "SELECT i.field_name, i.type_name, i.widget_type, c.required "
      . "FROM {content_node_field_instance} AS i "
      . "LEFT JOIN {content_node_field} AS c "
      . "ON i.field_name = c.field_name "
      . "WHERE i.field_name = '%s'";
      $middlename_field = db_fetch_object(db_query($sql, $form_state['values']['realname_registration_middlename_field']));
      if (empty($middlename_field)) {
        form_set_error('realname_registration_middlename_field', $err_pretext . $form_state['values']['realname_registration_middlename_field'] . $err_unknown);
      }
      if ($middlename_field->widget_type != 'text_textfield') {
        form_set_error('realname_registration_middlename_field', $err_pretext . $form_state['values']['realname_registration_middlename_field'] . $err_textfield);
      }
      $types = array_keys(content_profile_get_types('names', 'registration_use'));
      $match = FALSE;
      foreach ($types as $type) {
        if ($type == $middlename_field->type_name) {
          $match = TRUE;
          $form_state['values']['realname_registration_content_profile_middlename_field_node'] = $type;
        }
      }
      if (!$match) {
        form_set_error('realname_registration_middlename_field', $err_pretext . $form_state['values']['realname_registration_middlename_field'] . $err_register);
      }
    }
  }

  // Validation for the last name field.
  if ($form_state['values']['realname_registration_use_content_profile_lastname_field'] == 0) {
    $lastname_field = db_fetch_object(db_query("SELECT type, required, register FROM {profile_fields} WHERE name = '%s'", $form_state['values']['realname_registration_lastname_field']));
    if (empty($lastname_field)) {
      form_set_error('realname_registration_lastname_field', $err_pretext . $form_state['values']['realname_registration_lastname_field'] . $err_unknown);
    }
    if ($lastname_field->required != 1) {
      form_set_error('realname_registration_lastname_field', $err_pretext . $form_state['values']['realname_registration_lastname_field'] . $err_req);
    }
    if ($lastname_field->type != 'textfield') {
      form_set_error('realname_registration_lastname_field', $err_pretext . $form_state['values']['realname_registration_lastname_field'] . $err_textfield);
    }
    if ($lastname_field->register != 1) {
      form_set_error('realname_registration_lastname_field', $err_pretext . $form_state['values']['realname_registration_lastname_field'] . $err_register);
    }
  }
  else {
    $sql = "SELECT i.field_name, i.type_name, i.widget_type, c.required "
    . "FROM {content_node_field_instance} AS i "
    . "LEFT JOIN {content_node_field} AS c "
    . "ON i.field_name = c.field_name "
    . "WHERE i.field_name = '%s'";
    $lastname_field = db_fetch_object(db_query($sql, $form_state['values']['realname_registration_lastname_field']));
    if (empty($lastname_field)) {
      form_set_error('realname_registration_lastname_field', $err_pretext . $form_state['values']['realname_registration_lastname_field'] . $err_unknown);
    }
    if ($lastname_field->required != 1) {
      form_set_error('realname_registration_lastname_field', $err_pretext . $form_state['values']['realname_registration_lastname_field'] . $err_req);
    }
    if ($lastname_field->widget_type != 'text_textfield') {
      form_set_error('realname_registration_lastname_field', $err_pretext . $form_state['values']['realname_registration_lastname_field'] . $err_textfield);
    }
    $types = array_keys(content_profile_get_types('names', 'registration_use'));
    $match = FALSE;
    foreach ($types as $type) {
      if ($type == $lastname_field->type_name) {
        $match = TRUE;
        $form_state['values']['realname_registration_content_profile_lastname_field_node'] = $type;
      }
    }
    if (!$match) {
      form_set_error('realname_registration_lastname_field', $err_pretext . $form_state['values']['realname_registration_lastname_field'] . $err_register);
    }
  }
}