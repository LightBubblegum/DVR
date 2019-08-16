/**
*/

#ifndef __SSD1289_H__
#define __SSD1289_H__

#include <cstdint>
#include "display.h"
#include "gpio_manip.h"

namespace LcdEq
{
    class SSD1289
    {
    private:
        //default configuration
        enum rcmd_list
        {
            RAM_DATA_READ = 0x22,
        };
        enum wcmd_list
        {
            OSCILATION_START = 0x00,
            DRIVER_OUTPUT_CTRL = 0x01,
            LCD_DRIVE_AC_CTRL = 0x02,
            PWR_CTRL_1 = 0x03,
            COMPARE_REGISTR_1 = 0x05,
            COMPARE_REGISTR_2 = 0x06,
            DISP_CTRL = 0x07,
            FRAME_CYCLE_CTRL = 0x0B,
            PWR_CTRL_2 = 0x0C,
            PWR_CTRL_3 = 0x0D,
            PWR_CTRL_4 = 0x0E,
            GATE_SCAN_START_POSITION = 0x0F,
            SLEEP_MODE = 0x10,
            ENTRY_MODE = 0x11,
            HORIZONTAL_PORCH = 0x16,
            VERTICAL_PORCH = 0x17,
            PWR_CTRL_5 = 0x1E,
            RAM_DATA_WRITE = 0x22,
            RAM_DATA_WRITE_MASK_1 = 0x23,
            RAM_DATA_WRITE_MASK_2 = 0x24,
            VCOM_OTP_1 = 0x28,
            VCOM_OTP_2 = 0x29,
            GAMMA_CTRL_1 = 0x30,
            GAMMA_CTRL_2 = 0x31,
            GAMMA_CTRL_3 = 0x32,
            GAMMA_CTRL_4 = 0x33,
            GAMMA_CTRL_5 = 0x34,
            GAMMA_CTRL_6 = 0x35,
            GAMMA_CTRL_7 = 0x36,
            GAMMA_CTRL_8 = 0x37,
            GAMMA_CTRL_9 = 0x3A,
            GAMMA_CTRL_10 = 0x3B,
            VERTICAL_SCROLL_CTRL_1 = 0x41,
            VERTICAL_SCROLL_CTRL_2 = 0x42,
            HORIZONTAL_RAM_ADDR_POS = 0x44,
            VERTICAL_RAM_ADDR_START_POS = 0x45,
            VERTICAL_RAM_ADDR_END_POS = 0x46,
            FIRST_WINDOW_START = 0x48,
            FIRST_WINDOW_END = 0x49,
            SECOND_WINDOW_START = 0x4A,
            SECOND_WINDOW_END = 0x4B,
            SET_GDDRAM_X_ADDR_CNT = 0x4E,
            SET_GDDRAM_Y_ADDR_CNT = 0x4F,
        };

