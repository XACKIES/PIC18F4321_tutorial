/*
 * File:   main.c
 * Author: Kittiphop Phanthachart
 * Created on January 3, 2025, 12:52 AM
 */


#include "config.h"
#define SW PORTCbits.RC3
#define _XTAL_FREQ 1000000

uint8_t reverseBits(uint8_t value) {
    uint8_t result = 0;
    for (int i = 0; i < 8; i++) 
    {
        result |= ((value >> i) & 1) << (7 - i);
    }
    return result;
}

void main(void) 
{
   
    ADCON1 = 0x0F;
    TRISD =0x00;  //-- set all PORT D as output 
    TRISC =0xff;  //-- set all PORT C as input 
    PORTD = 0x00;
    while (1)
    {
        
  
        if (SW == 1) 
        {
            for (uint8_t i = 0; i < 256; i++) 
            {
                if (SW == 0 ) break;
                PORTD = reverseBits(i);
                __delay_ms(10);
            }
        }
        else if (SW == 0) 
        {
             for (uint8_t i = 0; i < 256; i++) 
            {
                 if (SW == 1 ) break;
                  PORTD = i;
                  __delay_ms(10);
            }
        }
        
        
    }
    
    return;
}
