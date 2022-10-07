#define F_CPU 8000000UL

#include <avr/io.h>
#include "uart.h"

UART::UART() {
    initialisationUART();
}

UART::~UART() {

}

void UART::initialisationUART(void) {
    // 2400 bauds. Nous vous donnons la valeur des deux
    // premiers registres pour vous éviter des complications.
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // permettre la réception et la transmission par le UART0
    UCSR0A = 0;
    UCSR0B = _BV(RXEN0) | _BV(TXEN0); //Receiver and transmitter enabled
    // Format des trames: 8 bits, 1 stop bits, sans parité
    //par defaut USBS0 = 0 (pour 1 stop bit)
    //par defaut UPM01 et UPM00 = 0 (sans parite)
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}

void UART::transmissionUART(uint8_t donnee) {
    //lorsque UDRE0 est 1, cela indique que le buffer est vide 
    //==> pret pour tramission (ecriture)
    while(!(UCSR0A & (_BV(UDRE0)))) {
    }
    UDR0 = donnee;
}