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

  // Success / Error
  // -----------------------------------
  #define PCD8544_SUCCESS   0
  #define PCD8544_ERROR     1

  // Command definition
  // -----------------------------------
  #define NOP               0x00

  // Function set
  // -----------------------------------
  // D7 D6 D5 D4 D3 D2 D1 D0  
  // 0   0  1  0  0 PD  V  H
  //
  // PD = {0, 1} => {Chip is active, Power Down}
  //  V = {0, 1} => {Horizontal addressing, Vertical adressing}
  //  H = {0, 1} => {Basic instruction set, Extended instruction set}
  #define FUNCTION_SET      0x20
  // PD
  #define MODE_ACTIVE       0x00
  #define MODE_P_DOWN       0x04
  // V
  #define HORIZ_ADDR_MODE   0x00
  #define VERTI_ADDR_MODE   0x02
  // H
  #define EXTEN_INS_SET     0x01
  #define BASIC_INS_SET     0x00

  // Display control
  // -----------------------------------
  // D7 D6 D5 D4 D3 D2 D1 D0  
  // 0   0  0  0  1  D  0  E
  //
  // D, E = {0, 0} => Display blank
  // D, E = {0, 1} => Normal mode
  // D, E = {1, 0} => All display segments on
  // D, E = {1, 1} => Inverse video mode
  #define DISPLAY_CONTROL   0x08
  // D, E
  #define DISPLAY_BLANK     0x00
  #define ALL_SEGMS_ON      0x01
  #define NORMAL_MODE       0x04
  #define INVERSE_MODE      0x05

  // Temperature coefficient
  // -----------------------------------
  // D7 D6 D5 D4 D3 D2  D1  D0  
  // 0   0  0  0  0  1 TC1 TC0
  //
  // TC1, TC0 = {0, 0} => VLCD temperature coefficient 0
  // TC1, TC0 = {0, 1} => VLCD temperature coefficient 1
  // TC1, TC0 = {1, 0} => VLCD temperature coefficient 2
  // TC1, TC0 = {1, 1} => VLCD temperature coefficient 3
  #define TEMP_CONTROL      0x04
  // TC1, TC0
  #define TEMP_COEF_1       0x00
  #define TEMP_COEF_2       0x01
  #define TEMP_COEF_3       0x02
  #define TEMP_COEF_4       0x03

  // Bias control
  // -----------------------------------
  // D7 D6 D5 D4 D3  D2  D1  D0  
  // 0   0  0  0  0 BS2 BS1 BS0
  //
  #define BIAS_CONTROL      0x10
  // BS2 BS1 BS0
  #define BIAS_1_100        0x00
  #define BIAS_1_80         0x01
  #define BIAS_1_65         0x02
  #define BIAS_1_48         0x03
  #define BIAS_1_34         0x04
  #define BIAS_1_24         0x05
  #define BIAS_1_16         0x06
  #define BIAS_1_8          0x07

  // AREA definition
  // -----------------------------------
  #define MAX_NUM_ROWS      6
  #define MAX_NUM_COLS      84
  #define CACHE_SIZE_MEM    (MAX_NUM_ROWS * MAX_NUM_COLS)

  // FUNCTION macros
  // -----------------------------------
  // clear bit
  #define CLR_BIT(port, bit)                ( ((port) &= ~(1 << (bit))) )
  // set bit
  #define SET_BIT(port, bit)                ( ((port) |= (1 << (bit))) )
  // bit is clear?
  #define IS_BIT_CLR(port, bit)             ( IS_BIT_SET(port, bit) ? 0 : 1 )
  // bit is set?
  #define IS_BIT_SET(port, bit)             ( ((port) & (1 << (bit))) ? 1 : 0 )
  // wait until bit is set
  #define WAIT_UNTIL_BIT_IS_SET(port, bit)  { while (IS_BIT_CLR(port, bit)); }

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
