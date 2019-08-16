/**
 * 
 * 
 */

#ifndef __GPIO_MANIP_H__
#define __GPIO_MANIP_H__

#include <wiringPi.h>
#include <array>
#include <iterator>
#include <exception>
#include <experimental/array>
#include <type_traits>

namespace Gpio
{
    typedef enum {
        GPIO_HIGH,
        GPIO_LOW
    }gpio_state_t;

    typedef enum {
        GPIO_OUT,
        GPIO_IN
    }gpio_mode_t;

    class IGpioManip
    {
    public:
        virtual ~IGpioManip() {};
        virtual void cfg(int pin, gpio_mode_t mode) = 0;
        virtual gpio_state_t read(int pin) = 0;
        virtual void write(int pin, gpio_state_t state) = 0;
    };

    class OPiGpio : public IGpioManip
    {
    public:
        OPiGpio() {};
        ~OPiGpio() {};
        void cfg(int pin, gpio_mode_t mode) override;
        gpio_state_t read(int pin) override;
        void write(int pin, gpio_state_t state) override;
    };


    class OPi1GpioManager : public IGpioManip
    {
    private:
        static constexpr int TOTAL_GPIO = 32;
        static constexpr int TOTAL_NONEXISTED_GPIO = 4;
        static constexpr std::array<int, TOTAL_NONEXISTED_GPIO> NONEXISTED_PINS = { 17,18,19,20 };
        OPiGpio opi_gpio;
        std::array<gpio_mode_t, TOTAL_GPIO> last_mode;
 
        virtual ~OPi1GpioManager() {};
        OPi1GpioManager();
        OPi1GpioManager( const OPi1GpioManager& );
        OPi1GpioManager& operator = ( OPi1GpioManager& );
    public:
        static OPi1GpioManager& get_instance() {
            static OPi1GpioManager instace;
            return instace;
        }
        static bool is_manipulated(int pin);

        void cfg(int pin, gpio_mode_t mode) override;
        gpio_state_t read(int pin) override;
        void write(int pin, gpio_state_t state) override;

        void cfg(const int *p_pin_array, int len, gpio_mode_t mode);
        void write(const int *p_pin_array, int len, gpio_state_t state);
    };

} // namespace gpio


#endif /* __GPIO_MANIP_H__ */
/**
*/
