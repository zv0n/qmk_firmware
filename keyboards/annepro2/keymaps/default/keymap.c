 /* Copyright 2021 OpenAnnePro community
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#include QMK_KEYBOARD_H

static ap2_led_t caps_lock_color = {.p.red = 0xFF, .p.green = 0x33, .p.blue = 0xDD, .p.alpha = 0xff};
static ap2_led_t layer_indicator_color = {.p.red = 0xFF, .p.green = 0x55, .p.blue = 0x00, .p.alpha = 0xff};

enum anne_pro_layers {
    BASE,
    FN1,
    FN2,
    GAMING,
};

// clang-format off
// Key symbols are based on QMK. Use them to remap your keyboard
/*
* Layer BASE
* ,-----------------------------------------------------------------------------------------.
* | esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
* |-----------------------------------------------------------------------------------------+
* | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    |
* |-----------------------------------------------------------------------------------------+
* | Caps    |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Enter    |
* |-----------------------------------------------------------------------------------------+
* | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |    Shift       |
* |-----------------------------------------------------------------------------------------+
* | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  FN2  | Ctrl  |
* \-----------------------------------------------------------------------------------------/
* Layer TAP in BASE
* ,-----------------------------------------------------------------------------------------.
* |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
* |-----------------------------------------------------------------------------------------+
* |        |     |     |     |     |     |     |     |     |     |     |     |     |        |
* |-----------------------------------------------------------------------------------------+
* |         |     |     |     |     |     |     |     |     |     |     |     |             |
* |-----------------------------------------------------------------------------------------+
* |            |     |     |     |     |     |     |     |     |     |     |       UP       |
* |-----------------------------------------------------------------------------------------+
* |       |       |       |                                 |       |  LEFT | DOWN  | RIGHT |
* \-----------------------------------------------------------------------------------------/
*/
 const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [BASE] = LAYOUT_60_ansi( /* Base */
    KC_ESC,           KC_1,    KC_2,    KC_3, KC_4, KC_5, KC_6,   KC_7, KC_8, KC_9,    KC_0,             KC_MINS,          KC_EQL,        KC_BSPC,
    KC_TAB,           KC_Q,    KC_W,    KC_E, KC_R, KC_T, KC_Y,   KC_U, KC_I, KC_O,    KC_P,             KC_LBRC,          KC_RBRC,       KC_BSLS,
    MO(FN1),          KC_A,    KC_S,    KC_D, KC_F, KC_G, KC_H,   KC_J, KC_K, KC_L,    KC_SCLN,          KC_QUOT,          KC_ENT,
    KC_LSFT,                   KC_Z,    KC_X, KC_C, KC_V, KC_B,   KC_N, KC_M, KC_COMM, KC_DOT,           KC_SLSH,          KC_RSFT,
    KC_LCTL,          KC_LGUI, KC_LALT,                   KC_SPC,             KC_RALT, MO(FN1),          LT(FN2, KC_DOWN), KC_RCTL
),
  /*
  * Layer FN1
  * ,-----------------------------------------------------------------------------------------.
  * |  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |  DELETE   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  | UP  |  e  |  r  |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |LEFT |DOWN |RIGHT|  f  |  g  |  h  |  j  |  k  |  l  | PGUP|PGDN |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |V-UP |V-DWN|MUTE |  v  |  b  |  n  |  m  |  ,  |INSRT| DEL |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  FN2  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [FN1] = LAYOUT_60_ansi( /* FN1 */
     KC_GRV, KC_F1,     KC_F2,   KC_F3,   KC_F4, KC_F5,   KC_F6,   KC_F7,   KC_F8,      KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_DEL,
    _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, KC_PGUP,   KC_UP,  KC_PGDN, KC_PSCR, KC_SCRL, KC_PAUS, _______,
    _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT,  KC_INS,  KC_DEL, _______,
    KC_CAPS,          _______, _______, _______, _______, _______,  KC_END, _______,  _______, _______, _______, _______,
    _______, _______, _______,                            _______,                    _______, _______, MO(FN2), _______
),
  /*
  * Layer FN2
  * ,-----------------------------------------------------------------------------------------.
  * |  ~  | BT1 | BT2 | BT3 | BT4 |  F5 |  F6 | F7 | F8 | MOD | TOG | BRI- | BRI+ |    Bksp   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  | UP  |  e  |  r  |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |LEFT |DOWN |RIGHT|  f  |  g  |  h  |  j  |  k  |  l  | PGUP|PGDN |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |INSRT| DEL |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  FN2  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [FN2] = LAYOUT_60_ansi( /* FN2 */
    _______, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, KC_AP2_BT_UNPAIR, _______, _______, _______, KC_AP_RGB_MOD, KC_AP_RGB_TOG, KC_AP_RGB_VAD, KC_AP_RGB_VAI, _______,
    _______,    _______,    _______,    _______,    _______, _______, _______, _______, _______,       _______,       _______,       _______,       _______, _______,
    _______,    _______,    _______,    _______,    _______, _______, _______, _______, _______,       _______,       _______,       _______,       _______,
    _______,               TO(BASE), TO(GAMING),    _______, _______, _______, _______, _______,       _______,       _______,       _______,       _______,
    _______,    _______,    _______,                                  _______,                         _______,       MO(FN1),       MO(FN2),       _______
 ),
 [GAMING] = LAYOUT_60_ansi(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_AP_RGB_MOD, KC_AP_RGB_TOG, KC_AP_RGB_VAD, KC_AP_RGB_VAI, _______,
    _______, _______, _______, _______, _______, _______, _______, _______,   KC_UP,       _______,       _______,       _______,       _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN,      KC_RIGHT,       _______,       _______,       _______,
    _______,          _______, _______, _______, _______, _______, _______, _______,       _______,       _______,       _______,       _______,
    _______, _______, _______,                            _______,                         _______,       MO(FN1),       MO(FN2),       _______
 ),
};
// clang-format on


// The function to handle the caps lock logic
bool led_update_user(led_t leds) {
    if (leds.caps_lock) {
        ap2_led_set_sticky_key(2, 0, caps_lock_color);
    } else if (!leds.caps_lock) {
        ap2_led_unset_sticky_key(2, 0);
    }

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case FN1:
            break;
        case FN2:
            break;
        case GAMING:
            ap2_led_set_sticky_key(3, 3, layer_indicator_color);
            break;
        default:
            // Reset back to the current profile
            ap2_led_unset_sticky_row(3);
            break;
    }
    return state;
}