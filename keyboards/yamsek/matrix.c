/*
adopted from keyboards/ergodox/ez/matrix.c for its MCP23018 code
done some cleaned-up and additional documentation

Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>

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

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "wait.h"
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "yamsek.h"
#include "i2cmaster.h"
#ifdef DEBUG_MATRIX_SCAN_RATE
#include  "timer.h"
#endif

/*
 * This constant define not debouncing time in msecs, but amount of matrix
 * scan loops which should be made to get stable debounced results.
 *
 * On Ergodox matrix scan rate is relatively low, because of slow I2C.
 * Now it's only 317 scans/second, or about 3.15 msec/scan.
 * According to Cherry specs, debouncing time is 5 msec.
 *
 * And so, there is no sense to have DEBOUNCE higher than 2.
 */
#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif
static uint8_t debouncing = DEBOUNCE;

/* data-type that will hold the bits of one whole column
   so it has to be sized depending on the number of configured rows
 */
#if (MATRIX_ROWS <= 8)
typedef uint8_t matrix_col_t;
#elif (MATRIX_ROWS <= 16)
typedef uint16_t matrix_col_t;
#endif

/* matrix state(1:on, 0:off) */
static matrix_col_t matrix[MATRIX_COLS];
static matrix_col_t matrix_debouncing[MATRIX_COLS];

static matrix_col_t read_rows(void);
static void init_rows(void);
static void unselect_cols(void);
static void select_col(uint8_t col);

#ifdef DEBUG_MATRIX_SCAN_RATE
uint32_t matrix_timer;
uint32_t matrix_scan_count;
#endif

/***
    "library" methods for extensability, inherited from tmk_core/common/matrix.h
***/
__attribute__ ((weak))
void matrix_init_user(void) {}

__attribute__ ((weak))
void matrix_scan_user(void) {}

/*
__attribute__ ((weak))
void matrix_init_kb(void) {
  matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
  matrix_scan_user();
}
*/

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}


/***
    MCP23017 setup code
***/
// I2C aliases and register addresses
#define I2C_ADDR        0b0100000
#define I2C_ADDR_WRITE  ( (I2C_ADDR<<1) | I2C_WRITE )
#define I2C_ADDR_READ   ( (I2C_ADDR<<1) | I2C_READ  )
#define IODIRA          0x00            // i/o direction register
#define IODIRB          0x01
#define GPPUA           0x0C            // GPIO pull-up resistor register
#define GPPUB           0x0D
#define GPIOA           0x12            // general purpose i/o port register (write modifies OLAT)
#define GPIOB           0x13
#define OLATA           0x14            // output latch register
#define OLATB           0x15

/** MCP23017
                ┌─────┐
    Row 0   B0 ─┤1    ├─ A7
     "  1   B1 ─┤     ├─ A6
     "  2   B2 ─┤     ├─ A5 Column 5
     "  3   B3 ─┤     ├─ A4    "   4
            B4 ─┤     ├─ A3    "   3
            B5 ─┤     ├─ A2    "   2
            B6 ─┤     ├─ A1    "   1
            B7 ─┤     ├─ A0    "   0
           Vdd ─┤     ├─
       Gnd/Vss ─┤     ├─
               ─┤     ├─!Reset──Vdd
           SCL ─┤     ├─Addr2─┐
           SDA ─┤     ├─Addr1─┤
               ─┤     ├─Addr0─┤
                └─────┘       └─Vss/Gnd

*/

static bool i2c_initialized = 0;
static uint8_t mcp23017_status = 0x20;
static uint8_t mcp23017_reset_loop;

