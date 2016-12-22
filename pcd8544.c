/*** 
 * LCD driver for controller pcd8544 / Nokia 5110, 3110 /
 *
 * Copyright (C) 2016 Marian Hrinko.
 * Written by Marian Hrinko (mato.hrinko@gmail.com)
 *
 */
#ifndef F_CPU
  #define F_CPU 16000000UL
#endif

#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "pcd8544.h"

/***
 * @description Charset
 *
 * @param void
 * @return void
 */
const uint8_t CHARACTERS[][5] PROGMEM = {
  { 0x00, 0x00, 0x00, 0x00, 0x00 }, // 20 space
  { 0x00, 0x00, 0x5f, 0x00, 0x00 }, // 21 !
  { 0x00, 0x07, 0x00, 0x07, 0x00 }, // 22 "
  { 0x14, 0x7f, 0x14, 0x7f, 0x14 }, // 23 #
  { 0x24, 0x2a, 0x7f, 0x2a, 0x12 }, // 24 $
  { 0x23, 0x13, 0x08, 0x64, 0x62 }, // 25 %
  { 0x36, 0x49, 0x55, 0x22, 0x50 }, // 26 &
  { 0x00, 0x05, 0x03, 0x00, 0x00 }, // 27 '
  { 0x00, 0x1c, 0x22, 0x41, 0x00 }, // 28 (
  { 0x00, 0x41, 0x22, 0x1c, 0x00 }, // 29 )
  { 0x14, 0x08, 0x3e, 0x08, 0x14 }, // 2a *
  { 0x08, 0x08, 0x3e, 0x08, 0x08 }, // 2b +
  { 0x00, 0x50, 0x30, 0x00, 0x00 }, // 2c ,
  { 0x08, 0x08, 0x08, 0x08, 0x08 }, // 2d -
  { 0x00, 0x60, 0x60, 0x00, 0x00 }, // 2e .
  { 0x20, 0x10, 0x08, 0x04, 0x02 }, // 2f /
  { 0x3e, 0x51, 0x49, 0x45, 0x3e }, // 30 0
  { 0x00, 0x42, 0x7f, 0x40, 0x00 }, // 31 1
  { 0x42, 0x61, 0x51, 0x49, 0x46 }, // 32 2
  { 0x21, 0x41, 0x45, 0x4b, 0x31 }, // 33 3
  { 0x18, 0x14, 0x12, 0x7f, 0x10 }, // 34 4
  { 0x27, 0x45, 0x45, 0x45, 0x39 }, // 35 5
  { 0x3c, 0x4a, 0x49, 0x49, 0x30 }, // 36 6
  { 0x01, 0x71, 0x09, 0x05, 0x03 }, // 37 7
  { 0x36, 0x49, 0x49, 0x49, 0x36 }, // 38 8
  { 0x06, 0x49, 0x49, 0x29, 0x1e }, // 39 9
  { 0x00, 0x36, 0x36, 0x00, 0x00 }, // 3a :
  { 0x00, 0x56, 0x36, 0x00, 0x00 }, // 3b ;
  { 0x08, 0x14, 0x22, 0x41, 0x00 }, // 3c <
  { 0x14, 0x14, 0x14, 0x14, 0x14 }, // 3d =
  { 0x00, 0x41, 0x22, 0x14, 0x08 }, // 3e >
  { 0x02, 0x01, 0x51, 0x09, 0x06 }, // 3f ?
  { 0x32, 0x49, 0x79, 0x41, 0x3e }, // 40 @
  { 0x7e, 0x11, 0x11, 0x11, 0x7e }, // 41 A
  { 0x7f, 0x49, 0x49, 0x49, 0x36 }, // 42 B
  { 0x3e, 0x41, 0x41, 0x41, 0x22 }, // 43 C
  { 0x7f, 0x41, 0x41, 0x22, 0x1c }, // 44 D
  { 0x7f, 0x49, 0x49, 0x49, 0x41 }, // 45 E
  { 0x7f, 0x09, 0x09, 0x09, 0x01 }, // 46 F
  { 0x3e, 0x41, 0x49, 0x49, 0x7a }, // 47 G
  { 0x7f, 0x08, 0x08, 0x08, 0x7f }, // 48 H
  { 0x00, 0x41, 0x7f, 0x41, 0x00 }, // 49 I
  { 0x20, 0x40, 0x41, 0x3f, 0x01 }, // 4a J
  { 0x7f, 0x08, 0x14, 0x22, 0x41 }, // 4b K
  { 0x7f, 0x40, 0x40, 0x40, 0x40 }, // 4c L
  { 0x7f, 0x02, 0x0c, 0x02, 0x7f }, // 4d M
  { 0x7f, 0x04, 0x08, 0x10, 0x7f }, // 4e N
  { 0x3e, 0x41, 0x41, 0x41, 0x3e }, // 4f O
  { 0x7f, 0x09, 0x09, 0x09, 0x06 }, // 50 P
  { 0x3e, 0x41, 0x51, 0x21, 0x5e }, // 51 Q
  { 0x7f, 0x09, 0x19, 0x29, 0x46 }, // 52 R
  { 0x46, 0x49, 0x49, 0x49, 0x31 }, // 53 S
  { 0x01, 0x01, 0x7f, 0x01, 0x01 }, // 54 T
  { 0x3f, 0x40, 0x40, 0x40, 0x3f }, // 55 U
  { 0x1f, 0x20, 0x40, 0x20, 0x1f }, // 56 V
  { 0x3f, 0x40, 0x38, 0x40, 0x3f }, // 57 W
  { 0x63, 0x14, 0x08, 0x14, 0x63 }, // 58 X
  { 0x07, 0x08, 0x70, 0x08, 0x07 }, // 59 Y
  { 0x61, 0x51, 0x49, 0x45, 0x43 }, // 5a Z
  { 0x00, 0x7f, 0x41, 0x41, 0x00 }, // 5b [
  { 0x02, 0x04, 0x08, 0x10, 0x20 }, // 5c backslash
  { 0x00, 0x41, 0x41, 0x7f, 0x00 }, // 5d ]
  { 0x04, 0x02, 0x01, 0x02, 0x04 }, // 5e ^
  { 0x40, 0x40, 0x40, 0x40, 0x40 }, // 5f _
  { 0x00, 0x01, 0x02, 0x04, 0x00 }, // 60 `
  { 0x20, 0x54, 0x54, 0x54, 0x78 }, // 61 a
  { 0x7f, 0x48, 0x44, 0x44, 0x38 }, // 62 b
  { 0x38, 0x44, 0x44, 0x44, 0x20 }, // 63 c
  { 0x38, 0x44, 0x44, 0x48, 0x7f }, // 64 d
  { 0x38, 0x54, 0x54, 0x54, 0x18 }, // 65 e
  { 0x08, 0x7e, 0x09, 0x01, 0x02 }, // 66 f
  { 0x0c, 0x52, 0x52, 0x52, 0x3e }, // 67 g
  { 0x7f, 0x08, 0x04, 0x04, 0x78 }, // 68 h
  { 0x00, 0x44, 0x7d, 0x40, 0x00 }, // 69 i
  { 0x20, 0x40, 0x44, 0x3d, 0x00 }, // 6a j
  { 0x7f, 0x10, 0x28, 0x44, 0x00 }, // 6b k
  { 0x00, 0x41, 0x7f, 0x40, 0x00 }, // 6c l
  { 0x7c, 0x04, 0x18, 0x04, 0x78 }, // 6d m
  { 0x7c, 0x08, 0x04, 0x04, 0x78 }, // 6e n
  { 0x38, 0x44, 0x44, 0x44, 0x38 }, // 6f o
  { 0x7c, 0x14, 0x14, 0x14, 0x08 }, // 70 p
  { 0x08, 0x14, 0x14, 0x14, 0x7c }, // 71 q
  { 0x7c, 0x08, 0x04, 0x04, 0x08 }, // 72 r
  { 0x48, 0x54, 0x54, 0x54, 0x20 }, // 73 s
  { 0x04, 0x3f, 0x44, 0x40, 0x20 }, // 74 t
  { 0x3c, 0x40, 0x40, 0x20, 0x7c }, // 75 u
  { 0x1c, 0x20, 0x40, 0x20, 0x1c }, // 76 v
  { 0x3c, 0x40, 0x30, 0x40, 0x3c }, // 77 w
  { 0x44, 0x28, 0x10, 0x28, 0x44 }, // 78 x
  { 0x0c, 0x50, 0x50, 0x50, 0x3c }, // 79 y
  { 0x44, 0x64, 0x54, 0x4c, 0x44 }, // 7a z
  { 0x00, 0x08, 0x36, 0x41, 0x00 }, // 7b {
  { 0x00, 0x00, 0x7f, 0x00, 0x00 }, // 7c |
  { 0x00, 0x41, 0x36, 0x08, 0x00 }, // 7d }
  { 0x10, 0x08, 0x08, 0x10, 0x08 }, // 7e ~
  { 0x00, 0x00, 0x00, 0x00, 0x00 }  // 7f
};

