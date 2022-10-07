/*
NOM: probleme 2
Auteurs: Dimitrios Nassif, Grégory Lagrandcourt
Objectif: Controle d'une roue avec différent rapport
*/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

const uint8_t DDR_IN = 0x00;
const uint8_t DDR_OUT = 0xff;


void setInsAndOuts() {
    DDRA = DDR_OUT;
    DDRA |= _BV(PA0) | _BV(PA1);
}

void wheelOn()
{
    PORTA = 0x01;
}

void wheelOff()
{
    PORTA = 0x00;
}

void rapportMs(int front)
{
    for(int i = 0; i < front; i++)
    {
        _delay_ms(1);
    }
}

void rapportUs(int front)
{
    for(int i = 0; i < front; i++)
    {
        _delay_us(1);
    }
}


void probleme60Hz(int a, int b)
{
    for(int i = 0; i <= 3; i++)
    {
        for(int j = 0; j < 250; j++) // règle le temps
        {
            wheelOn();          // Représente
            rapportMs(a);         //   la
            wheelOff();         //  période
            rapportMs(b-a);       // (b = 1/fréquence) en secondes
        }
        a += 4.25;
    }
}

void probleme400Hz(int a, int b)
{
    for(int i = 0; i <= 3; i++)
    {
        for(int j = 0; j < 400; j++) // règle le temps
        {
            wheelOn();          // Représente
            rapportUs(a);         //   la
            wheelOff();         //  période
            rapportUs(b-a);       // (b = 1/fréquence) en secondes
        }
        a += 625;
    }
}


int main()
{
    setInsAndOuts();

    for(;;)
    {
        probleme60Hz(0,17);
        probleme400Hz(1250,2500);
    }
    
}