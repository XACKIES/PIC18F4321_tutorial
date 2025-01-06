#include "config.h"
#include <stdio.h>  


#define _XTAL_FREQ 8000000  

void UART_Init(unsigned long baud_rate) 
{
    SPBRG = 12;  //for baud rate 9600 bps     
    TXSTAbits.BRGH = 0;     

    TRISCbits.TRISC6 = 0;  
    TRISCbits.TRISC7 = 1;   

    RCSTAbits.SPEN = 1;     
    TXSTAbits.TXEN = 1;     
    RCSTAbits.CREN = 1;     
}


void UART_Write(char data) 
{
    while (!TXSTAbits.TRMT); 
    TXREG = data;          
}

void UART_Write_String(const char *text) 
{
    while (*text) {
        UART_Write(*text++);
    }
}
void UART_Write_Int(int value) {
    char buffer[20];              
    sprintf(buffer, "%d", value); 
    UART_Write_String(buffer);   
}



char UART_Read() 
{
    while (!PIR1bits.RCIF);  
    return RCREG;           
}

// Main Function
void main() 
{
    OSCCONbits.IRCF = 0b111; 
    UART_Init(9600); 
    __delay_ms(1000);
    UART_Write_String("UART Initialized\r\n"); 

    
    
    ADCON1 = 0x06;
    
    TRISBbits.RB2 = 1;
    
    ADCON2bits.ADCS = 0;
    ADCON2bits.ACQT = 1;
    ADCON2bits.ADFM = 1;
    
    ADCON0bits.CHS  = 0b1000;
    
    ADCON0bits.ADON =1;
    
    while (1) 
    {
//        ADCON0bits.GO = 1 ;
//        while( ADCON0bits.GO_NOT_DONE );
//        int num;
//        num = ADRESH << 8 | ADRESL ;
//        
//        UART_Write_Int(num );

        
        
//--  Moving average filter at 100 sampling
        unsigned long sum = 0;
        for (unsigned int i = 0; i < 100; i++) 
        {
            ADCON0bits.GO = 1;
            while (ADCON0bits.GO_NOT_DONE);
            int num;
            num = ADRESH << 8 | ADRESL;
            sum += num;

        }
        UART_Write_Int(sum / 100);
        
        
        UART_Write_String("\r\n"); 
        __delay_ms(10);
        
            
    }
}
