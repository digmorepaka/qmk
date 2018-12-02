#include "yamsek.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /**
       RIGHT
       ╔═══════════╦═══════════╦═══════════╗
       ║     Y     ║     U     ║     I     ╠═══════════╗
       ╠═══════════╬═══════════╬═══════════╣     O     ╠═══════════╦═══════════╗
       ║     H     ║     J     ║     K     ╠═══════════╣     P     ║     [     ║  Top Row
       ╠═══════════╬═══════════╬═══════════╣     L     ╠═══════════╬═══════════╣
       ║     N     ║     M     ║     ,     ╠═══════════╣     ;     ║     '     ║  Mid Row
       ╚═══════════╩═══════════╩═══════════╣     .     ╠═══════════╬═══════════╣
                                           ╚═══════════╣     /     ║           ║  Bot Row
                                                       ╚═══════════╩═══════════╝
                           ╔═════════╗
                 ╔═════════╣3        ║  ╔═════════╗
       ╔═════════╣2        ╠═════════╝  ║4        ║  Thumb Cluster key-order
       ║1        ╠═════════╝  ╔═════════╬═════════╣
       ╚═════════╝            ║6        ║5        ║
                              ╚═════════╩═════════╝

       +-----------+-----------+-----------+-----------+-----------+-----------+
       |     Y     |     U     |     I     |     O     |     P     |     [     |  Top Row
       +-----------+-----------+-----------+-----------+-----------+-----------+
       |     H     |     J     |     K     |     L     |     ;     |     '     |  Mid Row
       +-----------+-----------+-----------+-----------+-----------+-----------+
       |     N     |     M     |     ,     |     .     |     /     |           |  Bot Row
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
       |  Layer 4  |     Q     |     W     |     E     |     R     |     T     |  Top Row
       +-----------+-----------+-----------+-----------+-----------+-----------+
       |  Layer 3  |     A     |     S     |     D     |     F     |     G     |  Mid Row
       +-----------+-----------+-----------+-----------+-----------+-----------+
       |  Layer 2  |     Z     |     S     |     C     |     V     |     B     |  Bot Row
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
        KC_Y       ,KC_U       ,KC_I       ,KC_O       ,KC_P       ,KC_LBRC,
        KC_H       ,KC_J       ,KC_K       ,KC_L       ,KC_SCLN    ,KC_QUOT,
        KC_N       ,KC_M       ,KC_COMM    ,KC_DOT     ,KC_SLSH    ,KC_NO,
        KC_BSPC    ,KC_DELT    ,KC_SPC     ,KC_ENT     ,KC_TAB     ,MO(5),
        //left
        KC_ESC     ,KC_Q       ,KC_W       ,KC_E       ,KC_R       ,KC_T,
        TG(3)      ,KC_A       ,KC_S       ,KC_D       ,KC_F       ,KC_G,
        MO(2)      ,KC_Z       ,KC_X       ,KC_C       ,KC_V       ,KC_B,
        TG(1)      ,KC_BSPC    ,KC_DELT    ,KC_LSHIFT  ,KC_LCTRL   ,KC_LALT
        ),//       |           |           |           |           |
#endif
    [1] = KEYMAP(//|           |           |           |           |
        // gaming, with shifted WASD block
        //right
        KC_MPRV    ,KC_MPLY    ,KC_MNXT    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_LEFT    ,KC_UP      ,KC_RIGHT   ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_DOWN    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_Q       ,KC_E       ,KC_SPC     ,KC_TAB     ,KC_TRNS    ,KC_TRNS,
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
    [5] = KEYMAP(//| Function and numbers  |           |           |
        //right
        KC_F6      ,KC_F7      ,KC_F8      ,KC_F9      ,KC_F10     ,KC_TRNS,
        KC_6       ,KC_7       ,KC_8       ,KC_9       ,KC_0       ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        //left
        KC_TRNS    ,KC_F1      ,KC_F2      ,KC_F3      ,KC_F4      ,KC_F5,
        KC_TRNS    ,KC_1       ,KC_2       ,KC_3       ,KC_4       ,KC_5,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
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
    neopixel_i2c_setrgb(1, 0, 20, 20);
    neopixel_i2c_setrgb(2, 20, 0, 20);
    neopixel_i2c_setrgb(3, 20, 0, 20);
    neopixel_i2c_setrgb(4, 0, 20, 20);
};

uint8_t lastLayer = 0;
uint8_t sat = 25;
void matrix_scan_user(void) {
    return;
    uint8_t layer = biton32(layer_state);
#if 0
    if (lastLayer == layer)
        if (sat > 0)
            sat -= 1;
    else
    {
        sat = 55;
        lastLayer = layer;
    }
#endif
    switch (layer) {
    case 0:
        neopixel_i2c_setrgb(1, 0, 0, 0);
        break;
    case 1:
        neopixel_i2c_setrgb(1, sat, 0, 0);
        break;
    case 2:
        neopixel_i2c_setrgb(1, 0, sat, 0);
        break;
    case 3:
        neopixel_i2c_setrgb(1, 0, 0, sat);
        break;
#if 0
    default:
//        rgblight_setrgb(sat, sat, sat);
        setrgb(0,255,0, (LED_TYPE *)&led[0]);
        rgblight_set();
#endif
    }
};

/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
*/
