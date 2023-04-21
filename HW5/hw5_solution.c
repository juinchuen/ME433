#include <stdio.h>
#include "nu32dip.h"
#include "spi.h"

void set_voltage(unsigned short vout){
    
    vout = vout & 0b0000001111111111;
    
    unsigned char buf1 = (unsigned char) 0b00110000 | vout >> 6;
    
    unsigned char buf2 = (unsigned char) (vout << 2);
    
    NU32DIP_GREEN = 0;
    
    spi_io(buf1);
    
    spi_io(buf2);
    
    NU32DIP_GREEN = 1;
    
}

int main (){
    
    _CP0_SET_COUNT(0);

    NU32DIP_Startup();
    
    initSPI();
    
    NU32DIP_GREEN = 1;
    
    while (_CP0_GET_COUNT() < 24000000){}
    
    unsigned short vout = 0;
    
    char uart_buf[100];
    
    while (1){
        
        for (int i = 0; i < 100; i++){
                    
            _CP0_SET_COUNT(0);
            
            set_voltage(vout);

            vout = (unsigned short)(1024.0 * 0.5 * (sin(2 * 3.1415 * i / 100.0) + 1));
            
            //sprintf(uart_buf, "%d\r\n", vout);
            
            //NU32DIP_WriteUART1(uart_buf);
            
            while(_CP0_GET_COUNT() < 120000){}
        
        }
        
    }
    
    
}