/** @var array Chache memory Lcd 6 * 84 = 504 bytes */
static uint8_t cacheMemLcd[CACHE_SIZE_MEM];

/** @var array Chache memory char index */
int cacheMemIndex = 0;

/***
 * @description Initialise pcd8544 controller
 *
 * @param void
 * @return void
 */
void Pcd8544Init(void)
{
  // Actiavte pull-up register
  // logical high on pin RST
  PORT |= (1 << RST);
  // Output: RST, SCK, DIN, CE, DC 
  DDR  |= (1 << RST) | 
          (1 << SCK) | 
          (1 << DIN) | 
          (1 << CE)  | 
          (1 << DC);
  // 1 ms delay and reset impulse
  ResetImpulse();
  // SPE  - SPI Enale
  // MSTR - Master device
  // SPR0 - Prescaler fclk/16 = 1MHz
  SPCR |= (1 << SPE)  | 
          (1 << MSTR) |
          (1 << SPR0);
  // extended instruction set
  CmdOrDataSend(COMMAND, 0x21);
  // temperature set - temperature coefficient of IC
  CmdOrDataSend(COMMAND, 0x06);
  // bias 1:48 - optimum bias value
  CmdOrDataSend(COMMAND, 0x13);
  // for mux 1:48 optimum operation voltage is Ulcd = 6,06.Uth
  // Ulcd = 3,06 + (Ucp6 to Ucp0).0,06
  // 6 < Ulcd < 8,05
  // command for operation voltage = 0x1 Ucp6 Ucp5 Ucp4 Ucp3 Ucp2 Ucp1 Ucp0
  // Ulcd = 0x11000010 = 7,02 V
  CmdOrDataSend(COMMAND, 0xC2);
  // normal instruction set
  // horizontal adressing mode
  CmdOrDataSend(COMMAND, 0x20);
  // normal mode
  CmdOrDataSend(COMMAND, 0x0C);
}
/***
 * @description Comand/data send
 *
 * @param enumCmdOrData (see enum in pcd8544.h)
 * @param uint8_t 
 * @return void
 */
