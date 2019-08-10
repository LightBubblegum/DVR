/**
* autor: Egor Plotkin
*/

#include <unistd.h>
#include "equipment_lcd.h"

namespace LcdEq
{
    SSD1289::SSD1289(lcd_pinouts_cmd_t *p_cmd_pins, lcd_pinouts_16bit_t *p_data_pins) 
        : gpio_manager(Gpio::OPi1GpioManager::get_instance()),
        cmd_pins(*p_cmd_pins), data_pins (*p_data_pins)
    {
        //gpio cfg for cmd
        gpio_manager.cfg(cmd_pins.pins.cbegin, cmd_pins.pins.size, Gpio::GPIO_OUT);
        //gpio cfg for data
        gpio_manager.cfg(data_pins.pins.cbegin, data_pins.pins.size, Gpio::GPIO_OUT);

    }

    void SSD1289::write_cmd(uint16_t cmd)
    {

    }

    void SSD1289::init()
    {
        int rst = cmd_pins.pins[cmd_pins.RST];

        gpio_manager.write(rst, Gpio::GPIO_HIGH);
        usleep(5000); //delay 5 ms
        gpio_manager.write(rst, Gpio::GPIO_LOW);
        usleep(15000); //delay 15 ms
        gpio_manager.write(rst, Gpio::GPIO_HIGH);
        usleep(20000); //delay 20 ms

    }
}


