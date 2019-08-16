/**
*/

#ifndef __SPFD54124B_H__
#define __SPFD54124B_H__

#include <cstdint>
#include "display.h"
#include "gpio_manip.h"

#define SPFD54124B_SEND_CMD		    0
#define SPFD54124B_SEND_DATA	    0x100

/* READ COMMAND */
#define SPFD54124B_CMD_RDDID		  0x04 // ID (1 dummy read + 3 id)
#define SPFD54124B_CMD_RDDST      0x09 // Status (1 dummy read + 4 info)
#define SPFD54124B_CMD_RDDPM      0x0A // Power Mode (1 dummy read + 1 info)
#define SPFD54124B_CMD_RDDMADCTR  0x0B // MADCTR (1 dummy read + 1 info)
#define SPFD54124B_CMD_RDDCOLMOD  0x0C // Pixel Format (1 dummy read + 1 info)
#define SPFD54124B_CMD_RDDIM      0x0D // Image Mode (1 dummy read + 1 info)
#define SPFD54124B_CMD_RDDSM      0x0E // Signal Mode (1 dummy read + 1 info)
#define SPFD54124B_CMD_RDDSDR     0x0F // Self-diagnostic result (1 dummy read + 1 info)
#define SPFD54124B_CMD_RAMHD      0x2E // Memory read

/* WRITE COMMAND */
#define SPFD54124B_CMD_NOP		    0x00
#define SPFD54124B_CMD_SWRESET    0x01
#define SPFD54124B_CMD_SLPIN      0x10 // Sleep in & booster off
#define SPFD54124B_CMD_SLPOUT	    0x11 // Sleep out & booster on
#define SPFD54124B_CMD_PTLON      0x12 // Partial mode on
#define SPFD54124B_CMD_NORON	    0x13 // Partial off (Normal)

#define SPFD54124B_CMD_INVOFF	    0x20 // Display inversion off (Normal)
#define SPFD54124B_CMD_INVON      0x21 // Display inversion on
#define SPFD54124B_CMD_GAMSET     0x26 // Gamma curve select
#define SPFD54124B_CMD_DISPOFF    0x28 // Display off
#define SPFD54124B_CMD_DISPON	    0x29 // Display on
#define SPFD54124B_CMD_CASET	    0x2A // Column address set
#define SPFD54124B_CMD_RASET	    0x2B // Row address set
#define SPFD54124B_CMD_RAMWR	    0x2C // Memory write
#define SPFD54124B_CMD_RGBSET	    0x2D // LUT for 4k, 65k, 256k color display

#define SPFD54124B_CMD_PTLAR      0x30 // Partial start/end address set
#define SPFD54124B_CMD_SCRLAR     0x33 // Scroll area set
#define SPFD54124B_CMD_TEOFF      0x34 // Tearing effect line off
#define SPFD54124B_CMD_TEON       0x35 // Tearing effect mode set & on
#define SPFD54124B_CMD_MADCTR	    0x36 // Memory data access control
#define SPFD54124B_CMD_VSCSAD	    0x37 // Scroll start addess of RAM
#define SPFD54124B_CMD_IDMOFF     0x38 // Idle mode off
#define SPFD54124B_CMD_IDMON      0x39 // Idle mode on
#define SPFD54124B_CMD_COLMOD	    0x3A // Interface pixel format

#define SPFD54124B_CMD_RGBCTR     0xB0 // Set RGB signal control
#define SPFD54124B_CMD_FRMCTR1    0xB1 // In normal mode (Full colors)
#define SPFD54124B_CMD_FRMCTR2    0xB2 // In idle mode (8-colors)
#define SPFD54124B_CMD_FRMCTR3    0xB3 // In partial mode + Full colors


/* BITS */
#define SPFD54124B_CMD_GAMSET_GC0       0x01
#define SPFD54124B_CMD_GAMSET_GC1       0x02
#define SPFD54124B_CMD_GAMSET_GC2       0x04
#define SPFD54124B_CMD_GAMSET_GC3       0x08
#define SPFD54124B_CMD_GAMSET_GC4       0x10
#define SPFD54124B_CMD_GAMSET_GC5       0x20
#define SPFD54124B_CMD_GAMSET_GC6       0x40
#define SPFD54124B_CMD_GAMSET_GC7       0x80

#define SPFD54124B_CMD_COLMOD_MCU12bit	3			// MCU interface 12bit
#define SPFD54124B_CMD_COLMOD_MCU16bit	5			// MCU interface 16bit
#define SPFD54124B_CMD_COLMOD_MCU18bit	6			// MCU interface 18bit
#define SPFD54124B_CMD_COLMOD_RGB16bit	0x50			// RGB interface 16bit
#define SPFD54124B_CMD_COLMOD_RGB18bit	0x60			// RGB interface 18bit

#define SPFD54124B_CMD_MADCTR_MY	(1 << 7)		// Row Address Order
#define SPFD54124B_CMD_MADCTR_MX	(1 << 6)		// Column Address Order
#define SPFD54124B_CMD_MADCTR_MV	(1 << 5)		// Row/Column Exchange
#define SPFD54124B_CMD_MADCTR_ML	(1 << 4)		// Vertical Refresh Order
#define SPFD54124B_CMD_MADCTR_RGB	(1 << 3)		// RGB-BGR ORDER

#define LCD_VGA_BLACK (0x0000)
#define LCD_VGA_WHITE (0xFFFF)
#define LCD_VGA_RED   (0xF800)
#define LCD_VGA_GREEN (0x1FE0)
#define LCD_VGA_BLUE  (0x001F)


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
            const int _rst, _cs, _sda, _clk;
            Gpio::OPi1GpioManager &gpio_man;

            static constexpr int width = 128;
            static constexpr int height = 160;
            static constexpr int x_offset = 2;
            static constexpr int y_offset = 1;
            static constexpr int msg_size = 9;
            static constexpr int usleep_clk = 5;

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
