// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
enum layers {
    BASE,
    FN1,
    FN2,
};

enum custom_keycodes {
  SOCD_UP,
  SOCD_LEFT,
  SOCD_DOWN,
  SOCD_RIGHT
};

bool up_down = false;
bool left_down = false;
bool down_down = false;
bool right_down = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT_mypad(
        KC_INS,  KC_HOME, KC_PGUP,    KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_DEL,  KC_END,  KC_PGDN,    KC_P7,   KC_P8,   KC_P9,   
                                      KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
                 SOCD_UP,               KC_P1,   KC_P2,   KC_P3,   
        SOCD_LEFT, SOCD_DOWN, SOCD_RIGHT,    KC_P0,            KC_PDOT,  KC_PENT
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case SOCD_UP:
        if (record->event.pressed) {
            if (down_down) {
                unregister_code(KC_DOWN);
            }
            register_code(KC_UP);
            up_down = true;
        } else {
            unregister_code(KC_UP);
            up_down = false;

            if (down_down) {
                register_code(KC_DOWN);
            }

        }
        return false;
        break;
    case SOCD_LEFT:
        if (record->event.pressed) {
            if (right_down) {
                unregister_code(KC_RIGHT);
            }
            register_code(KC_LEFT);
            left_down = true;
        } else {
            unregister_code(KC_LEFT);
            left_down = false;

            if (right_down) {
                register_code(KC_RIGHT);
            }

        }
        return false;
        break;
    case SOCD_DOWN:
        if (record->event.pressed) {
            if (up_down) {
                unregister_code(KC_UP);
            }
            register_code(KC_DOWN);
            down_down = true;
        } else {
            unregister_code(KC_DOWN);
            down_down = false;

            if (up_down) {
                register_code(KC_UP);
            }

        }
        return false;
        break;
    case SOCD_RIGHT:
        if (record->event.pressed) {
            if (left_down) {
                unregister_code(KC_LEFT);
            }
            register_code(KC_RIGHT);
            right_down = true;
        } else {
            unregister_code(KC_RIGHT);
            right_down = false;

            if (left_down) {
                register_code(KC_LEFT);
            }
        }
        return false;
        break;
    }
    return true;
}