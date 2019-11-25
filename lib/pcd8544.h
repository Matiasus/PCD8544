/*** 
 * LCD driver PCD8544 / Nokia 5110, 3110 /
 * 
 * Copyright (C) 2019 Marian Hrinko.
 * Written by Marian Hrinko (mato.hrinko@gmail.com)
 *
 * @author      Marian Hrinko
 * @update      25.11.2019
 * @file        pcd8544.h
 * @tested      AVR Atmega16 / AVR Atmega8
 * @descript    Library designed for LCD with PCD8544 driver
 * @usage       LCD Resolution 48x84
 *              Ccommunication thorught 5 control wires (SCK, RST, DIN, CE, CS)
 * 
 */

#ifndef __PCD8544_H__
#define __PCD8544_H__

  // define clock
  #if defined(__AVR_ATmega8__)
    #define _FCPU 8000000
  #elif defined(__AVR_ATmega16__)
    #define _FCPU 16000000
  #endif
  // define port
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

  // @const Characters
  extern const char CHARACTERS[][5];

  /**
   * @desc    Initialise pcd8544 controller
   *
   * @param   void
   * @return  void
   */
  void Pcd8544Init(void);

  /**
   * @desc    Command send
   *
   * @param   char
   * @return  void
   */
  void CommandSend(char);

  /**
   * @desc    Data send
   *
   * @param   char
   * @return  void
   */
  void DataSend(char);

  /**
   * @desc    Reset Impulse
   *
   * @param   void
   * @return  void
   */
  void ResetImpulse(void);

  /**
   * @desc    Clear screen
   *
   * @param   void
   * @return  void
   */
  void ClearScreen(void);

  /**
   * @desc    Update screen
   *
   * @param   void
   * @return  void
   */
  void UpdateScreen(void);

  /**
   * @desc    Draw character
   *
   * @param   unsigned int
   * @return  char
   */
  char DrawChar(char);

  /**
   * @desc    Draw string
   *
   * @param   char*
   * @return  char
   */
  void DrawString(char*);

  /**
   * @desc    Set text position x, y
   *
   * @param   char x - position 0 <= x <=  5
   * @param   char y - position 0 <= y <= 14
   * @return  char
   */
  char SetTextPosition(char, char);

  /**
   * @desc    Set pixel position x, y
   *
   * @param   char x - position 0 <= x <= 47
   * @param   char y - position 0 <= y <= 83
   * @return  char
   */
  char SetPixelPosition(char, char);

  /**
   * @desc    Draw pixel on position x, y
   *
   * @param   char x - position
   * @param   char y - position
   * @return  void
   */
  char DrawPixel(char, char);

  /**
   * @desc    Draw line
   *
   * @param   char x - start x position
   * @param   char y - end x position
   * @param   char x - start y position
   * @param   char y - end y position
   * @return  CHAR
   */
  char DrawLine(char, char, char, char);

#endif
