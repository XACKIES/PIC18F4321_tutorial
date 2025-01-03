/*
 * File:   main.c
 * Author: Kittiphop Phanthachart
 *
 * Created on January 3, 2025, 2:40 PM
 */


#include "config.h"
#define _XTAL_FREQ 1000000
#define INTLED  PORTCbits.RC1     
#define SW PORTCbits.RC3
void __interrupt() toggle(void);

void main(void) {

    ADCON1 = 0x0f;
    
    RCONbits.IPEN = 1;          // Enable priority levels on interrupts
    
    TRISB = 0xff;               //-- set all PORT B as input 
    TRISD = 0x00;               //-- set all PORT D as output
    TRISC = 0xFD;               //-- set all PORT C as output   1111 1110

    INTCONbits.INT0IE = 1;
    INTCONbits.INT0IF = 0;      // INT0 is always High priority
    
    INTCON3bits.INT1IE = 1;
    INTCON3bits.INT1IF = 0; 
    INTCON3bits.INT1IP = 0;     // INT1  Low priority

    INTCONbits.GIEH = 1;        //  Enables all high priority interrupts
    INTCONbits.GIEL = 1;        //  Enables all low priority peripheral interrupts 
    
    INTCON2bits.INTEDG0 = 1;    // Interrupt on rising edge 
    INTCON2bits.INTEDG1 = 1;    // Interrupt on rising edge 
    
    
    
    while (1) {
        PORTD = 0x0F;
        __delay_ms(300);
        PORTD = 0x00;
        __delay_ms(300);
    }

    return;
}

void __interrupt(high_priority) toggle(void)
{
    if (INTCONbits.INT0IF && INTCONbits.INT0IE)
    {
        INTCONbits.INT0IF = 0;
        INTLED = ~INTLED;
    }
}

void __interrupt(low_priority) counting(void)
{
    
    if (INTCON3bits.INT1IF && INTCON3bits.INT1IE)
    {
        INTCON3bits.INT1IF = 0;
        INTLED = ~INTLED;
        for (uint8_t i = 0; i < 255; i++) 
          {
               if (SW == 0 ) break;
                PORTD = i;
                __delay_ms(10);
          }
    }
}