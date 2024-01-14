/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
// #include "keycode_str_converter.h"
#include <sendstring_jis.h>  // macro sendstring for jis keyboard マクロ文字列送信時に日本語キーボード設定での文字化け回避

enum custom_keycodes {
    ARROW_1 = SAFE_RANGE,
    ARROW_2,
    Z_TAB,
    Z_UP,
    Z_DOWN,
    Z_LEFT,
    Z_RIGHT,
    LCS_T,
    X_ONE,
    X_TWO,
    X_THREE,
    X_FOUR,
    X_FIVE,
    X_SIX
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  JP_AT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, JP_SCLN, JP_COLN,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, JP_COMM,  JP_DOT, JP_SLSH,  JP_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_MHEN,   MO(1),  KC_SPC,     KC_ENT,   MO(2), LGUI_T(KC_HENK)
                                      //`--------------------------'  `--------------------------'
  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      Z_TAB, KC_F12, LCTL(KC_W), LCTL(KC_PGUP), LCTL(KC_PGDN), LCS_T,           KC_HOME,  KC_ESC,  KC_NO,   KC_END,  KC_NO,   JP_EQL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, LCTL(KC_A), LCTL(KC_S), LCTL(KC_D), LCTL(KC_F), LCTL(KC_G),      Z_LEFT,   Z_DOWN,  Z_UP,    Z_RIGHT, JP_SCLN, JP_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_B),      KC_BSPC,  KC_DEL,  JP_LBRC, JP_RBRC, ARROW_1, JP_CIRC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_MHEN,  KC_TRNS,  KC_SPC,   LALT(KC_ENT), KC_TRNS, LGUI_T(KC_HENK)
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB,  KC_F11,  KC_F2,   KC_F3,   LALT(KC_F4), KC_F5,                    X_ONE,   X_TWO,   X_THREE, X_FOUR,  X_FIVE,  X_SIX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    JP_COLN,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, JP_EXLM, JP_DQUO, JP_HASH, JP_DLR, JP_PERC,                      JP_AMPR, JP_QUOT, JP_LPRN, JP_RPRN, LSFT(JP_YEN), JP_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_MHEN, KC_TRNS, KC_SPC,     KC_ENT, KC_TRNS, LGUI_T(KC_HENK)
                                      //`--------------------------'  `--------------------------'
  )
};

bool is_lalt_pressed = false;
bool is_lwin_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ARROW_1:
            if (record->event.pressed) {
                SEND_STRING("->");
            }
            break;

        case ARROW_2:
            if (record->event.pressed) {
                SEND_STRING("=>");
            }
            break;

        case Z_TAB:
            if (record->event.pressed) {
                register_code(KC_LALT);
                register_code(KC_TAB);
                is_lalt_pressed = true;
            } else {
                unregister_code(KC_TAB);
            }
            break;

        case Z_UP:
            if (record->event.pressed) {
                register_code(KC_UP);
            } else {
                unregister_code(KC_UP);
            }
            break;

        case Z_DOWN:
            if (record->event.pressed) {
                register_code(KC_DOWN);
            } else {
                unregister_code(KC_DOWN);
            }
            break;

        case Z_LEFT:
            if (record->event.pressed) {
                register_code(KC_LEFT);
            } else {
                unregister_code(KC_LEFT);
            }
            break;

        case Z_RIGHT:
            if (record->event.pressed) {
                register_code(KC_RIGHT);
            } else {
                unregister_code(KC_RIGHT);
            }
            break;

        case X_ONE:
            if (record->event.pressed) {
                register_code(KC_LWIN);
                register_code(KC_1);
                is_lwin_pressed = true;
            } else {
                unregister_code(KC_1);
            }
            break;

        case X_TWO:
            if (record->event.pressed) {
                register_code(KC_LWIN);
                register_code(KC_2);
                is_lwin_pressed = true;
            } else {
                unregister_code(KC_2);
            }
            break;

        case X_THREE:
            if (record->event.pressed) {
                register_code(KC_LWIN);
                register_code(KC_3);
                is_lwin_pressed = true;
            } else {
                unregister_code(KC_3);
            }
            break;

        case X_FOUR:
            if (record->event.pressed) {
                register_code(KC_LWIN);
                register_code(KC_4);
                is_lwin_pressed = true;
            } else {
                unregister_code(KC_4);
            }
            break;

        case X_FIVE:
            if (record->event.pressed) {
                register_code(KC_LWIN);
                register_code(KC_5);
                is_lwin_pressed = true;
            } else {
                unregister_code(KC_5);
            }
            break;

        case X_SIX:
            if (record->event.pressed) {
                register_code(KC_LWIN);
                register_code(KC_6);
                is_lwin_pressed = true;
            } else {
                unregister_code(KC_6);
            }
            break;

        case LCS_T:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                register_code(KC_T);
            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_LSFT);
                unregister_code(KC_T);
            }
            break;

        default:
            if (is_lalt_pressed) {
                unregister_code(KC_LALT);
                is_lalt_pressed = false;
            }
            if (is_lwin_pressed) {
                unregister_code(KC_LWIN);
                is_lwin_pressed = false;
            }
            break;
    }
    return true;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
}

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   if (record->event.pressed) {
//     set_keylog(keycode, record);
//   }
//   return true;
// }
#endif // OLED_ENABLE
