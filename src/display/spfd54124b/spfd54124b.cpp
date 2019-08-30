/**
* autor: Egor Plotkin
*/

#include <unistd.h>
#include <iostream>
#include <cstring>
#include "spfd54124b.h"

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



namespace LcdEq
{
    NOKIA1616::NOKIA1616(int rst, int cs, int sda, int clk) : 
        gpio_man(Gpio::OPi1GpioManager::get_instance()),
        _rst(rst), _cs(cs), _sda(sda), _clk(clk)
    {
        gpio_man.cfg(_rst, Gpio::GPIO_OUT);
        gpio_man.cfg(_cs, Gpio::GPIO_OUT);
        gpio_man.cfg(_sda, Gpio::GPIO_OUT);
        gpio_man.cfg(_clk, Gpio::GPIO_OUT);

        //set size of current window
        window.x = window.y =  0;
        window.w = window.h = 0;
    }
 
    void NOKIA1616::clk()
    {
        gpio_man.write(_clk, Gpio::GPIO_HIGH);
        gpio_man.write(_clk, Gpio::GPIO_LOW);
    }
    void NOKIA1616::send_cmd1616(uint8_t cmd, uint16_t a, uint16_t b)
    {
        send_cmd(cmd);
        send_data((a>>8) & 0xFF);
        send_data(a & 0xFF);
        send_data((b>>8) & 0xFF);
        send_data(b & 0xFF);
    }
    void NOKIA1616::send(uint16_t data)
    {
        gpio_man.write(_cs, Gpio::GPIO_LOW);

        for(int i = 0; i < msg_size; i++)
        {
            Gpio::gpio_state_t state;
            if ((data & (0x0100 >> i)) == 0)
              state = Gpio::GPIO_LOW;
            else
              state = Gpio::GPIO_HIGH;
            gpio_man.write(_sda, state);
            clk();
        }

        gpio_man.write(_cs, Gpio::GPIO_HIGH);
    }

    void NOKIA1616::init()
    {
        gpio_man.write(_rst, Gpio::GPIO_LOW);
        delay(100); //100ms
        gpio_man.write(_rst, Gpio::GPIO_HIGH);
        delay(100); //100ms

        //TODO:: find the command 0xBA and field for this command
        /* extra commands */
        send(0xBA); send(0x107); send(0x115); //data order
        send(SPFD54124B_CMD_SLPOUT); //exit from sleep mode
        delay(120); //could take ~120ms
        send(SPFD54124B_CMD_NORON); //normal mode on
        
        send(SPFD54124B_CMD_COLMOD);
        send(SPFD54124B_SEND_DATA | SPFD54124B_CMD_COLMOD_MCU16bit );
        send(SPFD54124B_CMD_DISPON); //display on
        send(SPFD54124B_CMD_INVOFF); //inversion off
        send(SPFD54124B_CMD_NORON); //normal mode on
    }
    void NOKIA1616::send_pixel(pixel_rgb_t rgb)
    {
        rgb_color16bit color = formate_pixel(rgb);
        send_pixel(color);
    }
    void NOKIA1616::send_pixel(rgb_color16bit color)
    {
        send_data(color >> 8);
        send_data(color & 0xFF);
    }
    void NOKIA1616::send_pixel(rgb_color16bit color, uint16_t cnt)
    {
        while(cnt--) send_pixel(color);
    }
    void NOKIA1616::set_window(uint8_t x, uint8_t y, uint8_t w, uint8_t h)
    {
        win_size_t request_windows = { .x = x, .y = y, .w = w, .h = h };
        set_window(request_windows);
    }
    void NOKIA1616::set_window(win_size_t winsize)
    {
        if(memcmp(&window, &winsize, sizeof(win_size_t)) == 0)
            return;

        //are we still in size limits
        if( (winsize.x + winsize.w > width)
            || (winsize.y + winsize.h > height))
        {
            throw "Out of range";
        }

        // column start/end
        send_cmd1616(SPFD54124B_CMD_CASET, winsize.x + x_offset, 
                                            winsize.x + x_offset + winsize.w - 1);
        // page start/end
        send_cmd1616(SPFD54124B_CMD_RASET, winsize.y + y_offset, 
                                            winsize.y + y_offset + winsize.h - 1);
        // RAMWR
        send_cmd(SPFD54124B_CMD_RAMWR);

        //update window size
        window = winsize;
    }
    void NOKIA1616::fill_window(std::vector<rgb_color16bit>& palette)
    {
        if(palette.size() > (window.w * window.h))
        {
          //TODO implement this part
        }
        else
        {
          set_window(window);
          for(auto a : palette)
          {
            send_pixel(a);
          }
        }
    }
    void NOKIA1616::fill_window(rgb_color16bit color)
    {
        set_window(window); //need to send it to reset (don't know where we are right now)
        send_pixel(color, window.w * window.h); //fill all window with
    }
    void NOKIA1616::fill_background(rgb_color16bit color)
    {
        win_size_t ws = window;
        window.w = window.h = 0; //set to '0' to avoid ignoring of next command
        set_window(0, 0, width, height);
        send_pixel(color, width * height);
        set_window(ws); //return back window size
    }
    win_size_t NOKIA1616::get_window_size(void)
    {
        return window;
    }
    colors_t<uint8_t> NOKIA1616::get_resolution()
    {
        colors_t<uint8_t> bits;
        bits.red = 5;
        bits.green = 6;
        bits.blue = 5;
        return bits;
    }
}
