#include "config.h"

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

    UART_Write_String("UART Initialized\r\n"); 

    while (1) 
    {
        char received_char = UART_Read(); 
        if (received_char != 0)
        {
             UART_Write_String("received :  ");
             UART_Write(received_char);
             UART_Write_String("\r\n"); 
        }
            
    }
}
