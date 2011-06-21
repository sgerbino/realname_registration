<?php
/**
 * @file
 * Token callbacks for the realname_registration module.
 */

/**
 * Implements hook_token_info().
 */
function realname_registration_token_info() {
  $user['first-name'] = array(
    'name' => t('First name'),
    'description' => t("The first name of the user."),
  );
  $user['middle-name'] = array(
    'name' => t('Middle name'),
    'description' => t("The middle name of the user."),
  );
  $user['last-name'] = array(
    'name' => t('Last name'),
    'description' => t("The last name of the user."),
  );
  $user['first-initial'] = array(
    'name' => t('First inital'),
    'description' => t("The first initial of the user."),
  );
  $user['middle-initial'] = array(
    'name' => t('Middle inital'),
    'description' => t("The middle initial of the user."),
  );
  $user['last-initial'] = array(
    'name' => t('Last initial'),
    'description' => t("The last initial of the user."),
  );

  return array( 'tokens' => array('user' => $user) );
}

/**
 * Implements hook_tokens().
 */
function realname_registration_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $sanitize = !empty($options['sanitize']);
  $replacements = array();

  $field_firstname = variable_get('realname_registration_firstname_field');
  $field_middlename = variable_get('realname_registration_middlename_field');
  $field_lastname = variable_get('realname_registration_lastname_field');

  if(isset($field_firstname) && isset($field_lastname)) {
    if ($type == 'user' && !empty($data['user'])) {
      $account = $data['user'];
      foreach ($tokens as $name => $original) {
        switch ($name) {
          case 'first-name':
            $replacements[$original] = !empty($account->$field_firstname) ? $account->{$field_firstname}['und']['0']['value'] : '';
            break;

          case 'middle-name':
            $replacements[$original] = !empty($account->$field_middlename) ? $account->{$field_middlename}['und']['0']['value'] : '';
            break;

          case 'last-name':
            $replacements[$original] = !empty($account->$field_lastname) ? $account->{$field_lastname}['und']['0']['value'] : '';
            break;

          case 'first-initial':
            $replacements[$original] = !empty($account->$field_firstname) ? drupal_substr($account->{$field_firstname}['und']['0']['value'], 0, 1) : '';
            break;
 
          case 'middle-initial':
            $replacements[$original] = !empty($account->$field_middlename) ? drupal_substr($account->{$field_middlename}['und']['0']['value'], 0, 1) : '';
            break;

          case 'last-initial':
            $replacements[$original] = !empty($account->$field_lastname) ? drupal_substr($account->{$field_lastname}['und']['0']['value'], 0, 1) : '';
            break;
        }
      }
    }
  }

  if ($type == 'current-user') {
    $account = user_load($GLOBALS['user']->uid);
    $replacements += token_generate('user', $tokens, array('user' => $account), $options);
  }
  return $replacements;
}