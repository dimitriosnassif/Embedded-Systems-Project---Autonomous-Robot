#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t DEL_OFF = 0x00;
const uint8_t MASQUE_D2 = 0x04;
const uint16_t BUTTONDELAI = 10000;
const uint8_t DELAI_ON = 100;
const uint16_t DUREE = 7692;

volatile bool gMinuterieExpiree;
volatile bool gBoutonPoussoir;

void turnOff() {
    PORTA &= DEL_OFF;
}

void redColor() {
    PORTA |= (1 << PA0);
}

void greenColor() {
    PORTA |= (1 << PA1);
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

ISR (TIMER1_COMPA_vect) {
    gMinuterieExpiree = true;
}

ISR (INT0_vect) {
    _delay_ms(30);
    gBoutonPoussoir = false;
    if(PIND & MASQUE_D2) {
        gBoutonPoussoir = true;
    }
}

void partirMinuterie ( uint16_t duree ) {
    gMinuterieExpiree = false;
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    TCNT1 = 0;
    OCR1A = duree;
    TCCR1A |= _BV(COM1A1) ;
    TCCR1B |= (1<<CS12) | (1<<CS10);
    TCCR1C = 0;
    TIMSK1 |= _BV(OCIE1A) ;
}

void routinePrincipale() {
    do {
    // attendre qu'une des deux variables soit modifiée
    // par une ou l'autre des interruptions.
    } while ( gMinuterieExpiree == false && gBoutonPoussoir == false);

    // Une interruption s'est produite. Arrêter toute
    // forme d'interruption. Une seule réponse suffit.
    cli ();
    // Verifier la réponse
    if(gBoutonPoussoir) {
        greenColor();
    }
    else {
        redColor();
    }
    sei();
}

void fonction() {
    _delay_ms(BUTTONDELAI);
    redColor();
    _delay_ms(DELAI_ON);
    turnOff();
}

int main() {
    initialisation();
    fonction();
    partirMinuterie(DUREE);
    routinePrincipale();
}