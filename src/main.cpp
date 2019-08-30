/**
 * autor: Egor Plotkin
 */

#include <iostream>
#include <unistd.h>
#include <string>
#include "spfd54124b.h"
#include "libbmp.h"

//================================================
using namespace std;

//================================================
#define RST_PIN     (21)
#define CS_PIN      (22)
#define MOSI_PIN    (23)
#define SCLK_PIN    (24)

//================================================
static uint8_t convert_to_color(uint8_t val, uint8_t bits);
//================================================
//const string path = "/home/egor/dropBox/linux.bmp";
//const string path = "/home/egor/dropBox/rosa.bmp";

BmpImg bmp;
LcdEq::NOKIA1616 n1616(RST_PIN, CS_PIN, MOSI_PIN, SCLK_PIN);
//================================================

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Provide path to bmp file" << endl;
        return 0;
    }

    cout << argv[0] << endl;
    cout << argv[1] << endl;

    cout << "Programm working" << endl;

    bmp.read(argv[1]); // load picture
    int bmp_width = bmp.get_width();
    int bmp_height = bmp.get_height();

    n1616.init(); // init display
    n1616.fill_background(0xFFFF);
    n1616.set_window(0, 0, bmp_width, bmp_height); //set window size based of loaded picture


    cout << "Picture size w[ " << bmp_width 
         << " ] and h[ " << bmp_height << " ]" << endl;

    bool background_set = false;
    for(int y = 0; y < bmp_height; ++y)
        for(int x = 0; x < bmp_width; ++x)
        {
            unsigned char red, green, blue;
            red = convert_to_color(bmp.red_at(x, y), 5);
            green = convert_to_color(bmp.green_at(x,y), 6);
            blue = convert_to_color(bmp.blue_at(x,y), 5);

            LcdEq::pixel_rgb_t rgb = {red, green, blue};
            n1616.send_pixel(rgb);
        }

    return 0;
}

static uint8_t convert_to_color(uint8_t val, uint8_t bits)
{
    const uint8_t div = UINT8_MAX / ((1 << bits) - 1);
    return val / div;    
}
//================================================
