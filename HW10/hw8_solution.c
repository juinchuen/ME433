#include "font.h"
#include "i2c_master_noint.h"
#include "nu32dip.h"
#include "ssd1306.h"
#include "mpu6050.h"
#include <stdio.h>

int main () {
    
    NU32DIP_Startup();
    i2c_master_setup();
    ssd1306_setup();
    init_mpu6050();
    
    uint8_t data[IMU_ARRAY_LEN];
    char buf[100];
    
    int flag = 0;
    
    while (1){
        
        sprintf(buf, "%8d fps", 24000000/_CP0_GET_COUNT());
        
        _CP0_SET_COUNT(0);
        
        ssd1306_writeString(0,16,buf);
        
        burst_read_mpu6050(data);
        
        sprintf(buf, "%8.3f g", conv_zXL(data));
        
        ssd1306_writeString(0,0,buf);
        
        ssd1306_update();
        
        NU32DIP_YELLOW = (flag ++)%2;
        

        
    }
    
    ssd1306_clear();
    
}