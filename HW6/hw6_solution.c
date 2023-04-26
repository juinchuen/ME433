#include "nu32dip.h"
#include "i2c_master_noint.h"

void write_olat(unsigned char byte){
    
    unsigned char send_buf;
    
    i2c_master_start();
    send_buf = 0b01000000;
    i2c_master_send(send_buf);
    send_buf = 0x0A;
    i2c_master_send(send_buf);
    i2c_master_send(byte);
    i2c_master_stop();
    
}

unsigned char read_gpio(){
    
    unsigned char send_buf;
    
    unsigned char recv_buf;
    
    i2c_master_start();
    send_buf = 0b01000000;
    i2c_master_send(send_buf);
    send_buf = 0x09;
    i2c_master_send(send_buf);
    i2c_master_restart();
    
    send_buf = 0b01000001;
    i2c_master_send(send_buf);
    recv_buf = i2c_master_recv();
    
    i2c_master_ack(1);
    
    i2c_master_stop();
    
    return recv_buf;
}

void blink_led(){
    
    for(int i = 0; i < 10; i++){
    
        write_olat(0xFF);

        _CP0_SET_COUNT(0);

        while (_CP0_GET_COUNT() < 12000000){};

        write_olat(0x00);
        
        _CP0_SET_COUNT(0);

        while (_CP0_GET_COUNT() < 12000000){};
    
    }
    
}

int main (){
    
    unsigned char send_buf = 0;
    
    NU32DIP_Startup();
    
    i2c_master_setup();
    
    //set all pins to output
    i2c_master_start();
    send_buf = 0b01000000;
    i2c_master_send(send_buf);
    send_buf = 0x00;
    i2c_master_send(send_buf);
    send_buf = 0b01111111;
    i2c_master_send(send_buf);
    i2c_master_stop();
    
    //blink_led();
    
    while(1){
        
        if (read_gpio() & 0x01){
            
            write_olat(0xFF);
            
        } else {
            
            blink_led();
            
        }
        
    }
     
}