void CmdOrDataSend(enumCmdOrData cmdOrData, uint8_t data)
{
  // chip enable - active low
  PORT &= ~(1 << CE);
  // check if data
  if (cmdOrData == DATA) {
    // data (active high)
    PORT |= (1 << DC);
  // command
  } else {
    // command (active low)
    PORT &= ~(1 << DC);
  }
  // transmitting data
  SPDR = data;
  // wait till data transmit
  while (!(SPSR & (1 << SPIF)));
  // chip disable - idle high
  PORT |= (1 << CE);
}
/***
 * @description Reset impulse
 *
 * @param void
 * @return void
 */
void ResetImpulse(void)
{
  // delay 1ms
  _delay_ms(1);
  // Reset Low 
  PORT &= ~(1 << RST);
  // delay 1ms
  _delay_ms(1);
  // Reset High
  PORT |=  (1 << RST);
}
/***
 * Clear screen
 *
 * @param void
 * @return void
 */
void ClearScreen(void)
{
  // null cache memory lcd
  memset(cacheMemLcd, 0x00, CACHE_SIZE_MEM);
}
/***
 * @description Update screen
 *
 * @param void
 * @return void
 */
void UpdateScreen(void)
{
  int i;
  // set position x, y
  SetTextPosition(0, 0);
  // loop through cache memory lcd
  for (i=0; i<CACHE_SIZE_MEM; i++) {
    // write data to lcd memory
    CmdOrDataSend(DATA, cacheMemLcd[i]);
  }  
}
/***
 * @description Draw character
 *
 * @param char
 * @return void
 */
char DrawChar(char character)
{
  uint8_t i;
  // check if character is out of range
  if ((character < 0x20) &&
      (character > 0x7f)) { 
    // out of range
    return 0;
  }
  // 
  if ((cacheMemIndex % MAX_NUM_COLS) > (MAX_NUM_COLS - 5)) {
    // check if memory index not longer than 48 x 84
    if ((((cacheMemIndex / MAX_NUM_COLS) + 1) * MAX_NUM_COLS) > CACHE_SIZE_MEM) {
      // out of range
      return 0;
    }
    // resize index on new row
    cacheMemIndex = ((cacheMemIndex / MAX_NUM_COLS) + 1) * MAX_NUM_COLS;
  }
  // loop through 5 bytes
  for (i = 0; i < 5; i++) {
    // read from ROM memory 
    cacheMemLcd[cacheMemIndex++] = pgm_read_byte(&CHARACTERS[character - 32][i]);
  }
  //
  cacheMemIndex++;
  // return exit
  return 0;
}
/***
 * @description Draw string
 *
 * @param char *
 * @return void
 */
