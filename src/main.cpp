/**
 * autor: Egor Plotkin
 */

#include <iostream>
#include <unistd.h>
#include "spfd54124b.h"

using namespace std;

#define RST_PIN     (21)
#define CS_PIN      (22)
#define MOSI_PIN    (23)
#define SCLK_PIN    (24)

int main(int argc, char *argv[])
{
    cout << "Programm working" << endl;

    LcdEq::NOKIA1616 n1616(RST_PIN, CS_PIN, MOSI_PIN, SCLK_PIN);
    n1616.init();

    rgb_color16bit color = LCD_VGA_BLACK;
    while(1)
    {
      switch(color)
      {
        case LCD_VGA_BLACK:
          color = LCD_VGA_BLUE;
          break;
        case LCD_VGA_BLUE:
          color = LCD_VGA_GREEN;
          break;
        case LCD_VGA_GREEN:
          color = LCD_VGA_RED;
          break;
        case LCD_VGA_RED:
          color = LCD_VGA_WHITE;
          break;
        case LCD_VGA_WHITE:
          color = LCD_VGA_BLACK;
          break;
      }
      n1616.fill_background(color);
    }

	return 0;
}
