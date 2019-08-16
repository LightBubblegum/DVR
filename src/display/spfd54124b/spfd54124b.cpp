/**
* autor: Egor Plotkin
*/

#include <unistd.h>
#include "spfd54124b.h"
#include <iostream>

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
    }
 
    void NOKIA1616::clk()
    {
        gpio_man.write(_clk, Gpio::GPIO_HIGH);
//        usleep(usleep_clk);
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
        send_cmd1616(SPFD54124B_CMD_CASET, x, x+w-1);	// column start/end
        send_cmd1616(SPFD54124B_CMD_RASET, y, y+h-1);	// page start/end
        send_cmd(SPFD54124B_CMD_RAMWR);				    // RAMWR
    }
    void NOKIA1616::fill_background(rgb_color16bit color)
    {
        set_window(0, 0, width, height);
        send_pixel(color, width * height);
    }
}
