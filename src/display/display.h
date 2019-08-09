/**
*/

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

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