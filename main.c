/** 
 * ---------------------------------------------------+ 
 * @desc        Main file
 * ---------------------------------------------------+ 
 * @copyright   Copyright (C) 2020 Marian Hrinko.
 * @author      Marian Hrinko
 * @email       mato.hrinko@gmail.com
 * @datum       22.12.2016
 * @update      04.12.2020
 * @file        main.c
 * @version     2.0
 * @tested      AVR Atmega16
 * ---------------------------------------------------+
 */
#include "lib/pcd8544.h"

/**
 * @desc    Main function
 *
 * @param   Void
 *
 * @return  Void
 */
int main(void)
{
  // init LCD
  PCD8544_Init();
  // clear screen
  PCD8544_ClearScreen();
  // set position
  PCD8544_SetTextPosition(0, 3);
  // draw string
  PCD8544_DrawString("Init LCD");
  // update
  PCD8544_UpdateScreen();

  // EXIT
  // ------------------------------------------------- 
  // return & exit
  return 0;
}
