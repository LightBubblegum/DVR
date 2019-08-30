/**
*/

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <array>

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

class IDispDriver
{
  public:
    virtual ~IDispDriver();
    virtual bool init() = 0;
    virtual void show() = 0;
    virtual std::size_t height() = 0;
    virtual std::size_t width() = 0;
};

class Display
{
  private:
    IDispDriver *monitor;

  public:
    Display(IDispDriver *);
};

#endif /* __DISPLAY_H__ */
