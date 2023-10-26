/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
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
#include <os_detection.h>

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
enum custom_layers {
    _BL,
    _FL,
};

typedef union {
  uint32_t raw;
  struct {
    uint8_t keys_color;
    uint8_t mods_color;
    uint8_t pads_color;
    uint8_t side_color;
  };
} user_config_t;

user_config_t user_config;

const uint8_t PROGMEM RGB_GROUP_FN[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
const uint8_t PROGMEM RGB_GROUP_MOD[] = { 18, 31, 36, 49, 54, 66, 70, 81, 87, 88, 89, 91, 92, 93 };
const uint8_t PROGMEM RGB_GROUP_PAD[] = { 14, 15, 16, 17, 32, 33, 34, 35, 50, 51, 52, 53, 67, 68, 69, 83, 84, 85, 86, 97, 98 };
const uint8_t PROGMEM RGB_GROUP_SIDE[] = { 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120 };

const uint8_t RGB_GROUP_FN_SIZE = 14;
const uint8_t RGB_GROUP_MOD_SIZE = 14;
const uint8_t RGB_GROUP_PAD_SIZE = 21;
const uint8_t RGB_GROUP_SIDE_SIZE = 20;

const uint8_t COLORS_SIZE = 12;
const uint8_t PROGMEM COLORS[][3] = { {HSV_BLUE}, {HSV_WHITE}, {HSV_YELLOW}, {HSV_RED}, {HSV_GREEN}, {HSV_ORANGE}, {HSV_AZURE}, {HSV_CORAL}, {HSV_CYAN}, {HSV_GOLDENROD}, {HSV_MAGENTA}, {HSV_PURPLE} };
const uint8_t DEFAULT_KEYS_COLOR = 1;
const uint8_t DEFAULT_MODS_COLOR = 3;
const uint8_t DEFAULT_PADS_COLOR = 0;
const uint8_t DEFAULT_SIDE_COLOR = 2;

uint8_t keys_color[3];
uint8_t mods_color[3];
uint8_t pads_color[3];
uint8_t side_color[3];

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: Base Layer (Default Layer)
   */
[_BL] = LAYOUT(
  QK_GESC,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_DEL,   KC_INS,   KC_PGUP,  KC_PGDN,
  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
  KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,   KC_P4,    KC_P5,    KC_P6,
  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_P1,    KC_P2,    KC_P3,    KC_PENT,
  KC_LCTL,  KC_LGUI,  KC_LALT,                      KC_SPC,                                 KC_RALT,  MO(_FL),  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,    KC_PDOT),

  /* Keymap _FL: Function Layer
   */
[_FL] = LAYOUT(
  QK_BOOT,  KC_MYCM,  KC_WHOM,  KC_CALC,  KC_MSEL,  KC_MPRV,  KC_MRWD,  KC_MPLY,  KC_MSTP,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,   _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
  RGB_TOG,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,  _______,  _______,
  _______,  RGB_HUI,  RGB_HUD,  RGB_SPD,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_VAI,   _______,  _______,  _______,  _______,
  _______,  UC_WIN,   _______,                      _______,                                _______,  _______,  _______,  RGB_RMOD,  RGB_VAD,  RGB_MOD,  _______,  _______)
};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;

  // Should load from eeprom here...
  user_config.raw = 0;
  user_config.keys_color = DEFAULT_KEYS_COLOR;
  user_config.mods_color = DEFAULT_MODS_COLOR;
  user_config.pads_color = DEFAULT_PADS_COLOR;
  user_config.side_color = DEFAULT_SIDE_COLOR;

  keys_color[0] = pgm_read_byte(&COLORS[user_config.keys_color][0]);
  keys_color[1] = pgm_read_byte(&COLORS[user_config.keys_color][1]);
  keys_color[2] = pgm_read_byte(&COLORS[user_config.keys_color][2]);

  mods_color[0] = pgm_read_byte(&COLORS[user_config.mods_color][0]);
  mods_color[1] = pgm_read_byte(&COLORS[user_config.mods_color][1]);
  mods_color[2] = pgm_read_byte(&COLORS[user_config.mods_color][2]);

  pads_color[0] = pgm_read_byte(&COLORS[user_config.pads_color][0]);
  pads_color[1] = pgm_read_byte(&COLORS[user_config.pads_color][1]);
  pads_color[2] = pgm_read_byte(&COLORS[user_config.pads_color][2]);

  side_color[0] = pgm_read_byte(&COLORS[user_config.side_color][0]);
  side_color[1] = pgm_read_byte(&COLORS[user_config.side_color][1]);
  side_color[2] = pgm_read_byte(&COLORS[user_config.side_color][2]);
}

RGB hsv_to_rgb_keep_brightness(int h, int s, int v) {
    HSV hsv = { h, s, v };
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }
    return hsv_to_rgb(hsv);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    uint32_t mode = rgblight_get_mode();
    // assign colors if the matrix is on and the current mode
    // is SOLID COLORS => No animations running
    if(rgb_matrix_config.enable == 1 && mode == 1) { // && swap_colors) {

        RGB rgb_color = hsv_to_rgb_keep_brightness(keys_color[0], keys_color[1], keys_color[2]);
        RGB rgb_mods_color = hsv_to_rgb_keep_brightness(mods_color[0], mods_color[1], mods_color[2]);
        RGB rgb_pads_color = hsv_to_rgb_keep_brightness(pads_color[0], pads_color[1], pads_color[2]);
        RGB rgb_side_color = hsv_to_rgb_keep_brightness(side_color[0], side_color[1], side_color[2]);

        for (uint8_t i = led_min; i < led_max; i++) {
            rgb_matrix_set_color(i, rgb_color.r, rgb_color.g, rgb_color.b);
        }

        // FN group
        for (uint8_t i = 0; i < RGB_GROUP_FN_SIZE; i++) {
            rgb_matrix_set_color(RGB_GROUP_FN[i], rgb_mods_color.r, rgb_mods_color.g, rgb_mods_color.b);
        }
        // Mod group
        for (uint8_t i = 0; i < RGB_GROUP_MOD_SIZE; i++) {
            rgb_matrix_set_color(RGB_GROUP_MOD[i], rgb_mods_color.r, rgb_mods_color.g, rgb_mods_color.b);
        }
        // Pad group
        for (uint8_t i = 0; i < RGB_GROUP_PAD_SIZE; i++) {
            rgb_matrix_set_color(RGB_GROUP_PAD[i], rgb_pads_color.r, rgb_pads_color.g, rgb_pads_color.b);
        }
        // Side lights
        for (uint8_t i = 0; i < RGB_GROUP_SIDE_SIZE; i++) {
            rgb_matrix_set_color(RGB_GROUP_SIDE[i], rgb_side_color.r, rgb_side_color.g, rgb_side_color.b);
        }

        // for (uint8_t i = 0; i < led_max; i++) {
        //     if (i > 98) {
        //         rgb_matrix_set_color(i, rgb_mods_color.r, rgb_mods_color.g, rgb_mods_color.b);
        //     }
        // }
    }
    return true;
}
