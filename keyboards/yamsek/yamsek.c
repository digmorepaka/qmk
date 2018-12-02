#include "yamsek.h"

#include "analog.h"

// from mousekey.c
#include "host.h"
#include "timer.h"
//#include "print.h"
//#include "debug.h"
#include "mousekey.h"

#include "i2cmaster.h"

/** Pololu A-Star 32U4 Micro
                   micro
                ┌───USB───┐
 Column 0  PB5 ─┤9      A0├─ PF7 (future: joystick?)
    "   1  PB4 ─┤8      A1├─ PF6 (future: joystick?)
    "   2  PE6 ─┤7      10├─ PB6 Row 0
    "   3  PD7 ─┤6      11├─ PB7 Row 1
    "   4  PC6 ─┤5      12├─ PD6 Row 2
    "   5  PD4 ─┤4        ├─ Reset
  I2C SCL  PD0 ─┤3        ├─ 3V3
  I2C SDA  PD1 ─┤2        ├─ 5V
  RGB LED  PD3 ─┤1  OOO   ├─ Gnd
   Row 3   PD2 ─┤0  ICSP  ├─ Vin
                └─────────┘

 Rows 0-2 are on the top-shell/half
 Row 3 is the thumb-cluster
*/



//static uint16_t last_timer = 0;
// milliseconds between mouse-events
#define MOUSE_DELAY 20

//static report_mouse_t mouse_report = {};
static int16_t vertCenter = 512;
static int16_t horzCenter = 512;
#define DEADZONE 10

void matrix_init_kb(void) {
    matrix_init_user();

    // calibrate joystick center once during startup
    vertCenter = analogRead(5);
    horzCenter = analogRead(4);
}


// TODO: create separate function that is called during tmk_core/keyboard.c:keybard_task instead of piggibacking on the matrix_scan task
void matrix_scan_kb(void) {
    matrix_scan_user();
#if 0 // TODO 2017-03-18 mouse code disabled for now, since the analog joystick isn't hooked up ATM
    if (timer_elapsed(last_timer) < MOUSE_DELAY)
        return;

    report_mouse_t mouse_report = {0};

    // analog joystick mouse_task - analog to mousekey->mousekey_task
    // AVR ADC gives us 10 bit, so analogRead range should be [0,1024]
    int16_t vert = analogRead(5);
    int16_t horz = analogRead(4);
    // teensy pin-mapping: 5 = ADC5 = PF5

#if 1
    int8_t dx = (horz - horzCenter) / 100; // range [-5,5]
    int8_t dy = (vert - vertCenter) / 100;
    dx *= abs(dx); dy *= abs(dy); // square for faster movement
#endif
#if 0
    int8_t dx = (pow(horz,2.2d) - pow(horzCenter,2.2d) ) / 100; // range [-5,5]
    int8_t dy = (pow(vert,2.2d) - pow(vertCenter,2.2d) ) / 100;
#endif
    mouse_report.x = dx;
    mouse_report.y = dy;

    /*
    if (horz > horzCenter + DEADZONE) {
        mouse_report.x = 1;
        sendReport = true;
    }
    else if (horz < horzCenter - DEADZONE) {
        mouse_report.x = -1;
        sendReport = true;
    }
    else
        mouse_report.x = 0;

    if (vert > vertCenter + DEADZONE) {
        mouse_report.y = 1;
        sendReport = true;
    }
    else if (vert < vertCenter - DEADZONE) {
        mouse_report.y = -1;
        sendReport = true;
    }
    else
        mouse_report.y = 0;
    */

//    mouse_report.y = 1;
//    if (sendReport)
//    if (timer_elapsed(last_timer) > MOUSE_DELAY) {
        host_mouse_send(&mouse_report);
        last_timer = timer_read();
//    }
#endif
}

void neopixel_i2c_setrgb(uint8_t pixel, uint8_t r, uint8_t g, uint8_t b)
{
    uint8_t status = 0x20;

    status = i2c_start(0x30);          if (status) goto out;
    // pixel address byte
    status = i2c_write(pixel *3 + 1);  if (status) goto out;
    // Note: native format of neopixels is jumbled! = Green, Red, Blue
    status = i2c_write(g);             if (status) goto out; // Green
    status = i2c_write(r);             if (status) goto out; // Red
    status = i2c_write(b);             if (status) goto out; // Blue
out:
    i2c_stop();
}
