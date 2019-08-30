/**
*/

#ifndef __EQUIPMENT_LCD_H__
#define __EQUIPMENT_LCD_H__

#include <cstdint>
#include "display.h"
#include "gpio_manip.h"

namespace LcdEq
{
  struct win_size_t
  {
    size_t x, y, w, h;
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
