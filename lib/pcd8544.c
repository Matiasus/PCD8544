/** 
 * --------------------------------------------------------------------------------------------+ 
 * @desc        LCD driver PCD8544 / Nokia 5110, 3110 /
 * --------------------------------------------------------------------------------------------+ 
 *              Copyright (C) 2020 Marian Hrinko.
 *              Written by Marian Hrinko (mato.hrinko@gmail.com)
 *
 * @author      Marian Hrinko
 * @datum       13.10.2020
 * @update      07.07.2021
 * @file        pcd8544.c
 * @version     2.0
 * @tested      AVR Atmega16
 *
 * @depend      font.h
 * --------------------------------------------------------------------------------------------+
 * @usage       LCD Resolution 48x84
 *              Ccommunication thorught 5 control wires (SCK, RST, DIN, CE, CS)
 */
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <string.h>
#include "font.h"
#include "pcd8544.h"

// @var array Chache memory Lcd 6 * 84 = 504 bytes
static char cacheMemLcd[CACHE_SIZE_MEM];

// @var array Chache memory char index
int cacheMemIndex = 0;

/**
 * @desc    Initialise pcd8544 controller
 *
 * @param   void
 *
 * @return  void
 */
void PCD8544_Init (void)
{
  // Actiavte pull-up register -> logical high on pin RST
  PORT |= (1 << RST);
  // Output: RST, SCK, DIN, CE, DC 
  DDR  |= (1 << RST) | 
          (1 << SCK) | 
          (1 << DIN) | 
          (1 << CE)  | 
          (1 << DC);
  // 1 ms delay and reset impulse
  PCD8544_ResetImpulse();
  // SPE  - SPI Enale
  // MSTR - Master device
  // SPR0 - Prescaler fclk/16 = 1MHz
  SPCR |= (1 << SPE)  | 
          (1 << MSTR) |
          (1 << SPR0);
  // extended instruction set
  PCD8544_CommandSend (FUNCTION_SET | EXTEN_INS_SET);
  // temperature set - temperature coefficient of IC / correction 3
  PCD8544_CommandSend (TEMP_CONTROL | TEMP_COEF_3);
  // bias 1:48 - optimum bias value
  PCD8544_CommandSend (BIAS_CONTROL | BIAS_1_48);
  // for mux 1:48 optimum operation voltage is Ulcd = 6,06.Uth
  // Ulcd = 3,06 + (Ucp6 to Ucp0) x 0,06
  // 6 < Ulcd < 8,05
  // command for operation voltage = 0x1 Ucp6 Ucp5 Ucp4 Ucp3 Ucp2 Ucp1 Ucp0
  // Ulcd = 0x11000010 = 7,02 V
  PCD8544_CommandSend (0xC2);
  // normal instruction set / horizontal adressing mode
  PCD8544_CommandSend (FUNCTION_SET | BASIC_INS_SET | HORIZ_ADDR_MODE);
  // normal mode
  PCD8544_CommandSend (DISPLAY_CONTROL | NORMAL_MODE);
}

/**
 * @desc    Command send
 *
 * @param   char
 * 
 * @return  void
 */
void PCD8544_CommandSend (char data)
{
  // chip enable - active low
  // PORT &= ~(1 << CE);
  CLR_BIT (PORT, CE);
  // command (active low)
  // PORT &= ~(1 << DC);
  CLR_BIT (PORT, DC);
  // transmitting data
  SPDR = data;
  // wait till data transmit
  // while (!(SPSR & (1 << SPIF)));
  WAIT_UNTIL_BIT_IS_SET (SPSR, SPIF);
  // chip disable - idle high
  // PORT |= (1 << CE);
  SET_BIT (PORT, CE);
}

/**
 * @desc    Data send
 *
 * @param   char 
 *
 * @return  void
 */
void PCD8544_DataSend (char data)
{
  // chip enable - active low
  // PORT &= ~(1 << CE);
  CLR_BIT (PORT, CE);
  // data (active high)
  // PORT |= 1 << DC;
  SET_BIT (PORT, DC);
  // transmitting data
  SPDR = data;
  // wait till data transmit
  // while (!(SPSR & (1 << SPIF)));
  WAIT_UNTIL_BIT_IS_SET (SPSR, SPIF);
  // chip disable - idle high
  // PORT |= (1 << CE);
  SET_BIT (PORT, CE);
}

/**
 * @desc    Reset impulse
 *
 * @param   void
 *
 * @return  void
 */
void PCD8544_ResetImpulse (void)
{
  // delay 1ms
  _delay_ms(1);
  // Reset Low 
  // PORT &= ~(1 << RST);
  CLR_BIT (PORT, RST);
  // delay 1ms
  _delay_ms(1);
  // Reset High
  // PORT |=  (1 << RST);
  SET_BIT (PORT, RST);
}

/**
 * @desc    Clear screen
 *
 * @param   void
 *
 * @return  void
 */
void PCD8544_ClearScreen (void)
{
  // null cache memory lcd
  memset (cacheMemLcd, 0x00, CACHE_SIZE_MEM);
}

/**
 * @desc    Update screen
 *
 * @param   void
 *
 * @return  void
 */
