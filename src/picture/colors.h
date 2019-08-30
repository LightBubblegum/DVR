#ifndef __COLORS_H__
#define __COLORS_H__

#include <cstdint>

template <typename T>
struct colors_t
{
    T red, green, blue;
    bool operator == (const colors_t<T> & right)
    {
        return (this.red == right.red) && (this.green == right.green) && (this.blue == right.blue);
    }
    bool operator != (const colors_t<T> & right)
    {
        return !(this == right);
    }
};

class IResolution
{
    public:
        virtual ~IResolution() {};
        virtual colors_t<uint8_t> get_resolution() = 0;
};

#endif /* __COLORS_H__ */