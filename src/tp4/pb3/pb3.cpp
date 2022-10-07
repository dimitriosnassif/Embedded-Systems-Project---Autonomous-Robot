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
const uint16_t BUTTONDELAI = 10000;


void ajustementPwm (uint8_t rapport) {

    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5
    // page 130 de la description technique du ATmega324PA)

    OCR1A = rapport;
    OCR1B = rapport;


    // division d'horloge par 8 - implique une fréquence de PWM fixe

    TCCR1A |= _BV(COM1A1) | _BV(COM1B1)| _BV(WGM10) ;
    TCCR1B |= _BV(CS11) ;
    TCCR1C = 0;
}

void initialisation ( void ) {
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontrôleur n'est pas prêt...
    cli ();
    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    //DDRA |= _BV(PA0) | _BV(PA1);
    DDRD |= 0xff;
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

int main()
{
    TCNT1 = 0;
    initialisation();
    ajustementPwm(255);
    _delay_ms(2000);
    ajustementPwm(192);
    _delay_ms(2000);
    ajustementPwm(128);
    _delay_ms(2000);
    ajustementPwm(64);
    _delay_ms(2000);
    ajustementPwm(0);
}