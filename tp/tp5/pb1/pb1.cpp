#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "memoire_24.h"

const uint8_t WDELAY = 5;
const uint16_t address = 0x0000;

void redColor() {
    PORTA |= (1 << PA0);
    PORTA &= ~(1 << PA1);
}

void greenColor() {
    PORTA |= (1 << PA1);
    PORTA &= ~(1 << PA0);
}

void setInsAndOuts() {
    DDRA |= _BV(PA0) | _BV(PA1); // PORT connecter a la DEL
}

void memoryManip() {
    //write

    Memoire24CXXX memory;
    const uint8_t sizeOfData = 47;
    char wData[] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*\0";
    
    
    memory.ecriture(address, (uint8_t*)wData, sizeOfData);
    _delay_ms(WDELAY);
    

    //read
    char rData[sizeOfData];
    memory.lecture(address, (uint8_t*)rData, sizeOfData);

    //compare
    if(strcmp(wData,rData))
    {
        greenColor();
    }
    else{
        redColor();
    }
}

int main() {
    setInsAndOuts();
    memoryManip();
}
/*
-on commence a l'adresse 0x0000
-ecriture et lecture 
-comparaison de la donnee lu et celle ecrite 
-if (comparaison == true )
     return green;
 return red;
ecriture : prevoir un delai de 5ms entre chaque octet ecrit 
*/