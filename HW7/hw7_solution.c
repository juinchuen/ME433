#include <stdio.h>
#include "i2c_master_noint.h"
#include "nu32dip.h"
#include "mpu6050.h"

void write_register(unsigned char addr, unsigned char val){
    
    unsigned send_buf = 0;
    
    i2c_master_start();
    
    send_buf = 0b11010000;
    i2c_master_send(send_buf);
    
    i2c_master_send(addr);
    
    i2c_master_send(val);
    
    i2c_master_stop();
    
}

unsigned char verify_whoami(){
    
    unsigned char recv_buf;
    unsigned char send_buf;
    
    i2c_master_start();
    send_buf = 0b11010000;
    i2c_master_send(send_buf);
    
    send_buf = 0x75;
    i2c_master_send(send_buf);
    
    i2c_master_restart();
    
    send_buf = 0b11010001;
    i2c_master_send(send_buf);
    
    recv_buf = i2c_master_recv();
    
    i2c_master_ack(1);
    
    i2c_master_stop();
    
    return recv_buf;
    
}

void blink_led(){
    
    for(int i = 0; i < 10; i++){
    
        NU32DIP_GREEN = 1;

        _CP0_SET_COUNT(0);

        while (_CP0_GET_COUNT() < 12000000){};

        NU32DIP_GREEN = 0;
        
        _CP0_SET_COUNT(0);

        while (_CP0_GET_COUNT() < 12000000){};
    
    }
    
}

int main (){
    
    unsigned char send_buf = 0;
    
    char buf[100];
    
    NU32DIP_Startup();
    
    i2c_master_setup();
    
    if (verify_whoami() != 0x68){
        
        blink_led();
        
        return 1;
        
    }
    
    uint8_t data[IMU_ARRAY_LEN];
    
    init_mpu6050();
    
    while(1){
        
        _CP0_SET_COUNT(0);
    
        burst_read_mpu6050(data);

        /*
        sprintf(buf, "Accel_X = %7.3f Accel_Y = %7.3f Accel_Z = %7.3f\r\n",
                conv_xXL(data),
                conv_yXL(data),
                conv_zXL(data));

        NU32DIP_WriteUART1(buf);
        
        sprintf(buf, "Gyro_X = %7.3f Gyro_Y = %7.3f Gyro_Z = %7.3f\r\n",
                conv_xG(data),
                conv_yG(data),
                conv_zG(data));

        NU32DIP_WriteUART1(buf);
        
        sprintf(buf, "Temp = %7.3f\r\n", conv_temp(data));
        
        NU32DIP_WriteUART1(buf);
         * 
         */
        
        sprintf(buf, "%f\r\n", conv_zXL(data));
        
        NU32DIP_WriteUART1(buf);
        
        while(_CP0_GET_COUNT() < 240000){}
    
    }
    
    return 0;

}