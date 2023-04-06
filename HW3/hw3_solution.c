#include "nu32dip.h" // constants, functions for startup and UART
#include <string.h>
#include <stdio.h>
#include <math.h>

void blink(int, int); // blink the LEDs function

int main(void) {
    
    char buf[100];
  
    while(1){
        
        if (!PORTAbits.RA4){
            
            for (int i = 0; i < 100; i++){
                
                sprintf(buf, "%f\r\n", sin(2*3.1415*i/100));
                
                NU32DIP_WriteUART1(buf);
                
                _CP0_SET_COUNT(0);
                
                while(_CP0_GET_COUNT() < 240000){}
                
            }
            
        }
        
    }
    
}

// blink the LEDs
void blink(int iterations, int time_ms){
	int i;
	unsigned int t;
	for (i=0; i< iterations; i++){
		NU32DIP_GREEN = 0; // on
		NU32DIP_YELLOW = 1; // off
		t = _CP0_GET_COUNT(); // should really check for overflow here
		// the core timer ticks at half the SYSCLK, so 24000000 times per second
		// so each millisecond is 24000 ticks
		// wait half in each delay
		while(_CP0_GET_COUNT() < t + 12000*time_ms){}
		
		NU32DIP_GREEN = 1; // off
		NU32DIP_YELLOW = 0; // on
		t = _CP0_GET_COUNT(); // should really check for overflow here
		while(_CP0_GET_COUNT() < t + 12000*time_ms){}
	}
}