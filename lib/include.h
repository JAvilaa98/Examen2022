
#ifndef LIB_INCLUDE_H_
#define LIB_INCLUDE_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define _40MHZ 9
#define _20MHZ 19
#define _10MHZ 39
#define _50MHZ 0x07
#define _25MHZ 0x0F
#define _80MHZ 0x04 
 
/*Variables agregadas*/
 // volatile uint16_t Result[6];

    /*float valor1;
    float valor2;
    float valor3;
    float valor4;
    float valor5;
    float valor6;*/

#include "TM4C123GH6PM.h"
#include "GPIO.h"
#include "PLL.h"
#include "UART.h"
#include "ADC.h"
#include "TIMER.h"


#endif /* INCLUDE_H_ */