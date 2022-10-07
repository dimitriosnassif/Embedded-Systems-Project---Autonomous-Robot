/*
NOM: probleme 1
Auteurs: Dimitrios Nassif, Grégory Lagrandcourt
Objectif: Eteindre une DEL progressivement (sur 3 secondes)
*/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

const uint8_t DDR_IN = 0x00;
const uint8_t DDR_OUT = 0xff;


void setInsAndOuts() {
    DDRA = DDR_OUT;
    DDRA |= _BV(PA0) | _BV(PA1);

    DDRD = DDR_IN;
}


void redColor(){
    PORTA = 0x01;
}

void turnOff(){
    PORTA = 0x00;
}


void delayFade(int time)
{
    for(int i = 0; i < time; i++)
    {
        _delay_us(100);
    }
}   

int a = 100;
int b = 100;

void probleme1()
{
    for (int i = 0; i < 3000; i++)
    {
        redColor();
        delayFade(a);
        turnOff();
        delayFade(b-a);
        a -= 0.01 ;
    }
}    



int main() 
{
    setInsAndOuts();
    probleme1();
}