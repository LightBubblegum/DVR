/**
 * autor: Egor Plotkin
 */

#include <iostream>
#include <unistd.h>
#include "spfd54124b.h"

using namespace std;

#define RST_PIN     (21)
#define CS_PIN      (22)
#define MOSI_PIN    (12)
#define SCLK_PIN    (14)

int main(int argc, char *argv[])
{
    cout << "Programm working" << endl;

    LcdEq::NOKIA1616 n1616(RST_PIN, CS_PIN, MOSI_PIN, SCLK_PIN);
    n1616.init();

    while(1)
    {
        for(rgb_color16bit color = 0; color < 0xFFF0; color += 10)
        {
            usleep(10000);
            n1616.fill_background(color);
        }
    }

	return 0;
}
