/**
*/

#ifndef __SPFD54124B_H__
#define __SPFD54124B_H__

#include <cstdint>
#include <vector>
#include "colors.h"
#include "display.h"
#include "gpio_manip.h"
#include "equipment_lcd.h"

#define SPFD54124B_SEND_CMD         0
#define SPFD54124B_SEND_DATA        0x100

#define LCD_VGA_BLACK   (0x0000)
#define LCD_VGA_WHITE   (0xFFFF)
#define LCD_VGA_RED     (0xF800)
#define LCD_VGA_GREEN   (0x1FE0)
#define LCD_VGA_BLUE    (0x001F)


namespace LcdEq
{
  typedef uint16_t rgb_color16bit;

  struct pixel_rgb_t
  {
    uint16_t red : 5;
    uint16_t green : 6;
    uint16_t blue : 5;
  };
  
  class NOKIA1616 : public IResolution
  {
       public: //static
            static rgb_color16bit formate_pixel(pixel_rgb_t rgb)
            {
                rgb_color16bit red, green, blue;
                red = (((rgb_color16bit)rgb.red & 0x1F) << 11);
                green = (((rgb_color16bit)rgb.green & 0x3F) << 5);
                blue = ((rgb_color16bit)rgb.blue & 0x1F);

                return red | green | blue;
            }
            static int get_width() { return width; }
            static int get_height() { return height; }
 
      public:
            NOKIA1616(int rst, int cs, int sda, int clk);
            void init();
            void send_pixel(pixel_rgb_t rgb);
            void send_pixel(rgb_color16bit color);
            void send_pixel(rgb_color16bit color, uint16_t cnt);
            void set_window(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
            void set_window(win_size_t winsize);
            void fill_window(std::vector<rgb_color16bit> &palette);
            void fill_window(rgb_color16bit color);
            void fill_background(rgb_color16bit color);
            win_size_t get_window_size(void);
            // inherited interfaces
            colors_t<uint8_t> get_resolution() override;
      private:
            static constexpr int width = 128;
            static constexpr int height = 160;
            static constexpr int x_offset = 2;
            static constexpr int y_offset = 1;
            static constexpr int msg_size = 9;

            const int _rst, _cs, _sda, _clk;

            Gpio::OPi1GpioManager &gpio_man;
            win_size_t window;

            void clk();
            void send_cmd1616(uint8_t cmd, uint16_t a, uint16_t b);
            void send_cmd(uint8_t data) { send(SPFD54124B_SEND_CMD | data); }
            void send_data(uint8_t data) { send(SPFD54124B_SEND_DATA | data); }
            void send(uint16_t data);
  };
}
#endif /* __SPFD54124B_H__ */
