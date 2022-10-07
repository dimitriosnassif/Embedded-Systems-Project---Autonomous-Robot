#define F_CPU 8000000UL

#include <util/delay.h>
#include "uart.h"
#include "memoire_24.h"

const uint8_t WDELAY = 5;
const uint16_t ADDRESS = 0x0000;

void setInsAndOuts() {
    DDRD |= _BV(PD1) | _BV(PD0);
}

void memoryToPC() {
    //write in memory
    Memoire24CXXX memory;
    const uint8_t sizeOfData = 47;
    char wData[] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*\0";
    memory.ecriture(ADDRESS, (uint8_t*)wData, sizeOfData);
    _delay_ms(WDELAY);

    //transmit using usart
    UART uart;
    uint16_t address = ADDRESS;
    uint8_t rData;
    while(address != 0xFF) {
        memory.lecture(address, &rData);
        uart.transmissionUART(rData);
        address++;
    }
}

int main() {
    setInsAndOuts();
    memoryToPC();
    return 0;
}