        enum bits_oscilation_start
        {
            OSCEN = 0x0001
        };
        enum bits_driver_output_ctrl
        {
            MUX0 = 0x0001,
            MUX1 = 0x0002,
            MUX2 = 0x0004,
            MUX3 = 0x0008,
            MUX4 = 0x0010,
            MUX5 = 0x0020,
            MUX6 = 0x0040,
            MUX7 = 0x0080,
            MUX8 = 0x0100,
            TB = 0x0200,
            SM = 0x0400,
            BGR = 0x0800,
            CAD = 0x1000,
            REV = 0x2000,
            RL = 0x4000,
        };
        enum bits_lcd_drive_ac_ctrl
        {
            NW0 = 0x0001,
            NW1 = 0x0002,
            NW2 = 0x0004,
            NW3 = 0x0008,
            NW4 = 0x0010,
            NW5 = 0x0020,
            NW6 = 0x0040,
            NW7 = 0x0080,
            WSMD = 0x0100,
            EOR = 0x0200,
            BC = 0x0400,
            ENWS = 0x0800,
            FLD = 0x1000
        };
        enum bits_pwr_ctrl_1
        {
            AP0 = 0x0002,
            AP1 = 0x0004,
            AP2 = 0x0008,
            DC0 = 0x0010,
            DC1 = 0x0020,
            DC2 = 0x0040,
            DC3 = 0x0080,
            BT0 = 0x0200,
            BT1 = 0x0400,
            BT2 = 0x0800,
            DCT0 = 0x1000,
            DCT1 = 0x2000,
            DCT2 = 0x4000,
            DCT3 = 0x8000
        };
        enum bits_compare_registr_1
        {
            CPG0 = 0x0004,
            CPG1 = 0x0008,
            CPG2 = 0x0010,
            CPG3 = 0x0020,
            CPG4 = 0x0040,
            CPG5 = 0x0080,
            CPR0 = 0x0400,
            CPR1 = 0x0800,
            CPR2 = 0x1000,
            CPR3 = 0x2000,
            CPR4 = 0x4000,
            CPR5 = 0x8000,
        };
        enum bits_compare_registr_2
        {
            CPB0 = 0x0004,
            CPB1 = 0x0008,
            CPB2 = 0x0010,
            CPB3 = 0x0020,
            CPB4 = 0x0040,
            CPB5 = 0x0080,
        };
        enum bits_disp_ctrl
        {
            D0 = 0x0001,
            D1 = 0x0002,
            CM = 0x0008,
            DTE = 0x0010,
            GON = 0x0020,
            SPT = 0x0100,
            VLE1 = 0x0200,
            VLE2 = 0x0400,
            PT0 = 0x0800,
            PT1 = 0x1000,
        };
        enum bits_frame_cycle_ctrl
        {
            RTN0 = 0x0001,
            RTN1 = 0x0002,
            RTN2 = 0x0004,
            RTN3 = 0x0008,
            SRTN = 0x0010,
            SDIV = 0x0020,
            DIV0 = 0x0040,
            DIV1 = 0x0080,
            EQ0 = 0x0100,
            EQ1 = 0x0200,
            EQ2 = 0x0400,
            SDT0 = 0x1000,
            SDT1 = 0x2000,
            NO0 = 0x4000,
            NO1 = 0x8000,
        };
        enum bits_pwr_ctrl_2
        {
            VRC0 = 0x0001,
            VRC1 = 0x0002,
            VRC2 = 0x0004,
        };
        enum bits_pwr_ctrl_3
        {
            VRH0 = 0x0001,
            VRH1 = 0x0002,
            VRH2 = 0x0003,
            VRH3 = 0x0004,
        };
        enum bits_pwr_ctrl_4
        {
            VDV0 = 0x0100,
            VDV1 = 0x0200,
            VDV2 = 0x0400,
            VDV3 = 0x0800,
            VDV4 = 0x0100,
            VCOMG = 0x2000,
        };
        enum bits_gate_scan_start_position
        {
            SCN0 = 0x0001,
            SCN1 = 0x0002,
            SCN2 = 0x0004,
            SCN3 = 0x0008,
            SCN4 = 0x0010,
            SCN5 = 0x0020,
            SCN6 = 0x0040,
            SCN7 = 0x0080,
            SCN8 = 0x0100,
        };
        enum bits_sleep_mode
        {
            SLP = 0x0001
        };
        enum bits_entry_mode
        {
            LG0 = 0x0001,
            LG1 = 0x0002,
            LG2 = 0x0004,
            AM = 0x0008,
            ID0 = 0x0010,
            ID1 = 0x0020,
            TY0 = 0x0040,
            TY1 = 0x0080,
            DMODE0 = 0x0100,
            DMODE1 = 0x0200,
            WMODE1 = 0x0400,
            OEDEF = 0x0800,
            TRANS = 0x1000,
            DFM0 = 0x2000,
            DFM1 = 0x4000,
            VSMODE = 0x8000,
        };
        enum bits_horizontal_porch
        {
            HBP0 = 0x0001,
            HBP1 = 0x0002,
            HBP2 = 0x0004,
            HBP3 = 0x0008,
            HBP4 = 0x0010,
            HBP5 = 0x0020,
            HBP6 = 0x0040,
            HBP7 = 0x0080,
            XL0 = 0x0100,
            XL1 = 0x0200,
            XL2 = 0x0400,
            XL3 = 0x0800,
            XL4 = 0x1000,
            XL5 = 0x2000,
            XL6 = 0x4000,
            XL7 = 0x8000,
        };
        enum bits_vertical_porch
        {
            VBP0 = 0x0001,
            VBP1 = 0x0002,
            VBP2 = 0x0004,
            VBP3 = 0x0008,
            VBP4 = 0x0010,
            VBP5 = 0x0020,
            VBP6 = 0x0040,
            VBP7 = 0x0080,
            VFP0 = 0x0100,
            VFP1 = 0x0200,
            VFP2 = 0x0400,
            VFP3 = 0x0800,
            VFP4 = 0x1000,
            VFP5 = 0x2000,
            VFP6 = 0x4000,
        };
        enum bits_pwr_ctrl_5
        {
            VCM0 = 0x0001,
            VCM1 = 0x0002,
            VCM2 = 0x0004,
            VCM3 = 0x0008,
            VCM4 = 0x0010,
            VCM5 = 0x0020,
            NOTP = 0x0040,
        };
        enum bits_ram_data_write_mask_1
        {
            WMG0 = 0x0004,
            WMG1 = 0x0008,
            WMG2 = 0x0010,
            WMG3 = 0x0020,
            WMG4 = 0x0040,
            WMG5 = 0x0080,
            WMR0 = 0x0400,
            WMR1 = 0x0800,
            WMR2 = 0x1000,
            WMR3 = 0x2000,
            WMR4 = 0x4000,
            WMR5 = 0x8000,
        };
        enum bits_ram_data_write_mask_2
        {
            WMB0 = 0x0004,
            WMB1 = 0x0008,
            WMB2 = 0x0010,
            WMB3 = 0x0020,
            WMB4 = 0x0040,
            WMB5 = 0x0080,
        };
        enum bits_gamma_ctrl_1
        {
            PKP00 = 0x0001,
            PKP01 = 0x0002,
            PKP02 = 0x0004,
            PKP10 = 0x0100,
            PKP11 = 0x0200,
            PKP12 = 0x0400,
        };
        enum bits_gamma_ctrl_2
        {
            PKP20 = 0x0001,
            PKP21 = 0x0002,
            PKP22 = 0x0004,
            PKP30 = 0x0100,
            PKP31 = 0x0200,
            PKP32 = 0x0400,
        };
        enum bits_gamma_ctrl_3
        {
            PKP40 = 0x0001,
            PKP41 = 0x0002,
            PKP42 = 0x0004,
            PKP50 = 0x0100,
            PKP51 = 0x0200,
            PKP52 = 0x0400,
        };
        enum bits_gamma_ctrl_4
        {
            PRP00 = 0x0001,
            PRP01 = 0x0002,
            PRP02 = 0x0004,
            PRP10 = 0x0100,
            PRP11 = 0x0200,
            PRP12 = 0x0400,
        };
        enum bits_gamma_ctrl_5
        {
            PKN00 = 0x0001,
            PKN01 = 0x0002,
            PKN02 = 0x0004,
            PKN10 = 0x0100,
            PKN11 = 0x0200,
            PKN12 = 0x0400,
        };
        enum bits_gamma_ctrl_6
        {
            PKN20 = 0x0001,
            PKN21 = 0x0002,
            PKN22 = 0x0004,
            PKN30 = 0x0100,
            PKN31 = 0x0200,
            PKN32 = 0x0400,
        };
        enum bits_gamma_ctrl_7
        {
            PKN40 = 0x0001,
            PKN41 = 0x0002,
            PKN42 = 0x0004,
            PKN50 = 0x0100,
            PKN51 = 0x0200,
            PKN52 = 0x0400,
        };
        enum bits_gamma_ctrl_8
        {
            PRN00 = 0x0001,
            PRN01 = 0x0002,
            PRN02 = 0x0004,
            PRN10 = 0x0100,
            PRN11 = 0x0200,
            PRN12 = 0x0400,
        };
        enum bits_gamma_ctrl_9
        {
            VRP00 = 0x0001,
            VRP01 = 0x0002,
            VRP02 = 0x0004,
            VRP03 = 0x0008,
            VRP10 = 0x0100,
            VRP11 = 0x0200,
            VRP12 = 0x0400,
            VRP13 = 0x0800,
            VRP14 = 0x1000,
        };
        enum bits_gamma_ctrl_10
        {
            VRN00 = 0x0001,
            VRN01 = 0x0002,
            VRN02 = 0x0004,
            VRN03 = 0x0008,
            VRN10 = 0x0100,
            VRN11 = 0x0200,
            VRN12 = 0x0400,
            VRN13 = 0x0800,
            VRN14 = 0x1000,
        };
        enum bits_vertical_scroll_ctrl_1
        {
            VL10 = 0x0001,
            VL11 = 0x0002,
            VL12 = 0x0004,
            VL13 = 0x0008,
            VL14 = 0x0010,
            VL15 = 0x0020,
            VL16 = 0x0040,
            VL17 = 0x0080,
            VL18 = 0x0100,
        };
        enum bits_vertical_scroll_ctrl_2
        {
            VL20 = 0x0001,
            VL21 = 0x0002,
            VL22 = 0x0004,
            VL23 = 0x0008,
            VL24 = 0x0010,
            VL25 = 0x0020,
            VL26 = 0x0040,
            VL27 = 0x0080,
            VL28 = 0x0100,
        };
        enum bits_horizontal_ram_addr_pos
        {
            HSA0 = 0x0001,
            HSA1 = 0x0002,
            HSA2 = 0x0004,
            HSA3 = 0x0008,
            HSA4 = 0x0010,
            HSA5 = 0x0020,
            HSA6 = 0x0040,
            HSA7 = 0x0080,
            HEA0 = 0x0100,
            HEA1 = 0x0200,
            HEA2 = 0x0400,
            HEA3 = 0x0800,
            HEA4 = 0x1000,
            HEA5 = 0x2000,
            HEA6 = 0x4000,
            HEA7 = 0x8000,
        };
        enum bits_vertical_ram_addr_start_pos
        {
            VSA0 = 0x0001,
            VSA1 = 0x0002,
            VSA2 = 0x0004,
            VSA3 = 0x0008,
            VSA4 = 0x0010,
            VSA5 = 0x0020,
            VSA6 = 0x0040,
            VSA7 = 0x0080,
            VSA8 = 0x0100,
        };
        enum bits_vertical_ram_addr_end_pos
        {
            VEA0 = 0x0001,
            VEA1 = 0x0002,
            VEA2 = 0x0004,
            VEA3 = 0x0008,
            VEA4 = 0x0010,
            VEA5 = 0x0020,
            VEA6 = 0x0040,
            VEA7 = 0x0080,
            VEA8 = 0x0100,
        };
        enum bits_first_window_start
        {
            SS10 = 0x0001,
            SS11 = 0x0002,
            SS12 = 0x0004,
            SS13 = 0x0008,
            SS14 = 0x0010,
            SS15 = 0x0020,
            SS16 = 0x0040,
            SS17 = 0x0080,
            SS18 = 0x0100,
        };
        enum bits_first_window_end
        {
            SE10 = 0x0001,
            SE11 = 0x0002,
            SE12 = 0x0004,
            SE13 = 0x0008,
            SE14 = 0x0010,
            SE15 = 0x0020,
            SE16 = 0x0040,
            SE17 = 0x0080,
            SE18 = 0x0100,
        };
        enum bits_second_window_start
        {
            SS10 = 0x0001,
            SS11 = 0x0002,
            SS12 = 0x0004,
            SS13 = 0x0008,
            SS14 = 0x0010,
            SS15 = 0x0020,
            SS16 = 0x0040,
            SS17 = 0x0080,
            SS18 = 0x0100,
        };
        enum bits_second_window_end
        {
            SE10 = 0x0001,
            SE11 = 0x0002,
            SE12 = 0x0004,
            SE13 = 0x0008,
            SE14 = 0x0010,
            SE15 = 0x0020,
            SE16 = 0x0040,
            SE17 = 0x0080,
            SE18 = 0x0100,
        };
        enum bits_set_gddram_x_addr_cnt
        {
            XAD0 = 0x0001,
            XAD1 = 0x0002,
            XAD2 = 0x0004,
            XAD3 = 0x0008,
            XAD4 = 0x0010,
            XAD5 = 0x0020,
            XAD6 = 0x0040,
            XAD7 = 0x0080,
        };
        enum bits_set_gddram_y_addr_cnt
        {
            YAD0 = 0x0001,
            YAD1 = 0x0002,
            YAD2 = 0x0004,
            YAD3 = 0x0008,
            YAD4 = 0x0010,
            YAD5 = 0x0020,
            YAD6 = 0x0040,
            YAD7 = 0x0080,
            YAD8 = 0x0100,
        };


        static const int height = 240;
        static const int height = 320;

        int _rs, _wr, _rd, _cs, _rst;

        lcd_pinouts_16bit_t data_pins; //data pins
        Gpio::OPi1GpioManager &gpio_manager;

        int last_cmd = -1;

        uint16_t read_data(void);
        uint16_t read_cmd(void);
        void write_data(uint16_t);
        void write_cmd(uint16_t);

    public:
        SSD1289(int rs, int rst, int wr, int rd, int cs,
                lcd_pinouts_16bit_t *p_data_pins);
        void init();
        void turn_on();
        void turn_off();
        void set_cursor_pos(int x, int y);
        void upload_pic(uint8_t red, uint8_t green, uint8_t blue);
    };
}
#endif /* __SSD1289_H__ */