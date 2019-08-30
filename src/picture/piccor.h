#ifndef __PICCOR_H__
#define __PICCOR_H__

#include <cstdint>
#include "colors.h"

template (typename T)
class Piccor
{
    public:
        Piccor(colors_t<T> bits_resolution) : bresl(bits_resolution) {};
        colors_t<T> rought_correction(colors_t<T> &color, colors_t<T> &bits_resolution)
        {
            colors_t<T> ret = color;
            calc_correct(bits_resolution);
            ret.red /= factor.red;
            ret.blue /= factor.blue;
            ret.green /= factor.green;
        }
    private:
        colors_t<T> bresl;
        colors_t<T> last_bresl, factor;

        void calc_correct(colors_t<T> &bits_resolution) {
            if(last_bresl != bits_resolution)
            {
                last_bresl = bits_resolution;
                factor.blue = factor.green = factor.red = 1;
                if(bits_resolution.red > bresl.red)
                    factor.red = ((1 << (uint64_t)bits_resolution.red) - 1) / ((1 << (uint64_t)bresl.red) - 1);
                if(bits_resolution.green > bresl.green)
                    factor.green = ((1 << (uint64_t)bits_resolution.green) - 1) / ((1 << (uint64_t)bresl.green) - 1);
                if(bits_resolution.blue > bresl.blue)
                    factor.blue = ((1 << (uint64_t)bits_resolution.blue) - 1) / ((1 << (uint64_t)bresl.blue) - 1);
            }
        }
};


#endif /* PICCOR */