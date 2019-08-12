/**
*/

#ifndef __SPFD54124B_H__
#define __SPFD54124B_H__

#include <cstdint>
#include "display.h"
#include "gpio_manip.h"

#define SPFD54124B_SEND_CMD		0
#define SPFD54124B_SEND_DATA	0x100

#define SPFD54124B_CMD_NOP		0x00
#define SPFD54124B_CMD_SLPOUT	0x11
#define SPFD54124B_CMD_NORON	0x13

#define SPFD54124B_CMD_INVOFF	0x20
#define SPFD54124B_CMD_DISPON	0x29
#define SPFD54124B_CMD_CASET	0x2A
#define SPFD54124B_CMD_RASET	0x2B
#define SPFD54124B_CMD_RAMWR	0x2C
#define SPFD54124B_CMD_RGBSET	0x2D

#define SPFD54124B_CMD_MADCTR	0x36
#define SPFD54124B_CMD_VSCSAD	0x37
#define SPFD54124B_CMD_COLMOD	0x3A

#define SPFD54124B_CMD_COLMOD_MCU12bit	3			// MCU interface 12bit
#define SPFD54124B_CMD_COLMOD_MCU16bit	5			// MCU interface 16bit
#define SPFD54124B_CMD_COLMOD_MCU18bit	6			// MCU interface 18bit
#define SPFD54124B_CMD_COLMOD_RGB16bit	50			// RGB interface 16bit
#define SPFD54124B_CMD_COLMOD_RGB18bit	60			// RGB interface 18bit

#define SPFD54124B_CMD_MADCTR_MY	(1 << 7)		// Row Address Order
#define SPFD54124B_CMD_MADCTR_MX	(1 << 6)		// Column Address Order
#define SPFD54124B_CMD_MADCTR_MV	(1 << 5)		// Row/Column Exchange
#define SPFD54124B_CMD_MADCTR_ML	(1 << 4)		// Vertical Refresh Order
#define SPFD54124B_CMD_MADCTR_RGB	(1 << 3)		// RGB-BGR ORDER

typedef uint16_t rgb_color16bit;
typedef struct {
    uint16_t red : 5;
    uint16_t green : 6;
    uint16_t blue : 5;
}pixel_rgb_t;

namespace LcdEq
{
    class NOKIA1616
    {
        private:
            int _rst, _cs, _sda, _clk;
            Gpio::OPi1GpioManager &gpio_man;

            static constexpr int width = 128;
            static constexpr int height = 160;
            static constexpr int x_offset = 2;
            static constexpr int y_offset = 1;
            static constexpr int msg_size = 9;
            static constexpr int usleep_clk = 100;

            void clk();
            void send_cmd1616(uint8_t cmd, uint16_t a, uint16_t b);
            void send_cmd(uint8_t data) { send(SPFD54124B_SEND_CMD | data); }
            void send_data(uint8_t data) { send(SPFD54124B_SEND_DATA | data); }
            void send(uint16_t data);
        public:
            static rgb_color16bit formate_pixel(pixel_rgb_t rgb)
            {
                rgb_color16bit red, green, blue;
                red = (((rgb_color16bit)rgb.red & 0x1F) << 11);
                green = (((rgb_color16bit)rgb.green & 0x3F) << 5);
                blue = ((rgb_color16bit)rgb.blue & 0x1F);

                return red | green | blue;
            }

            NOKIA1616(int rst, int cs, int sda, int clk);
            void init();
            void send_pixel(rgb_color16bit color);
            void send_pixel(rgb_color16bit color, uint16_t cnt);
            void set_window(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
            void fill_background(rgb_color16bit color);
            int get_width() { return width; }
            int get_height() { return height; }
    };
}
#endif /* __SPFD54124B_H__ */