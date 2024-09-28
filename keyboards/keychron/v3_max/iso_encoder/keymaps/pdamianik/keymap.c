/* Copyright 2024 @ Keychron (https://www.keychron.com)
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
#include "keychron_common.h"
#include "raw_hid.h"

#include "lpm.h"
// #include "action.h"

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
    WIN_FN_SYS,
    WIN_MOD,
    WIN_MOD_SYS,

    LAYER_COUNT, // internal, must be last
};
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_tkl_iso(
        KC_CAPS,  KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,   KC_VOLU,     KC_MUTE,    KC_SNAP,  KC_SIRI,  RGB_MOD,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,      KC_BSPC,    KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC,                 KC_DEL,   KC_END,   KC_PGDN,
        KC_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,   KC_NUHS,     KC_ENT,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                KC_RSFT,              KC_UP,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD, KC_ROPTN,  MO(MAC_FN),  KC_RCTL,    KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_tkl_iso(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,     RGB_TOG,    _______,  _______,  RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    _______,  _______,  _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    _______,  _______,  _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,  _______,  _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,              _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,    _______,  _______,  _______),

    [WIN_BASE] = LAYOUT_tkl_iso(
        KC_CAPS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,       KC_F12,      KC_MPLY,  KC_PSCR,  KC_F14,   RGB_TOG,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,      KC_EQL,      KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,      KC_RBRC,               KC_DEL,   KC_END,   KC_PGDN,
        KC_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,      KC_NUHS,     KC_ENT,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                   KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LCMD,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(WIN_MOD),  MO(WIN_FN),  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_tkl_iso(
        _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,         KC_VOLU,  RGB_TOG,    _______,  _______,  RGB_MOD,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,         _______,  _______,    _______,  _______,  _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,         _______,              _______,  _______,  _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,         _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,                   _______,              _______,
        _______,  _______,  _______,                                EC_TOGG,                                _______,  TG(WIN_FN_SYS),  _______,  _______,    _______,  _______,  _______),

    [WIN_FN_SYS] = LAYOUT_tkl_iso(
        _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  _______, _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,  _______,                                _______,                      _______,  _______,  _______,  _______,    _______,  _______,  _______),

    [WIN_MOD] = LAYOUT_tkl_iso(
        _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,          RGB_TOG,    _______,  _______,  RGB_MOD,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,          _______,    _______,  _______,  _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,          _______,
        _______,  _______,  _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,                    _______,              _______,
        _______,  _______,  _______,                                EC_TOGG,                                _______,  _______,  TG(WIN_MOD_SYS),  _______,    _______,  _______,  _______),

    [WIN_MOD_SYS] = LAYOUT_tkl_iso(
        _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,  _______,                                _______,                      _______,  _______,  _______,  _______,    _______,  _______,  _______),

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN]   = {ENCODER_CCW_CW(KC_WH_U, KC_WH_D)},
    [WIN_FN_SYS]   = {ENCODER_CCW_CW(KC_WH_U, KC_WH_D)},
    [WIN_MOD]   = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
    [WIN_MOD_SYS]   = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
};
#endif // ENCODER_MAP_ENABLE

enum {
    LAYER_TYPE_DEFAULT,
    LAYER_TYPE_MOMENTARY,
    LAYER_TYPE_TOGGLE,
};

struct layer_info_t {
    uint8_t type;
    uint8_t index;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

const struct layer_info_t PROGMEM layers_info[] = {
    [MAC_BASE] = {LAYER_TYPE_DEFAULT, 0, RGB_BLACK},
    [MAC_FN] = {LAYER_TYPE_MOMENTARY, 83, RGB_CYAN},
    [WIN_BASE] = {LAYER_TYPE_DEFAULT, 0, RGB_BLACK},
    [WIN_FN] = {LAYER_TYPE_MOMENTARY, 83, RGB_CYAN},
    [WIN_FN_SYS] = {LAYER_TYPE_TOGGLE, 83, RGB_RED},
    [WIN_MOD] = {LAYER_TYPE_MOMENTARY, 82, RGB_CYAN},
    [WIN_MOD_SYS] = {LAYER_TYPE_TOGGLE, 82, RGB_RED},
};

// clang-format on
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    return true;
}

static bool vol_lvl_indicator_active = false;
static uint32_t vol_lvl_indicator_timer_buffer = 0;
static uint32_t vol_lvl_indicator_level = 0;
static bool vol_lvl_indicator_muted = false;

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t highest_layer = get_highest_layer(layer_state);
    if (highest_layer > 0) {
        for (uint8_t layer = 0; layer < LAYER_COUNT; layer++) {
            struct layer_info_t layer_info = layers_info[layer];
            if (layer_info.type > LAYER_TYPE_DEFAULT && IS_LAYER_ON(layer)) {
                rgb_matrix_set_color(layer_info.index, layer_info.red, layer_info.green, layer_info.blue);
            }
        }


        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];
                keypos_t pos = {col,row};

                if (index >= led_min && index < led_max && index != NO_LED &&
                    keymap_key_to_keycode(highest_layer, pos) > KC_TRNS) {
                    rgb_matrix_set_color(index, RGB_GREEN);
                }
            }
        }
    }

    if (vol_lvl_indicator_active) {
        uint8_t vol_lvl_led_list[10] = VOL_LEVEL_LED_LIST;

        uint8_t count = vol_lvl_indicator_level;
        if (vol_lvl_indicator_level == 0) {
            count = 100;
        }

        for (uint8_t i = 0; i < count / 10; i++) {
            uint8_t index = vol_lvl_led_list[i];
            if (index >= led_min && index < led_max) {
                if (vol_lvl_indicator_level == 0 || vol_lvl_indicator_muted) {
                    rgb_matrix_set_color(index, RGB_RED);
                } else {
                    rgb_matrix_set_color(index, RGB_WHITE);
                }
            }
        }

        if (vol_lvl_indicator_level > 0) {
        	uint8_t index = vol_lvl_led_list[vol_lvl_indicator_level / 10];
        	if (index >= led_min && index < led_max) {
                uint8_t sub_level = (int)(0xFF * ((float)(vol_lvl_indicator_level % 10) / 10.0));
                if (vol_lvl_indicator_muted) {
                	rgb_matrix_set_color(index, sub_level, 0x00, 0x00);
                } else {
                	rgb_matrix_set_color(index, sub_level, sub_level, sub_level);
                }
        	}
        }

        if (sync_timer_elapsed32(vol_lvl_indicator_timer_buffer) > 3000) {
            vol_lvl_indicator_active = false;
            vol_lvl_indicator_timer_buffer = 0;
            lpm_timer_reset();
        }
    }

    return false;
}

const uint8_t CUSTOM_PROTOCOL = 'A';

enum {
    CMD_SET_VOLUME = 0x01,
} CUSTOM_COMMANDS;

bool raw_hid_receive_keychron(uint8_t *data, uint8_t length) {
    if (data[0] != CUSTOM_PROTOCOL)
        return false;

    bool success = false;
    switch (data[1]) {
        case CMD_SET_VOLUME:
            if (data[2] < 101) {
                vol_lvl_indicator_timer_buffer = timer_read32();
                vol_lvl_indicator_active = true;
                vol_lvl_indicator_level = data[2];
                vol_lvl_indicator_muted = data[3];
                success = true;
            }
            break;
    }

    uint8_t response[length];
    memset(response, 0, length);
    response[0] = success;
    raw_hid_send(response, length);
    return true;
}
