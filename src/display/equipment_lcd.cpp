/**
* autor: Egor Plotkin
*/

#include "equipment_lcd.h"

namespace LcdEq
{
    ILI9341::ILI9341(lcd_pinouts_cmd_t *p_cmd_pins, lcd_pinouts_16bit_t *p_data_pins) 
        : gpio_manager(Gpio::OPi1GpioManager::get_instance())
    {
        cmd_pins = *p_cmd_pins;
        data_pins = *p_data_pins;

        //gpio cfg for cmd
        gpio_manager.cfg(cmd_pins.pins.cbegin, cmd_pins.pins.size, Gpio::GPIO_OUT);
        //gpio cfg for data
        gpio_manager.cfg(data_pins.pins.cbegin, data_pins.pins.size, Gpio::GPIO_OUT);

    }

    void ILI9341::init()
    {
        
    }
}


