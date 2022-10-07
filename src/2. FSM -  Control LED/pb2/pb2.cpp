/*
NOM: pb2.cpp
Auteurs: Dimitrios Nassif, Grégory Lagrandcourt
Objectif: Modifier la couleur de la LED à l'aide d'une machine à état
entre 4 différents états.

                TABLEAU D'ETATS PROBLEME 2
+---------------+-----------+---------------+---------------+
| CURRENT STATE | ENTREE D2 |  NEXT STATE   | OUTPUT (A1A0) |
+---------------+-----------+---------------+---------------+
| ROUGE INITIAL |         0 | ROUGE INITIAL | 01            |
| ROUGE INITIAL |         1 | AMBRE         | XX            |
| AMBRE         |         1 | AMBRE         | XX            |
| AMBRE         |         0 | VERT          | 10            |
| VERT          |         0 | VERT          | 10            |
| VERT          |         1 | ROUGE         | 01            |
| ROUGE         |         1 | ROUGE         | 01            |
| ROUGE         |         0 | ETEINT        | 00            |
| ETEINT        |         0 | ETEINT        | 00            |
| ETEINT        |         1 | VERT          | 10            |
+---------------+-----------+---------------+---------------+
*/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

const uint8_t DDR_IN = 0x00;
const uint8_t DDR_OUT = 0xFF;
const uint8_t DELAI_AMBRE = 2;
const uint8_t DELAI_DEBOUNCE = 10;
const uint8_t DEL_OFF = 0x00;
const uint8_t DEL_RED = 0x01;
const uint8_t DEL_GREEN = 0x02;
const uint8_t MASQUE_D2 = 0x04;
const uint8_t COUNTER_MAX = 50;

void setInsAndOuts() {
    DDRA = DDR_OUT;
    DDRA |= _BV(PA0) | _BV(PA1);

    DDRD = DDR_IN;
}

void turnOff() {
    PORTA = DEL_OFF;
}

void redColor() {
    PORTA = DEL_RED;
}

void greenColor() {
    PORTA = DEL_GREEN;
}

void amberColor() {

    uint8_t counter = 0;

    while(counter <= COUNTER_MAX) {

        counter++;

        redColor();
        _delay_ms(DELAI_AMBRE);
        greenColor();
        _delay_ms(DELAI_AMBRE);
    }
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

enum class State { Initial_Red, Amber, First_green, Red, Off, Second_green };

void probleme2() {

    State current_state = State::Initial_Red;

    for(;;) {
        switch(current_state)
        {
            case State::Initial_Red :
                while(!isPressed()) {
                    redColor();
                }

            case State::Amber :
                while(isPressed()) {
                    amberColor();
                }
            
            case State::First_green :
                while(!isPressed()) {
                    greenColor();
                }
            
            case State::Red :
                while(isPressed()) {
                    redColor();
                }
            
            case State::Off :
                while(!isPressed()) {
                    turnOff();
                }
            
            case State::Second_green :
                while(isPressed()) {
                    greenColor();
                }
            
        }
    }
}


int main() {
    setInsAndOuts();
    probleme2();
}
