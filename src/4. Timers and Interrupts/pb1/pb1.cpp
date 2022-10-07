#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t DDR_IN = 0x00;
const uint8_t DDR_OUT = 0xFF;
const uint8_t DELAI_AMBRE = 2;
const uint8_t DELAI_DEBOUNCE = 10;
const uint8_t DEL_OFF = 0x00;
const uint8_t DEL_RED = 0x01;
const uint8_t DEL_GREEN = 0x02;
const uint8_t MASQUE_D2 = 0x04;
const uint8_t COUNTER_MAX = 50;

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

volatile State current_state = State::Initial_Red;

void controleDel() {

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

// placer le bon type de signal d'interruption
// à prendre en charge en argument
ISR ( INT0_vect ) {
    // laisser un délai avant de confirmer la réponse du
    // bouton-poussoir: environ 30 ms (anti-rebond)
    _delay_ms ( 30 );
    // se souvenir ici si le bouton est pressé ou relâché
    isPressed();
    // changements d'état tels que ceux de la
    // semaine précédente
    controleDel();
    // Voir la note plus bas pour comprendre cette instruction et son rôle
    EIFR |= (1 << INTF0) ;
}

void initialisation ( void ) {
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontrôleur n'est pas prêt...
    cli ();
    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    DDRA |= _BV(PA0) | _BV(PA1);
    DDRD |= (0 << PA2);
    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0);
    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= (1 << ISC00);
    // sei permet de recevoir à nouveau des interruptions.
    sei ();
}

int main() {
    while(true) {
        initialisation();
    }
}