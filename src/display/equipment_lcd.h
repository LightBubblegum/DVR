/**
*/

#ifndef __EQUIPMENT_LCD_H__
#define __EQUIPMENT_LCD_H__

#include <cstdint>
#include "display.h"
#include "gpio_manip.h"

namespace LcdEq
{
    typedef struct {
        enum cmd_pins_e{
            RS = 0, WR = 1, CS = 2, RST = 3,
            SER = 4, TOTAL = 5
        };
        std::array<int, cmd_pins_e::TOTAL> pins;
    } lcd_pinouts_cmd_t;

    typedef struct {
        enum data_pins_e{
            DB0 = 0, DB1 = 1, DB2 = 2, DB3 = 3,
            DB4 = 4, DB5 = 5, DB6 = 6, DB7 = 7,
            DB8 = 8, DB9 = 9, DB10 = 10, DB11 = 11,
            DB12 = 12, DB13 = 13, DB14 = 14, DB15 = 15,
            TOTAL = 16
        };
        std::array<int, data_pins_e::TOTAL> pins;
    } lcd_pinouts_16bit_t;

    class ILI9341
    {
    private:
        //default configuration
        enum rcmd_list
        {
            READ_DISP_IDENTIFICATION_INFO = 0x04,
            READ_DISP_STATUS = 0x09,
            READ_DISP_POWER_MODE = 0x0A,
            READ_DISP_MADCTL = 0x0B,
            READ_DISP_PIXEL_FORMAT = 0x0C,
            READ_DISP_IMAGE_FORMAT = 0x0D,
            READ_DISP_SIGNAL_MODE = 0x0E,
            READ_DISP_SELF_DIAGNOSTIC_RESULT = 0x0F,
            READ_MEMORY_CONTINUE = 0x3E,
            READ_DISP_BRIGHTNESS = 0x52,
            READ_CTRL_DISP = 0x54,
            READ_CONTENT_ADAPTIVE_BRIGHTNESS_CONTROL = 0x56,
            READ_CABC_MINIMUM_BRIGHTNES = 0x5F,
            READ_ID_1 = 0xDA,
            READ_ID_2 = 0xDB,
            READ_ID_3 = 0xDC,
            READ_ID4 = 0xD3,
        };
        enum wcmd_list
        {
            SOFTWARE_RESET = 0x01,
            ENTER_SLEEP_MODE = 0x10,
            SLEEP_OUT = 0x11,
            PARTIAL_MODE_ON = 0x12,
            NORMAL_DISPLAY_MODE_ON = 0x13,
            DISPLAY_INVERSION_OFF = 0x20,
            DISPLAY_INVERSION_ON = 0x21,
            GAMMA_SET = 0x26,
            DISPLAY_OFF = 0x28,
            DISPLAY_ON = 0x29,
            COLUMN_ADDR_SET = 0x2A,
            PAGE_ADDR_SET = 0x2B,
            MEMORY_WRITE = 0x2C,
            COLOR_SET = 0x2D,
            PARTIAL_AREA = 0x30,
            VERTICAL_SCROL_DEFINITION = 0x33,
            TEARING_EFFECT_LINE_OFF = 0x34,
            TEARING_EFFECT_LINE_ON = 0x35,
            MEMORY_ACCESS_CONTROL = 0x36,
            VERTICAL_SCROLLING_START_ADDR = 0x37,
            IDLE_MODE_OFF = 0x38,
            IDLE_MODE_ON = 0x39,
            PIXEL_FORMAT_SET = 0x3A,
            WRITE_MEMORY_CONTINUE = 0x3C,
            SET_TEAR_SCANLINE = 0x44,
            GET_SCAN_LINE = 0x45,
            WRITE_DISP_BRIGHTNESS = 0x51,
            WRITE_CTRL_DISP = 0x53,
            WRITE_CONTENT_ADAPTIVE_BRIGHTNESS_CONTROL = 0x55,
            WRITE_CABC_MINIMUM_BRIGHTNES = 0x5E,
            RGB_INTERFACE_SIG_CONTROL = 0xB0,
            FRAME_CTRL_NORMAL_MODE = 0xB1,
            FRAME_CTRL_IDAL_MODE = 0xB2,
            FRAME_CTRL_PARTIAL_MODE = 0xB3,
            DISP_INVERSION_CTRL = 0xB4,
            BLANKING_PORCH_CTRL = 0xB5,
            DISP_FUNC_CTRL = 0xB6,
            ENTRY_MODE_SET = 0xB7,
            BACKLIGHT_CTRL_1 = 0xB8,
            BACKLIGHT_CTRL_2 = 0xB9,
            BACKLIGHT_CTRL_3 = 0xBA,
            BACKLIGHT_CTRL_4 = 0xBB,
            BACKLIGHT_CTRL_5 = 0xBC,
            BACKLIGHT_CTRL_7 = 0xBE,
            BACKLIGHT_CTRL_8 = 0xBF,
            PWR_CTRL_1 = 0xC0,
            PWR_CTRL_2 = 0xC1,
            VCOM_CTRL_1 = 0xC5,
            VCOM_CTRL_2 = 0xC7,
            NV_MEMORY_WRITE = 0xD0,
            NV_MEMORY_PROTECTION_KEY = 0xD1,
            NV_MEMORY_STATUS_READ = 0xD2,
            POSITIVE_GAMMA_CORECTION = 0xE0,
            NEGATIVE_GAMMA_CORECTION = 0xE1,
            DIGITAL_GAMMA_CTRL_1 = 0xE2,
            DIGITAL_GAMMA_CTRL_2 = 0xE3,
            INTERFACE_CTRL = 0xF6,
        };

        static const int height = 240;
        static const int height = 320;

        lcd_pinouts_cmd_t cmd_pins; //command pins
        lcd_pinouts_16bit_t data_pins; //data pins
        Gpio::OPi1GpioManager &gpio_manager;

        int last_cmd = -1;

        uint16_t read_data(void);
        uint16_t read_cmd(void);
        void write_data(uint16_t);
        void write_cmd(uint16_t);

    public:
        ILI9341(lcd_pinouts_cmd_t *p_cmd_pins, 
                lcd_pinouts_16bit_t *p_data_pins);
        void init();
        void turn_on();
        void turn_off();
        void set_cursor_pos(int x, int y);
        void upload_pic(uint8_t red, uint8_t green, uint8_t blue);
    };

    class TFT_320QVT : public IDispDriver
    {
    public:
        TFT_320QVT();
        bool init() override;
        void show() override;
        std::size_t height() override;
        std::size_t width() override;
    };

}

#endif /* __EQUIPMENT_LCD_H__ */
/**
*/