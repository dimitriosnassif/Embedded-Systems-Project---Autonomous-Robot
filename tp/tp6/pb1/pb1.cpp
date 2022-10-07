/*
NOM: probleme 1
Auteurs: Dimitrios Nassif, Grégory Lagrandcourt
Objectif: Controler une DEL avec un boutton à l'extérieur de la carte mère
*/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "can.h"

const uint8_t DDR_IN = 0x00;
const uint8_t DDR_OUT = 0xff;
const uint8_t DEL_GREEN = 0x02;
const uint8_t DEL_OFF = 0x00;
const uint8_t DELAI_DEBOUNCE = 10;
const uint8_t MASQUE_D2 = 0x04;

void setInsAndOuts() {
    DDRB = DDR_OUT;
    DDRB |= _BV(PB0) | _BV(PB1);

    DDRD = DDR_IN;
}

void greenColor() {
    PORTB = DEL_GREEN;
}

void turnOff() {
    PORTB = DEL_OFF;
}

bool isPressed() {

    if(PIND & MASQUE_D2) {
        _delay_ms(DELAI_DEBOUNCE);  
        if(PIND & MASQUE_D2) {
            return true;
        }
    }
    return false;
}

enum class State { Del_green, Del_off };

volatile State current_state = State::Del_green;

void controleDel()
{
    switch (current_state)
    {
        case State::Del_green :
            greenColor();
            while (!isPressed()){
            }

        case State::Del_off :
            turnOff():
            while (isPressed()){
            }
    }
}


int main()
{
    setInsAndOuts();
    for(;;){
        controleDel();
    }

    return 0;
}