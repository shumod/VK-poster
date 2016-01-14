<?php

function vkoa_form($form, &$form_state) {
  $form = array();

  $link = '1. <a href="https://oauth.vk.com/authorize?client_id=' . variable_get('vkoa_app_id') . '&scope=offline,docs,photos,video,audio,wall,friends,groups&redirect_uri=https://oauth.vk.com/blank.html&response_type=token" target="_blank">Получить токен</a>';
  $form['token'] = array(
    '#markup' => $link,
  );

  $form['token_url'] = array(
    '#title' => '2. Вставьте полученную строку в поле',
    '#type' => 'textfield',
    '#maxlength' => 256, 
  );

  $form['submit'] = array(
    '#type' => 'submit', 
    '#value' => 'Получить токен',
  );

  return $form;
}

//проверяем, чтобы строка с токеном не была пустой
function vkoa_form_validate($form, &$form_state) {
  if($form_state['values']['token_url'] == ''){
    form_set_error('token_url', 'Строка пуста :(');
  }
}

//сохраняем токен и user id в профиле
function vkoa_form_submit($form, &$form_state) {
  $url = $form_state['values']['token_url'];
  $parse_url = drupal_parse_url(str_replace('#', '?', $url));
  $vk_token = $parse_url['query']['access_token'];
  $vk_user_id = $parse_url['query']['user_id'];
  $user = user_load(arg(1));
  $user_wrapper = entity_metadata_wrapper('user', $user);
  $user_wrapper->field_token->set($vk_token);
  $user_wrapper->field_user_id->set($vk_user_id);
  $user_wrapper->save();
  drupal_set_message('Токен и user id успешно сохранён в ' . l('профиле', 'user/' . $user->uid . '/edit'));
}