#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef OLED_DRIVER_ENABLE
static uint32_t oled_timer = 0;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
  _QWERTY,
  _LOWER,
  _RAISE
};

// Custom keycodes for layer keys
// Dual function escape with left command
#define KC_LGESC LGUI_T(KC_ESC)
// #define _______ KC_NO

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Default Layer
 *
 * .-------------------------------------------.                  .-------------------------------------------.
 * |GUI/ESC |   Q  |  W   |  E   |  R   |  T   |                  |  Y   |  U   |  I   |  O   |  P   |  BPSC  |
 * |--------+------+------+------+------+------|                  |------+------+------+------+------+--------|
 * |CTR/TAB |   A  |  S   |  D   |  E   |  F   |                  |  H   |  J   |  K   |  L   |  L   | MET/'  |
 * |--------+------+------+------+------+------+                  |------+------+------+------+------+--------|
 * |SHIFT/( |   Z  |  X   |  C   |  V   |  B   |                  |  N   |  M   |  ,   |  .   |  /   |SHIFT/) |
 * '----------------------+------+------+------+                  |------+------+------+----------------------'
 *                        |      |      |      |                  |      |      |      |
 *                        | CMD  |SH/ENT| LOW  |                  |  UP  |MET/  | LEAD |
 *                        '--------------------'                  '--------------------'
 */

  [_QWERTY] = LAYOUT(
  //,-----------------------------------------.                ,---------------------------------------------.
    KC_LGESC,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                   KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,  KC_BSPC,
  //|------+------+------+------+------+------|                |------+------+-------+------+-------+--------|
    CTL_T(KC_TAB),  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,                   KC_H,  KC_J,  KC_K,  KC_L, KC_SCLN,MT(MOD_LALT, KC_QUOT),
  //|------+------+------+------+------+------|                |------+------+-------+------+-------+--------|
    KC_LSPO,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,                   KC_N,  KC_M,KC_COMM,KC_DOT,KC_SLSH,KC_RSPC,
  //|------+------+------+------+------+------+------|  |------+------+------+-------+------+-------+--------|
    KC_LGUI, MT(MOD_LSFT, KC_ENT), LOWER,                         RAISE, MT(MOD_LALT, KC_SPC), KC_LEAD
                              //`--------------------'  `--------------------'
  ),

/*
 * Lower Layer: Numpad, Media
 *
 * .-------------------------------------------.                  .-------------------------------------------.
 * |        |  F7  | F8   | F9   | F10  |      |                  | / ?  | 7 &  | 8 *  | 9 (  | - _  |        |
 * |--------+------+------+------+------+------|                  |------+------+------+------+------+--------|
 * |        |  F4  | F5   | F6   | F11  |      |                  | *    | 4 $  | 5 %  | 6 ^  | , <  | +      |
 * |--------+------+------+------+------+------+                  |------+------+------+------+------+--------|
 * |        |  F1  | F2   | F3   | F12  |      |                  | 0 )  | 1 !  | 2 @  | 3 #  | = +  |        |
 * '----------------------+------+------+------+                  |------+------+------+----------------------'
 *                        |      |      |      |                  |      |      |      |
 *                        |      |      |      |                  |      |      |      |
 *                        '--------------------'                  '--------------------'
 */
    [_LOWER] = LAYOUT(
      _______, KC_F7,   KC_F8,   KC_F9,   KC_F10, _______,     KC_SLSH, KC_7,    KC_8,    KC_9, KC_MINS, _______,
      _______, KC_F4,   KC_F5,   KC_F6,   KC_F11, _______,     KC_ASTR, KC_4,    KC_5,    KC_6, KC_COMM, KC_PLUS,
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F12, _______,     KC_0,    KC_1,    KC_2,    KC_3, KC_EQL,  _______,
                               _______, _______, _______,     _______, _______, _______
    ),
/*
 * Raise Layer: Symbols
 *
 * .-------------------------------------------.                   .-------------------------------------------.
 * |        |  !   |  @   |  {   |  }   |  |   |                   |      |  _   |  €   |      |      |  \     |
 * |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
 * |        |  #   |  $   |  (   |  )   |  `   |                   |   +  |  -   |  /   |  *   |  %   |  ' "   |
 * |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
 * |        |  %   |  ^   |  [   |  ]   |  ~   |                   |   &  |  =   |  ,   |  .   |  / ? | - _    |
 * '----------------------+------+------+------|                   |------+------+------+----------------------'
 *                        |      |      |      |                   |      |      |      |
 *                        |      |      |      |                   |      |      |      |
 *                        '--------------------'                   '--------------------'
 */
  [_RAISE] = LAYOUT(
   _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,        _______, KC_UNDS, ALGR(KC_5),_______,_______,KC_BSLS,
   _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,         KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_PERC, KC_QUOT,
   _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,        KC_AMPR, KC_EQL,  KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
                          _______, _______, _______,        _______, _______, _______
  )
};

int RGB_current_mode;

void matrix_init_user(void) {
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void render_logo(void) {
    static const char PROGMEM corne_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(corne_logo, false);
    oled_write_P(PSTR("corne"), false);
}

void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};

    if(layer_state_is(_LOWER)) {
        oled_write_P(lower_layer, false);
    } else if(layer_state_is(_RAISE)) {
        oled_write_P(raise_layer, false);
    } else {
      oled_write_P(default_layer, false);
    }
}

void render_status_main(void) {
    render_logo();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

void render_status_secondary(void) {
    render_logo();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 30000) {
        oled_off();
        return;
    }
#ifndef SPLIT_KEYBOARD
    else { oled_on(); }
#endif

    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}

#endif
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
#endif
    // set_timelog();
  }
  static uint16_t my_colon_timer;

  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
  }
  return true;
}
