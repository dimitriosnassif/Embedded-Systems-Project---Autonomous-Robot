
#include <avr/io.h>

class UART {
public:
    UART();
    ~UART();
    void initialisationUART(void);
    void transmissionUART(uint8_t donnee);
};