/*** 
 * LCD driver for controller pcd8544 / Nokia 5110, 3110 /
 *
 * Copyright (C) 2016 Marian Hrinko.
 * Written by Marian Hrinko (mato.hrinko@gmail.com)
 *
 */
#ifndef __PCD8544_H__
#define __PCD8544_H__

  #ifndef PORT
    #define PORT PORTB
  #endif
  #ifndef DDR
    #define DDR  DDRB
  #endif
  #ifndef SCK
    #define SCK  PB7  // SCK
  #endif
  #ifndef RST
    #define RST  PB6  // MISO
  #endif
  #ifndef DIN
    #define DIN  PB5  // MOSI
  #endif
  #ifndef CE
    #define CE   PB4  // SS
  #endif
  #ifndef DC
    #define DC   PB1  // INT2
  #endif

  #define MAX_NUM_ROWS 6
  #define MAX_NUM_COLS 84
  #define CACHE_SIZE_MEM (MAX_NUM_ROWS * MAX_NUM_COLS)

  /** @const Characters */
  extern const uint8_t CHARACTERS[][5];

  /** @enum Command or data */
  typedef enum {
    DATA = 1,     // active high
    COMMAND = 0,  // active low
  } enumCmdOrData;

  /***
   * Initialise pcd8544 controller
   *
   * @param void
   * @return void
   */
  void Pcd8544Init(void);

  /***
   * Command/data send
   *
   * @param EnumCmdOrData /see pcd8544.h/
   * @param uint8_t
   * @return void
   */
  void CmdOrDataSend(enumCmdOrData, uint8_t);

  /***
   * Reset Impulse
   *
   * @param void
   * @return void
   */
  void ResetImpulse(void);

  /***
   * Clear screen
   *
   * @param void
   * @return void
   */
  void ClearScreen(void);

  /***
   * Update screen
   *
   * @param void
   * @return void
   */
  void UpdateScreen(void);

  /***
   * Draw character
   *
   * @param char
   * @return void
   */
  char DrawChar(char);

  /***
   * Draw string
   *
   * @param char*
   * @return void
   */
  void DrawString(char*);

  /***
   * Set text position x, y
   *
   * @param uint8_t x - position 0 <= x <=  5
   * @param uint8_t y - position 0 <= y <= 14
   * @return void
   */
  char SetTextPosition(uint8_t, uint8_t);

  /***
   * Set pixel position x, y
   *
   * @param uint8_t x - position 0 <= x <= 47
   * @param uint8_t y - position 0 <= y <= 83
   * @return void
   */
  char SetPixelPosition(uint8_t, uint8_t);

  /***
   * Draw pixel on position x, y
   *
   * @param uint8_t x - position
   * @param uint8_t y - position
   * @return void
   */
  char DrawPixel(uint8_t, uint8_t);

  /***
   * Draw line
   *
   * @param uint8_t x - position
   * @param uint8_t y - position
   * @return void
   */
  char DrawLine(uint8_t, uint8_t, uint8_t, uint8_t);

#endif