void DrawString(char *str)
{
  uint8_t i = 0;
  // loop through 5 bytes
  while (str[i] != '\0') {
    //read characters and increment index
    DrawChar(str[i++]);
  }
}
/***
 * @description Set x, y pixel position
 *
 * @param uint8_t x - position / 0 <= rows <= 5 
 * @param uint8_t y - position / 0 <= cols <= 14 
 * @return void
 */
char SetTextPosition(uint8_t x, uint8_t y)
{
  // check if x, y is in range
  if ((x >= MAX_NUM_ROWS) ||
      (y >= (MAX_NUM_COLS / 6))) {
    // out of range
    return 0;
  }
  // normal instruction set
  // horizontal adressing mode
  CmdOrDataSend(COMMAND, 0x20);
  // set x-position
  CmdOrDataSend(COMMAND, (0x40 | x));
  // set y-position
  CmdOrDataSend(COMMAND, (0x80 | (y * 6)));
  // calculate index memory
  cacheMemIndex = (y * 6) + (x * MAX_NUM_COLS);
  // success return
  return 1;
}
/***
 * @description Set x, y pixel position
 *
 * @param uint8_t x - position / 0 <= rows <= 47 
 * @param uint8_t y - position / 0 <= cols <= 83 
 * @return void
 */
char SetPixelPosition(uint8_t x, uint8_t y)
{ 
  // check if x, y is in range
  if ((x >= (MAX_NUM_ROWS * 8)) ||
      (y >=  MAX_NUM_COLS)) {
    // out of range
    return 0;
  }
  // normal instruction set
  // horizontal adressing mode
  CmdOrDataSend(COMMAND, 0x20);
  // set x-position
  CmdOrDataSend(COMMAND, (0x40 | (x / 8)));
  // set y-position
  CmdOrDataSend(COMMAND, (0x80 | y));
  // calculate index memory
  cacheMemIndex = y + ((x / 8) * MAX_NUM_COLS);
  // success return
  return 1;
}
/***
 * @description Draw x, y pixel position
 *
 * @param uint8_t x - position / 0 <= rows <= 47 
 * @param uint8_t y - position / 0 <= cols <= 83 
 * @return void
 */
char DrawPixel(uint8_t x, uint8_t y)
{ 
  // set pixel position
  if (0 == SetPixelPosition(x, y)) {
    // out of range 
    return 0;
  }
  // send 1 as data
  cacheMemLcd[cacheMemIndex] |= 1 << (x % 8);
  // success return
  return 1;
}
/***
 * @description Draw line by Bresenham algoritm
 * @surce       https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 *  
 * @param uint8_t x - position / 0 <= cols <= 83 
 * @param uint8_t y - position / 0 <= rows <= 47 
 * @return void
 */
char DrawLine(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2)
{
  // determinant
  int D;
  // deltas
  int8_t delta_x, delta_y;
  // steps
  int8_t trace_x = 1, trace_y = 1;

  // delta x
  delta_x = x2 - x1;
  // delta y
  delta_y = y2 - y1;

  // check if x2 > x1
  if (delta_x < 0) {
    // negate detla x
    delta_x = -delta_x;
    // negate step x
    trace_x = -trace_x;
  }

  // check if x2 > x1
  if (delta_y < 0) {
    // negate detla x
    delta_y = -delta_y;
    // negate step x
    trace_y = -trace_y;
  }

  // Bresenham condition
  // for m < 1 (dy < dx)
  if (delta_y < delta_x) {
    // calculate determinant
    D = 2*delta_y - delta_x;
    // draw first pixel
    DrawPixel(y1, x1);
    // check if x1 equal x2
    while (x1 != x2) {
      // update x1
      x1 += trace_x;
      // check if determinant is positive
      if (D >= 0) {
        // update y1
        y1 += trace_y;
        // update determinant
        D -= 2*delta_x;    
      }
      // update deteminant
      D += 2*delta_y;
      // draw first pixel
      DrawPixel(y1, x1);
    }
  // for m > 1 (dy > dx)    
  } else {
    // calculate determinant
    D = -2*delta_x - delta_y;
    // draw first pixel
    DrawPixel(y2, x2);
    // check if y2 equal y1
    while (y2 != y1) {
      // update y2
      y2 -= trace_y;
      // check if determinant is positive
      if (D >= 0) {
        // update y1
        x2 -= trace_x;
        // update determinant
        D += 2*delta_y;    
      }
      // update deteminant
      D -= 2*delta_x;
      // draw first pixel
      DrawPixel(y2, x2);
    }
  }
  // success return
  return 1;
}
