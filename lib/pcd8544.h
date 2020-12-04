/** 
 * --------------------------------------------------------------------------------------------+ 
 * @desc        LCD driver PCD8544 / Nokia 5110, 3110 /
 * --------------------------------------------------------------------------------------------+ 
 *              Copyright (C) 2020 Marian Hrinko.
 *              Written by Marian Hrinko (mato.hrinko@gmail.com)
 *
 * @author      Marian Hrinko
 * @datum       13.10.2020
 * @file        pcd8544.h
 * @version     2.0
 * @tested      AVR Atmega16
 *
 * @depend      font.h
 * --------------------------------------------------------------------------------------------+
 * @usage       LCD Resolution 48x84
 *              Ccommunication thorught 5 control wires (SCK, RST, DIN, CE, CS)
 */

#ifndef __PCD8544_H__
#define __PCD8544_H__

  // define port
  #ifndef PORT
    #define PORT            PORTB
  #endif
  #ifndef DDR
    #define DDR             DDRB
  #endif
  #ifndef SCK
    #define SCK             PB7  // SCK
  #endif
  #ifndef RST
    #define RST             PB6  // MISO
  #endif
  #ifndef DIN
    #define DIN             PB5  // MOSI
  #endif
  #ifndef CE
    #define CE              PB4  // SS
  #endif
  #ifndef DC
    #define DC              PB1  // INT2
  #endif

  #define PCD8544_SUCCESS   0
  #define PCD8544_ERROR     1

  #define MAX_NUM_ROWS      6
  #define MAX_NUM_COLS      84
  #define CACHE_SIZE_MEM (MAX_NUM_ROWS * MAX_NUM_COLS)

  /**
   * @desc    Initialise pcd8544 controller
   *
   * @param   void
   *
   * @return  void
   */
  void PCD8544_Init (void);

  /**
   * @desc    Command send
   *
   * @param   char
   *
   * @return  void
   */
  void PCD8544_CommandSend (char);

  /**
   * @desc    Data send
   *
   * @param   char
   *
   * @return  void
   */
  void PCD8544_DataSend (char);

  /**
   * @desc    Reset Impulse
   *
   * @param   void
   *
   * @return  void
   */
  void PCD8544_ResetImpulse (void);

  /**
   * @desc    Clear screen
   *
   * @param   void
   *
   * @return  void
   */
  void PCD8544_ClearScreen (void);

  /**
   * @desc    Update screen
   *
   * @param   void
   *
   * @return  void
   */
  void PCD8544_UpdateScreen (void);

  /**
   * @desc    Draw character
   *
   * @param   char
   *
   * @return  char
   */
  char PCD8544_DrawChar (char);

  /**
   * @desc    Draw string
   *
   * @param   char *
   *
   * @return  char
   */
  void PCD8544_DrawString (char *);

  /**
   * @desc    Set text position x, y
   *
   * @param   char x - position 0 <= x <=  5
   * @param   char y - position 0 <= y <= 14
   *
   * @return  char
   */
  char PCD8544_SetTextPosition (char, char);

  /**
   * @desc    Set pixel position x, y
   *
   * @param   char x - position 0 <= x <= 47
   * @param   char y - position 0 <= y <= 83
   *
   * @return  char
   */
  char PCD8544_SetPixelPosition (char, char);

  /**
   * @desc    Draw pixel on position x, y
   *
   * @param   char x - position
   * @param   char y - position
   *
   * @return  char
   */
  char PCD8544_DrawPixel (char, char);

  /**
   * @desc    Draw line
   *
   * @param   char x - start x position
   * @param   char y - end x position
   * @param   char x - start y position
   * @param   char y - end y position
   *
   * @return  char
   */
  char PCD8544_DrawLine (char, char, char, char);

#endif