uint8_t init_mcp23017(void) {
    mcp23017_status = 0x20;

    // I2C subsystem

    // uint8_t sreg_prev;
    // sreg_prev=SREG;
    // cli();
    if (i2c_initialized == 0) {
        i2c_init();
        i2c_initialized++;
        _delay_ms(1000);
    }

    /** NOTE: 2017-03-18 without external pullups on the i2c lines the initilization seems to hang
        (when no i2c devices are connectes):-/
     */

    // set pin direction
    // - output : 0
    // - input  : 1
    mcp23017_status = i2c_start(I2C_ADDR_WRITE);    if (mcp23017_status) goto out;
    mcp23017_status = i2c_write(IODIRA);            if (mcp23017_status) goto out;
    //// PortA
    mcp23017_status = i2c_write(0b00000000);        if (mcp23017_status) goto out;
    //// PortB
    mcp23017_status = i2c_write(0b11111111);        if (mcp23017_status) goto out;
    i2c_stop();

    // set pull-up
    // - no-pullup : 0
    // - enable pullup : 1
    mcp23017_status = i2c_start(I2C_ADDR_WRITE);    if (mcp23017_status) goto out;
    mcp23017_status = i2c_write(GPPUA);             if (mcp23017_status) goto out;
    //// PortA
    mcp23017_status = i2c_write(0b00000000);        if (mcp23017_status) goto out;
    //// PortB
    mcp23017_status = i2c_write(0b11111111);        if (mcp23017_status) goto out;

out:
    i2c_stop();

    // SREG=sreg_prev;

    return mcp23017_status;
}

void matrix_init(void)
{
    // initialize row and col

    mcp23017_status = init_mcp23017();


    unselect_cols();
    init_rows();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_COLS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

#ifdef DEBUG_MATRIX_SCAN_RATE
    matrix_timer = timer_read32();
    matrix_scan_count = 0;
#endif

    matrix_init_quantum();

}

void matrix_power_up(void) {
    mcp23017_status = init_mcp23017();

    unselect_cols();
    init_rows();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_COLS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

#ifdef DEBUG_MATRIX_SCAN_RATE
    matrix_timer = timer_read32();
    matrix_scan_count = 0;
#endif

}

uint8_t matrix_scan(void)
{
    if (mcp23017_status) { // if there was an error
        if (++mcp23017_reset_loop == 0) {
            // since mcp23017_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans
            // this will be approx bit more frequent than once per second
            print("trying to reset mcp23017\n");
            mcp23017_status = init_mcp23017();
            if (mcp23017_status) {
                print("left side not responding\n");
            } else {
                print("left side attached\n");
                //TODO: signal status change through leds (?)
            }
        }
    }

#ifdef DEBUG_MATRIX_SCAN_RATE
    matrix_scan_count++;

    uint32_t timer_now = timer_read32();
    if (TIMER_DIFF_32(timer_now, matrix_timer)>1000) {
        print("matrix scan frequency: ");
        pdec(matrix_scan_count);
        print("\n");

        matrix_timer = timer_now;
        matrix_scan_count = 0;
    }
#endif

    /* scan over columns, by setting current column pin low and reading bit-state of all (internally pulled-up) rows into matrix_debounce
     */
    for (uint8_t i = 0; i < MATRIX_COLS; i++) {
        select_col(i);
        wait_us(30);  // without this wait read unstable value.
        matrix_col_t rows = read_rows();
        if (matrix_debouncing[i] != rows) {
            matrix_debouncing[i] = rows;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
        unselect_cols();
    }

    if (debouncing) {
        if (--debouncing) {
            wait_us(1);
            // this should be wait_ms(1) but has been left as-is at EZ's request
        } else {
            for (uint8_t i = 0; i < MATRIX_COLS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }

    matrix_scan_quantum();

    return 1;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_col_t)1<<col));
}


/**
   matrix_get_row is used by tmk_core for further keycode processing.

   since the matrix is an array of columns, we have to reassemble the single rowValues
 */
inline
matrix_row_t matrix_get_row(uint8_t row)
{
    uint8_t rowValues = 0x00;
    for (uint8_t col = 0; col < MATRIX_COLS; col++){
        if ( matrix[col] & (1<<row))
            rowValues |= 1 << col;
    }
    return rowValues;
}

void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        pbin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

/* Column pin configuration
 *
 * Main-MCU
 * col: 0   1   2   3   4   5
 * pin: PB5 PB4 PE6 PD7 PC6 PD4
 *
 * MCP23017
 * col: 0   1   2   3   4   5
 * pin: A0  A1  A2  A3  A4  A5
 */
/* Row pin configuration
 *
 * Main-MCU
 * row: 3   4   5
 * pin: PB6 PB7 PD6
 *
 * MCP23017
 * row: 0   1   2   3
 * pin: B0  B1  B2  B3
 */
/* wiring:

rows

R0 ─────│─┬─────│─┬──── ...
        │ └o o┐ │ └o o┐           -o o- = switch
        ├───|<┘ ├───|<┘
        │       │                  -|<- = diode
R1 ─────│─┬─────│─┬──── ...
        │ └o o┐ │ └o o┐
        ├───|<┘ ├───|<┘
        │       │
.       .       .
.       .       .
        │       │
       C0       C1      ... columns
*/


