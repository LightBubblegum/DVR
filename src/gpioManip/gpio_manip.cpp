/**
 * 
*/

#include <cassert>
#include "gpio_manip.h"

namespace Gpio
{
//==============================================================
    void OPiGpio::cfg(int pin, gpio_mode_t mode)
    {
        assert (mode == GPIO_IN || mode == GPIO_OUT);

        int pin_mode;
        switch (mode)
        {
            case GPIO_IN:
                pin_mode = INPUT;
                break;
            case GPIO_OUT:
                pin_mode = OUTPUT;
                break;
            default:
                //TODO:: throw through std::exception
                throw "Selected mode is not supported for pin";
                break;
        }
        pinMode(pin, pin_mode);
    }

    gpio_state_t OPiGpio::read(int pin)
    {
        return digitalRead(pin) == LOW? GPIO_LOW: GPIO_HIGH;
    }

    void OPiGpio::write(int pin, gpio_state_t state)
    {
        int new_state = state == GPIO_LOW? LOW: HIGH;
        digitalWrite(pin, new_state);
    }
//==============================================================
    OPi1GpioManager::OPi1GpioManager()
    {
      wiringPiSetup();
      last_mode.fill(GPIO_IN); //mark all last state as "input"
    }

    bool OPi1GpioManager::is_manipulated(int pin)
    {
        assert (pin >= 0 && pin < TOTAL_GPIO);

        for (auto elem : NONEXISTED_PINS)
        {
            if (elem == pin)
                return false;
        }
        return true;
    }

    void OPi1GpioManager::cfg(int pin, gpio_mode_t mode)
    {
        assert (pin >= 0 && pin < TOTAL_GPIO);

        if(is_manipulated(pin))
        {
            opi_gpio.cfg(pin, mode);
            last_mode[pin] = mode;
        }
        else
        {
            //TODO:: throw through std::exception
            throw "Pin " + std::to_string(pin) + " is not connected to CPU";
        }
    }

    gpio_state_t OPi1GpioManager::read(int pin)
    {
        assert (pin >= 0 && pin < TOTAL_GPIO);

        gpio_state_t ret;
        if (last_mode[pin] == GPIO_OUT)
        {
            //reconfigure pin, then read and turn back 
            opi_gpio.cfg(pin, GPIO_IN);
            ret = read(pin);
            opi_gpio.cfg(pin, GPIO_OUT);
        }
        else
        {
            ret = opi_gpio.read(pin);
        }
        return ret;
    }

    void OPi1GpioManager::write(int pin, gpio_state_t state) 
    {
        assert (pin >= 0 && pin < TOTAL_GPIO);

        if (last_mode[pin] == GPIO_IN)
        {
            opi_gpio.cfg(pin, GPIO_OUT);
            write(pin, state);
            opi_gpio.cfg(pin, GPIO_IN);
        }
        else
        {
            opi_gpio.write(pin, state);
        }
    }

    void OPi1GpioManager::write(const int *p_pin_array, int len, gpio_state_t state)
    {
        assert (p_pin_array != NULL && len > 0);

        for (int i = 0; i < len; ++i)
            this->write(p_pin_array[i], state);
    }

    void OPi1GpioManager::cfg(const int *p_pin_array, int len, gpio_mode_t mode)
    {
        assert (p_pin_array != NULL && len > 0);

        for (int i = 0; i < len; ++i)
            this->cfg(p_pin_array[i], mode);
    }

    int OPi1GpioManager::change_prio(int prio)
    {
        assert (prio >= 0 && prio <= MAX_GPIO_PRIO);

        //set priority for gpio
        return piHiPri(prio);
    }

    //==============================================================
} // namespace gpio

