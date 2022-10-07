/*
NOM: pb1.cpp
Auteurs: Dimitrios Nassif, Gregory Lagrandcourt
Objectif : allumer une DEL en utilisant une machine a etats, 
en cliquant 3 fois sur le boutton poussoir nous avons une couleure 
verte pour 2 secondes

            TABLEAU D'ETATS PROBLEME 1
+---------------+-----------+-------------+----------+
| CURRENT STATE | ENTREE D2 | NEXT STATE  |  OUTPUT  |
+---------------+-----------+-------------+----------+
| NOT PRESSED   |         0 | NOT PRESSED | 00 (OFF) |
| NOT PRESSED   |         1 | OFF         | 00 (OFF) |
| OFF           |         0 | OFF         | 00 (OFF) |
| OFF           |         1 | OFF         | 00 (OFF) |
| OFF           |         0 | OFF         | 00 (OFF) |
| OFF           |         1 | GREEN       | 00 (OFF) |
| GREEN         |         0 | GREEN       | 10 (ON)  |
| GREEN         |         0 | NOT PRESSED | 10 (ON)  |
+---------------+-----------+-------------+----------+
*/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

const uint8_t DDR_OUT = 0xFF;
const uint8_t DDR_IN = 0x00;
const uint8_t DEL_OFF = 0x00;
const uint8_t DELAI_DEBOUNCE = 10;
const uint16_t DELAI_GREEN = 2000;
const uint8_t MASQUE_D2 = 0x04;

bool isButtonPressed() {
    if(PIND & MASQUE_D2) {
        _delay_ms(DELAI_DEBOUNCE);
        return PIND & MASQUE_D2;
    }
    return false;
}

void setInsAndOuts() {
    DDRA = DDR_OUT;
    DDRA |= _BV(PA0) | _BV(PA1);

    DDRD = DDR_IN;
}

void turnOff() {
    PORTA = DEL_OFF;
}

void turnGreen() {
    PORTA |= _BV(PA1);
    _delay_ms(DELAI_GREEN);
    turnOff();
}

void probleme1() {

    enum class State 
    {
        NotPressed,
        Off,
        Green 
    };
    
    State state = State::NotPressed;

    for(;;) {

            switch(state) 
            {
                case State::NotPressed:
                    while(!isButtonPressed()) {
                        state = State::NotPressed;
                    }
                    state = State::Off;
                    while(isButtonPressed()){
                    }
                case State::Off:
                    while(!isButtonPressed()) {
                        state = State::Off;
                    }
                    while(isButtonPressed()) {
                        state = State::Green;
                    }
                case State::Green:
                    while(!isButtonPressed()) {
                    }
                    while(isButtonPressed()) {
                    }
                    turnGreen();
                    state = State::NotPressed;
                    
                    break;
            }
    }
}

int main() {
    setInsAndOuts();
    probleme1();
}
