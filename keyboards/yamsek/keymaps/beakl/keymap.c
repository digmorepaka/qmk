// https://deskthority.net/wiki/Keyboard_layouts#BEAKL_.282016.29

#include "yamsek.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /**
       RIGHT
       ╔═══════════╦═══════════╦═══════════╗
       ║     W     ║     D     ║     L     ╠═══════════╗
       ╠═══════════╬═══════════╬═══════════╣     N     ╠═══════════╦═══════════╗
       ║     G     ║     S     ║     T     ╠═══════════╣     V     ║     Z     ║  Top Row
       ╠═══════════╬═══════════╬═══════════╣     R     ╠═══════════╬═══════════╣
       ║     F     ║     C     ║     M     ╠═══════════╣     P     ║           ║  Mid Row
       ╚═══════════╩═══════════╩═══════════╣     B     ╠═══════════╬═══════════╣
                                           ╚═══════════╣     K     ║     Q     ║  Bot Row
                                                       ╚═══════════╩═══════════╝
                           ╔═════════╗
                 ╔═════════╣3        ║  ╔═════════╗
       ╔═════════╣2        ╠═════════╝  ║4        ║  Thumb Cluster key-order
       ║1        ╠═════════╝  ╔═════════╬═════════╣
       ╚═════════╝            ║6        ║5        ║
                              ╚═════════╩═════════╝

       +-----------+-----------+-----------+-----------+-----------+-----------+
       |     W     |     D     |     L     |     N     |     V     |     Z     |  Top Row
       +-----------+-----------+-----------+-----------+-----------+-----------+
       |     G     |     S     |     T     |     R     |     P     |           |  Mid Row
       +-----------+-----------+-----------+-----------+-----------+-----------+
       |     F     |     C     |     M     |     B     |     K     |     Q     |  Bot Row
       +-----------+-----------+-----------+-----------+-----------+-----------+

       +-----------+-----------+-----------+-----------+-----------+-----------+
       +  Layer 1  |  Backsp   |   Delete  |  Space    |   Enter   |   Tab     | Thumb Cluster
       +-----------+-----------+-----------+-----------+-----------+-----------+

                   |           |           |           |           |
                   |           |           |           |           |

       LEFT
                    ╔═════════╗
       ╔═════════╗  ║4        ╠═════════╗
       ║3        ║  ╚═════════╣5        ╠═════════╗
       ╠═════════╬═════════╗  ╚═════════╣6        ║  Thumb Cluster key-order
       ║2        ║1        ║            ╚═════════╝
       ╚═════════╩═════════╝

       +-----------+-----------+-----------+-----------+-----------+-----------+
       |     -     |     X     |     Y     |     O     |     U     |     '     |  Top Row
       +-----------+-----------+-----------+-----------+-----------+-----------+
       |           |     H     |     I     |     E     |     A     |     .     |  Mid Row
       +-----------+-----------+-----------+-----------+-----------+-----------+
       |     J     |     (     |     "     |     )     |     ,     |     :     |  Bot Row
       +-----------+-----------+-----------+-----------+-----------+-----------+

       +-----------+-----------+-----------+-----------+-----------+-----------+
       +  Layer 1  |  Backsp   |   Delete  |  L Shift  |   L Ctrl  |   L Alt   | Thumb Cluster
       +-----------+-----------+-----------+-----------+-----------+-----------+

                   |           |           |           |           |
                   |           |           |           |           |*/
#if 0
    [0] = KEYMAP( // TEST
        //right
        KC_1       ,KC_2       ,KC_3       ,KC_4       ,KC_5       ,KC_6,
        KC_A       ,KC_B       ,KC_C       ,KC_D       ,KC_E       ,KC_F,
        KC_G       ,KC_H       ,KC_I       ,KC_J       ,KC_K       ,KC_L,
        KC_M       ,KC_N       ,KC_O       ,KC_P       ,KC_Q       ,KC_R,
        //left
        KC_7       ,KC_8       ,KC_9       ,KC_0       ,KC_1       ,KC_2,
        KC_A       ,KC_B       ,KC_C       ,KC_D       ,KC_E       ,KC_F,
        KC_G       ,KC_H       ,KC_I       ,KC_J       ,KC_K       ,KC_L,
        KC_M       ,KC_N       ,KC_O       ,KC_P       ,KC_Q       ,KC_R
        ),//       |           |           |           |           |
#else
    [BASE] = KEYMAP( // Base
        //right
        KC_W       ,KC_D       ,KC_L       ,KC_N       ,KC_V       ,KC_Z,
        KC_G       ,KC_S       ,KC_T       ,KC_R       ,KC_P    ,KC_NO,
        KC_F       ,KC_C       ,KC_M    ,KC_B       ,KC_K       ,KC_Q,
        KC_V       ,KC_BSPC    ,KC_DELT    ,KC_SPC     ,KC_ENT     ,KC_TAB,
        //left
        KC_NO      ,KC_X       ,KC_Y       ,KC_O       ,KC_U       ,KC_QUOT,
        KC_NO      ,KC_H       ,KC_I       ,KC_E       ,KC_A       ,KC_DOT,
        KC_J       ,KC_LPRN    ,KC_DQT     ,KC_RPRN    ,KC_COMM    ,KC_SCLN,
        TG(1)      ,KC_BSPC    ,KC_DELT    ,KC_LSHIFT  ,KC_LCTRL     ,KC_LALT
        ),//       |           |           |           |           |
#endif
    [1] = KEYMAP(//|           |           |           |           |
        // gaming, with shifted WASD block
        //right
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_LEFT    ,KC_UP      ,KC_RIGHT   ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_DOWN    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_Q       ,KC_E       ,KC_SPC     ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        //left
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_A       ,KC_W       ,KC_D       ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_Q       ,KC_S       ,KC_E       ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS
        ),//       |           |           |           |           |
    [2] = KEYMAP(//| numpad (blender)      |           |           |
        //right
        KC_TRNS    ,KC_TRNS    ,KC_MPRV    ,KC_MPLY    ,KC_MNXT    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        //left
        KC_TRNS    ,KC_TRNS    ,KC_KP_7    ,KC_KP_8    ,KC_KP_9    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_KP_4    ,KC_KP_5    ,KC_KP_6    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_KP_1    ,KC_KP_2    ,KC_KP_3    ,KC_KP_COMMA,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS
        ),//       |           |           |           |           |
    [3] = KEYMAP(//| Mouse     |           |           |           |
        //right
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        //left
        KC_TRNS    ,KC_WH_U    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_WH_D    ,KC_MS_L    ,KC_MS_UP   ,KC_MS_R    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_MS_DOWN ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_LGUI    ,KC_TRNS    ,KC_MS_BTN1 ,KC_MS_BTN2 ,KC_BTN3
        ),
    [4] = KEYMAP( /* RGBLIGHT */
        //right
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        //left
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,RGB_TOG    ,RGB_MOD    ,RGB_HUI    ,RGB_HUD    ,KC_TRNS,
        KC_TRNS    ,RGB_SAI    ,RGB_SAD    ,RGB_VAI    ,RGB_VAD    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS
        ),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};


void matrix_init_user(void) {

};

void matrix_scan_user(void) {

};

/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
*/
