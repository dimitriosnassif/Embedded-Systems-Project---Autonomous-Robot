#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void setInsAndOuts() {
    DDRD = _BV(PD1) | _BV(PD0);
}

void initialisationUART(void) {
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

// Du USART vers le PC
void transmissionUART(uint8_t donnee) {
    //lorsque UDRE0 est 1, cela indique que le buffer est vide 
    //==> pret pour tramission (ecriture)
    while(!(UCSR0A & (_BV(UDRE0)))) {
    }
    UDR0 = donnee;
}

void verificationUART() {
    char mots[21] = "Le robot en INF1900\n";
    uint8_t i, j;
    for ( i = 0; i < 100; i++ ) {
        for ( j=0; j < 20; j++ ) {
            transmissionUART(mots[j]);
        }
    }
}

int main() {
    setInsAndOuts();
    initialisationUART();
    verificationUART();
}