static void  init_rows(void)
{
    // init on mcp23017
    // not needed, already done as part of init_mcp23017()

    // init on Main-MCU
    // Input with pull-up(DDR:0, PORT:1)
    DDRB  &= ~(1<<7 | 1<<6);
    PORTB |=  (1<<7 | 1<<6);
    DDRD  &= ~(1<<6 | 1<<2);
    PORTD |=  (1<<6 | 1<<2);

}

/**
   while one column is selected (output, set low -all other set high)
   read the whole PortB, to see which pins are pulled low
   (remember: internal pullup are ON, so all switches open ==  read all 1 on PortB)
 */
static matrix_col_t read_rows(void)
{
    matrix_col_t retVal = 0;

    // read row-part connected to Main-MCU
    retVal =
            (PINB&(1<<6) ? 0 : (1<<0)) | // Row 0
            (PINB&(1<<7) ? 0 : (1<<1)) | // Row 1
            (PIND&(1<<6) ? 0 : (1<<2)) | // Row 2
            (PIND&(1<<2) ? 0 : (1<<3)) ; // Row 3

    // read rows connected to MCP23017
    if (mcp23017_status) { // if there was an error
        // do nothing
    } else {
        uint8_t data = 0;
        mcp23017_status = i2c_start(I2C_ADDR_WRITE);    if (mcp23017_status) goto out;
        mcp23017_status = i2c_write(GPIOB);             if (mcp23017_status) goto out;
        mcp23017_status = i2c_start(I2C_ADDR_READ);     if (mcp23017_status) goto out;
        data = i2c_readNak();
        // internal pull-up, closed switch pulls low -> invert read byte
        data = ~data;
        retVal |= (data <<4);
    out:
        i2c_stop();
    }

    return retVal;
}

static void unselect_cols(void)
{
    // unselect on mcp23017
    if (mcp23017_status) { // if there was an error
        // do nothing
    } else {
        // set all rows hi-Z : 1
        mcp23017_status = i2c_start(I2C_ADDR_WRITE);    if (mcp23017_status) goto out;
        mcp23017_status = i2c_write(GPIOA);             if (mcp23017_status) goto out;
        mcp23017_status = i2c_write(0xFF);              if (mcp23017_status) goto out;
    out:
        i2c_stop();
    }

    // unselect columns connected to Main-MCU
    // Hi-Z(DDR:0, PORT:0) to unselect
    DDRB  &= ~(1<<5 | 1<<4);
    PORTB &= ~(1<<5 | 1<<4);
    DDRC  &= ~(1<<6);
    PORTC &= ~(1<<6);
    DDRD  &= ~(1<<7 | 1<<4);
    PORTD &= ~(1<<7 | 1<<4);
    DDRE  &= ~(1<<6);
    PORTE &= ~(1<<6);
}

static void select_col(uint8_t col)
{
    // select on mcp23017
    if (mcp23017_status) { // if there was an error
        // do nothing
    } else {
        // set active row low  : 0
        // set other rows hi-Z : 1
        mcp23017_status = i2c_start(I2C_ADDR_WRITE);        if (mcp23017_status) goto out;
        mcp23017_status = i2c_write(GPIOA);                 if (mcp23017_status) goto out;
        mcp23017_status = i2c_write( 0xFF & ~(1<<col)
                              );                                if (mcp23017_status) goto out;
    out:
        i2c_stop();
    }

    // select column connected to Main-MCU
    // Output low(DDR:1, PORT:0) to select
    switch (col) {
            case 0:
                DDRB  |= (1<<5);
                PORTB &= ~(1<<5);
                break;
            case 1:
                DDRB  |= (1<<4);
                PORTB &= ~(1<<4);
                break;
            case 2:
                DDRE  |= (1<<6);
                PORTE &= ~(1<<6);
                break;
            case 3:
                DDRD  |= (1<<7);
                PORTD &= ~(1<<7);
                break;
            case 4:
                DDRC  |= (1<<6);
                PORTC &= ~(1<<6);
                break;
            case 5:
                DDRD  |= (1<<4);
                PORTD &= ~(1<<4);
                break;
    }
}
