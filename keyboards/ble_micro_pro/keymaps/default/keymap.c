/* Copyright 2019 sekigon-gonnoc
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
#include "bmp.h"
#include "bmp_custom_keycode.h"
#include "keycode_str_converter.h"
#include <sendstring_jis.h> // macro sendstring for jis keyboard マクロ文字列送信時に日本語キーボード設定での文字化け回避

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    ARROW = SAFE_RANGE,
    Z_TAB,
    Z_UP,
    Z_DOWN,
    Z_LEFT,
    Z_RIGHT,
    LCS_T
};

const key_string_map_t custom_keys_user = {
    .start_kc = ARROW,
    .end_kc = LCS_T,
    .key_strings = "ARROW\0Z_TAB\0Z_UP\0Z_DOWN\0Z_LEFT\0Z_RIGHT\0LCS_T\0"
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    {{
    KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I,
        KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S
    }}
};

bool is_lalt_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool continue_process = process_record_user_bmp(keycode, record);
    if (continue_process == false)
    {
        return false;
    }
    switch (keycode) {
        case ARROW:
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

        default:
            if (is_lalt_pressed) {
                unregister_code(KC_LALT);
                is_lalt_pressed = false;
            }
            break;
        }
    return true;
}
