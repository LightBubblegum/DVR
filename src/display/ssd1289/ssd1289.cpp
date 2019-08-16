/**
* autor: Egor Plotkin
*/

#include <unistd.h>
#include "ssd1289.h"


namespace LcdEq
{
    SSD1289::SSD1289(int rs, int rst, int wr, int rd, int cs, lcd_pinouts_16bit_t *p_data_pins) 
        : gpio_manager(Gpio::OPi1GpioManager::get_instance()),
        _rs(rs), _wr(wr), _rd(rd), _cs(cs), _rst(rst), data_pins (*p_data_pins)
    {
        //gpio cfg for cmd
        //gpio_manager.cfg(cmd_pins.pins.cbegin, cmd_pins.pins.size, Gpio::GPIO_OUT);
        gpio_manager.cfg(_rs, Gpio::GPIO_OUT);
        gpio_manager.cfg(_wr, Gpio::GPIO_OUT);
        gpio_manager.cfg(_rd, Gpio::GPIO_OUT);
        gpio_manager.cfg(_cs, Gpio::GPIO_OUT);
        gpio_manager.cfg(_rst, Gpio::GPIO_OUT);
        //gpio cfg for data
        gpio_manager.cfg(data_pins.pins.cbegin, data_pins.pins.size, Gpio::GPIO_OUT);

    }

    void SSD1289::write_cmd(uint16_t cmd)
    {

    }

    void SSD1289::init()
    {
        gpio_manager.write(_rst, Gpio::GPIO_HIGH);
        usleep(5000); //delay 5 ms
        gpio_manager.write(_rst, Gpio::GPIO_LOW);
        usleep(15000); //delay 15 ms
        gpio_manager.write(_rst, Gpio::GPIO_HIGH);
        gpio_manager.write(_cs, Gpio::GPIO_HIGH);
        gpio_manager.write(_rd, Gpio::GPIO_HIGH);
        gpio_manager.write(_wr, Gpio::GPIO_HIGH);
        usleep(20000); //delay 20 ms

        gpio_manager.write(_cs, Gpio::GPIO_LOW);
    }
}
