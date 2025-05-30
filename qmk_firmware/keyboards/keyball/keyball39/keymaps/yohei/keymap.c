/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    LCTL_T(KC_A), KC_S  , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_MINS  ,
    LSFT_T(KC_Z), KC_X  , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,
    KC_LCTL  , KC_LGUI  , KC_LALT  ,LSFT_T(KC_LNG2),LT(1,KC_SPC),LT(3,KC_LNG1),KC_BSPC,LT(2,KC_ENT),LSFT_T(KC_LNG2),KC_RALT,KC_RGUI, KC_RSFT
  ),

  [1] = LAYOUT_universal(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_RBRC  ,                            KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,
    KC_F5    , KC_EXLM  , S(KC_6)  ,S(KC_INT3), S(KC_8)  ,                           S(KC_INT1), KC_BTN1  , KC_PGUP  , KC_BTN2  , KC_SCLN  ,
    S(KC_EQL),S(KC_LBRC),S(KC_7)   , S(KC_2)  ,S(KC_RBRC),                            KC_LBRC  , KC_DLR   , KC_PGDN  , KC_BTN3  , KC_F11   ,
    KC_INT1  , KC_EQL   , S(KC_3)  , _______  , _______  , _______  ,      TO(2)    , TO(0)    , _______  , KC_RALT  , KC_RGUI  , KC_F12
  ),

  [2] = LAYOUT_universal(
    KC_TAB   , KC_7     , KC_8     , KC_9     , KC_MINS  ,                            KC_NUHS  , _______  , KC_BTN3  , _______  , KC_BSPC  ,
   S(KC_QUOT), KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                            S(KC_9)  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_QUOT  ,
    KC_SLSH  , KC_1     , KC_2     , KC_3     ,S(KC_MINS),                           S(KC_NUHS), KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  ,
    KC_ESC   , KC_0     , KC_DOT   , KC_DEL   , KC_ENT   , KC_BSPC  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  ,                            _______  , _______  , SSNP_HOR , SSNP_VRT , SSNP_FRE ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , SCRL_DVI ,                            _______  , _______  , _______  , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , SCRL_DVD ,                            CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE ,
    QK_BOOT  , KBC_RST  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , KBC_RST  , QK_BOOT
  ),

  [4] = LAYOUT_universal(
    _______ , _______ , _______ , _______ , _______ ,                           _______ , _______ , _______ , _______ , _______ ,
    _______ , _______ , _______ , _______ , _______ ,                           _______ , _______ , _______ , _______ , _______ ,
    _______ , _______ , _______ , _______ , _______ ,                           _______ , _______ , _______ , _______ , _______ ,
    _______ , _______ , _______ , _______ , _______ , _______ ,      _______ , _______ , _______ , _______ , _______ , _______
  ),

  [5] = LAYOUT_universal(
    _______ , _______ , _______ , _______ , _______ ,                           _______ , _______ , _______ , _______ , _______ ,
    _______ , _______ , _______ , _______ , _______ ,                           _______ , _______ , _______ , _______ , _______ ,
    _______ , _______ , _______ , _______ , _______ ,                           _______ , _______ , _______ , _______ , _______ ,
    _______ , _______ , _______ , _______ , _______ , _______ ,      _______ , _______ , _______ , _______ , _______ , _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

// コンボ用の定義を追加
enum combo_events {
  // COMBO_E_W_ESC,         // E + W で ESC
  // COMBO_I_O_MINUS,       // i + o で -
  // COMBO_K_L_ENTER,       // k + l で Enter
  COMBO_BTN1_BTN2_SCROLL, // マウスボタン1と2でスクロール
  COMBO_LEFT_DOWN_CTRL_LEFT, // ←+↓ で Ctrl+←
  COMBO_RIGHT_DOWN_CTRL_RIGHT, // →+↓ で Ctrl+→
};

// const uint16_t PROGMEM e_w_esc_combo[] = {KC_E, KC_W, COMBO_END};
// const uint16_t PROGMEM i_o_minus_combo[] = {KC_I, KC_O, COMBO_END}; 
// const uint16_t PROGMEM k_l_enter_combo[] = {KC_K, KC_L, COMBO_END}; 
const uint16_t PROGMEM btn1_btn2_scroll_combo[] = {KC_BTN1, KC_BTN2, COMBO_END};
const uint16_t PROGMEM left_down_ctrl_left_combo[] = {KC_LEFT, KC_DOWN, COMBO_END};
const uint16_t PROGMEM right_down_ctrl_right_combo[] = {KC_RIGHT, KC_DOWN, COMBO_END};

combo_t key_combos[] = {
  // [COMBO_E_W_ESC] = COMBO(e_w_esc_combo, KC_ESC),
  // [COMBO_I_O_MINUS] = COMBO(i_o_minus_combo, KC_MINS),
  // [COMBO_K_L_ENTER] = COMBO(k_l_enter_combo, KC_ENT), 
  [COMBO_BTN1_BTN2_SCROLL] = COMBO_ACTION(btn1_btn2_scroll_combo),
  [COMBO_LEFT_DOWN_CTRL_LEFT] = COMBO(left_down_ctrl_left_combo, LCTL(KC_LEFT)),
  [COMBO_RIGHT_DOWN_CTRL_RIGHT] = COMBO(right_down_ctrl_right_combo, LCTL(KC_RIGHT)),
};

// ホールド必須のコンボを指定
bool get_combo_must_hold(uint16_t combo_index, combo_t *combo) {
    switch (combo_index) {
        case COMBO_BTN1_BTN2_SCROLL:
            return true;  // マウスボタン1+2のコンボはホールドが必要
        default:
            return false; // 他のコンボはタップでOK
    }
}

// コンボアクションの処理 - マウスボタン1+2を押している間だけレイヤー3を有効にする
void process_combo_event(uint16_t combo_index, bool pressed) {
  switch (combo_index) {
    case COMBO_BTN1_BTN2_SCROLL:
      if (pressed) {
        // レイヤー3をオンにする
        layer_on(3);
      } else {
        // レイヤー3をオフにする
        layer_off(3);
      }
      break;
  }
}


// 特定のキーに対するTapping Termの値を設定
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_A):  // 'a' キー (タップでa、ホールドでCtrl)
            return 200;  // 200msのtapping term
        case LSFT_T(KC_Z):  // 'z' キー (タップでz、ホールドでShift)
            return 200;  // 200msのtapping term
        default:
            return TAPPING_TERM;  // その他のキーはデフォルト値
    }
}