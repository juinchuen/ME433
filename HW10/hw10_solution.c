#include "ws2812b.h"
#include "nu32dip.h"
#include <math.h>

int main () {
    
    NU32DIP_Startup();
    
    ws2812b_setup();
    
    wsColor test [8];
    
    float hue = 0;
    
    for (int j = 0; j < 8; j++){
        
        test[j].r = 0;
        test[j].g = 0;
        test[j].b = 0;
        
    }
    
    while (1) {
    
        for (int i = 0; i < 7; i++) {

            test[i] = test[i + 1];

        }
        
        test[7] = HSBtoRGB(hue, 1.0, 1.0);
        
        hue = remainder(hue + 40, 360);
        
        ws2812b_setColor(test, 8);
        
        _CP0_SET_COUNT(0);
        
        while (_CP0_GET_COUNT() < 2400000){}
        
    }
    
}