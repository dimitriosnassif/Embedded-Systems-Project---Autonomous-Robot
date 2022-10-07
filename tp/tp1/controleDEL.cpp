/*
NOM: controle d`une DEL
Auteurs: Dimitrios Nassif, Gregory Lagrandcourt
Commentaire : nous avons determiner si 0x01 est rouge ou vert par essaie
*/


#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>


#define DDR_SORTIE 0xff
#define DDR_ENTREE 1000

const uint16_t DELAI = 1000;

void couleurAmbre()
{
    uint8_t compteur = 0;

    constexpr uint8_t DELAI_AMBRE = 3;

    while(compteur <= 200) 
    {
        compteur++;

        PORTA = 0x01;
        _delay_ms(DELAI_AMBRE);
        PORTA = 0x02;
        _delay_ms(DELAI_AMBRE);

    }
}


void clignoter() 
{
    DDRA = DDR_SORTIE;
    DDRA &= 0x03; //masque pour seulement rendre les ports A0 et A1 en sortie 

    for(;;) 
    {
        //couleur rouge
        PORTA = 0x01;
        _delay_ms(DELAI);
        //couleur vert
        PORTA = 0x02;
        _delay_ms(DELAI);

        //couleur ambre
        couleurAmbre();
    }
    
}

void clignoterBouttonPoussoir() 
{
    DDRA &= 0x03;

    DDRD = 0x00;

    for(;;)
    {
        if(PIND & 0x04)
        {
            _delay_ms(10);
            if(PIND &0x04)
            {
                PORTA = 0x01;
                _delay_ms(10);
                if(PIND & 0x04)
                {
                    PORTA = 0x02;
                    _delay_ms(10);
                }
            }
        }
    }
}

int main() 
{   
    clignoterBouttonPoussoir();
}