void PCD8544_UpdateScreen (void)
{
  int i;
  // set position x, y
  PCD8544_SetTextPosition(0, 0);
  // loop through cache memory lcd
  for (i=0; i<CACHE_SIZE_MEM; i++) {
    // write data to lcd memory
    PCD8544_DataSend(cacheMemLcd[i]);
  }  
}

/**
 * @desc    Draw character
 *
 * @param   char
 *
 * @return  char
 */
char PCD8544_DrawChar (char character)
{
  unsigned int i;
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
    cacheMemLcd[cacheMemIndex++] = pgm_read_byte(&FONTS[character - 32][i]);
  }
  //
  cacheMemIndex++;
  // return exit
  return 0;
}

/**
 * @desc    Draw string
 *
 * @param   char *
 *
 * @return  void
 */
void PCD8544_DrawString (char *str)
{
  unsigned int i = 0;
  // loop through 5 bytes
  while (str[i] != '\0') {
    // read characters and increment index
    PCD8544_DrawChar(str[i++]);
  }
}

/**
 * @desc    Set text position
 *
 * @param   char x - position / 0 <= rows <= 5 
 * @param   char y - position / 0 <= cols <= 14
 *
 * @return  char
 */
char PCD8544_SetTextPosition (char x, char y)
{
  // check if x, y is in range
  if ((x >= MAX_NUM_ROWS) ||
      (y >= (MAX_NUM_COLS / 6))) {
    // out of range
    return PCD8544_ERROR;
  }
  // normal instruction set / horizontal adressing mode
  PCD8544_CommandSend(0x20);
  // set x-position
  PCD8544_CommandSend((0x40 | x));
  // set y-position
  PCD8544_CommandSend((0x80 | (y * 6)));
  // calculate index memory
  cacheMemIndex = (y * 6) + (x * MAX_NUM_COLS);
  // success return
  return PCD8544_SUCCESS;
}

/**
 * @desc    Set pixel position
 *
 * @param   char x - position / 0 <= rows <= 47 
 * @param   char y - position / 0 <= cols <= 83
 * 
 * @return  char
 */
char PCD8544_SetPixelPosition (char x, char y)
{ 
  // check if x, y is in range
  if ((x >= (MAX_NUM_ROWS * 8)) ||
      (y >=  MAX_NUM_COLS)) {
    // out of range
    return PCD8544_ERROR;
  }
  // normal instruction set
  // horizontal adressing mode
  PCD8544_CommandSend(0x20);
  // set x-position
  PCD8544_CommandSend((0x40 | (x / 8)));
  // set y-position
  PCD8544_CommandSend((0x80 | y));
  // calculate index memory
  cacheMemIndex = y + ((x / 8) * MAX_NUM_COLS);
  // success return
  return PCD8544_SUCCESS;
}

/**
 * @desc    Draw pixel on x, y position
 *
 * @param   char x - position / 0 <= rows <= 47 
 * @param   char y - position / 0 <= cols <= 83
 *
 * @return  char
 */
char PCD8544_DrawPixel (char x, char y)
{ 
  // set pixel position
  if (PCD8544_SUCCESS == PCD8544_SetPixelPosition (x, y)) {
    // out of range 
    return PCD8544_ERROR;
  }
  // send 1 as data
  cacheMemLcd[cacheMemIndex] |= 1 << (x % 8);
  // success return
  return PCD8544_SUCCESS;
}

/**
 * @desc    Draw line by Bresenham algoritm
 * @surce   https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 *  
 * @param   char x - position / 0 <= cols <= 83 
 * @param   char x - position / 0 <= cols <= 83 
 * @param   char y - position / 0 <= rows <= 47 
 * @param   char y - position / 0 <= rows <= 47
 *
 * @return  char
 */
char PCD8544_DrawLine (char x1, char x2, char y1, char y2)
{
  // determinant
  int16_t D;
  // deltas
  int16_t delta_x, delta_y;
  // steps
  int16_t trace_x = 1, trace_y = 1;

  // delta x
  delta_x = x2 - x1;
  // delta y
  delta_y = y2 - y1;

  // check if x2 > x1
  if (delta_x < 0) {
    // negate delta x
    delta_x = -delta_x;
    // negate step x
    trace_x = -trace_x;
  }

  // check if y2 > y1
  if (delta_y < 0) {
    // negate detla y
    delta_y = -delta_y;
    // negate step y
    trace_y = -trace_y;
  }

  // Bresenham condition for m < 1 (dy < dx)
  if (delta_y < delta_x) {
    // calculate determinant
    D = 2*delta_y - delta_x;
    // draw first pixel
    PCD8544_DrawPixel(y1, x1);
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
      // draw next pixel
      PCD8544_DrawPixel(y1, x1);
    }
  // for m > 1 (dy > dx)    
  } else {
    // calculate determinant
    D = delta_y - 2*delta_x;
    // draw first pixel
    PCD8544_DrawPixel(y1, x1);
    // check if y2 equal y1
    while (y1 != y2) {
      // update y1
      y1 += trace_y;
      // check if determinant is positive
      if (D <= 0) {
        // update y1
        x1 += trace_x;
        // update determinant
        D += 2*delta_y;    
      }
      // update deteminant
      D -= 2*delta_x;
      // draw next pixel
      PCD8544_DrawPixel(y1, x1);
    }
  }
  // success return
  return PCD8544_SUCCESS;
}
