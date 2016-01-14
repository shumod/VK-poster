<?php

/**
 * CF config form.
 */
function vkoa_config_form($form, &$form_state) {
  $form = array();
 
  $form['vkoa_app_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Application ID'),
    '#default_value' => variable_get('vkoa_app_id', 5217521),
    '#required' => TRUE,
  );
 
  return system_settings_form($form);
}