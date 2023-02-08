#include "lib/include.h"


/*  Usando el modulo 0 y 1 , configurar la tarjeta a la frecuencia asignada, para adquirir 6 señales analógicas 
    a una velocidad de 1 millón de muestras por segundo, por los canales asignados  y guardar los valores en un 
    arreglo para ser enviados con un botones  externos asociado al gpio A a través del protocolo de comunicación 
    asíncrona a una velocidad todo esto usando interrupciones.
     c) 3,5,7,4,2,8 20 MHZ 9600  */


//Función para convertir los números del ADC en tipo char y mandarlos por UART
    extern void integer_to_char(uint16_t number) 
    {
        char number_in_string[5];
        int i = 3;
        int j = 0; 
        int n_digit;  
        while (i >= 0)
        {
            n_digit = (int)number / (int)(pow(10, i));
            number_in_string[j] = n_digit + '0';
            number = number - (n_digit * pow(10, i)); 
            i = i - 1; 
            j++;
        }
        number_in_string[4] = '\n';
        printString(number_in_string);
    }

int main(void)
{

    // Declaración de variables 
    volatile uint16_t Result[6];

    /*Para enviar los valores del ADC en carácteres, 
     es char para mandarlo por UART*/
    uint16_t valor1;
    

    Configurar_PLL(_20MHZ);  //Configuracion de velocidad de reloj
    Configura_Reg_ADC0();
    Configurar_UART0();
    Configurar_GPIO();
    // Configurar_Timer0A();

    while(1)
    {   
        //Manda llamar a la función de conversión
        ADC0_InSeq1(Result);  
        //ADC1_InSeq2(Result);
        //ADC1_InSeq3(Result);


        //Se convierte result(numerico) en valor(caracteres) con una base de 10 (en binario)
        valor1 = (uint16_t)(Result[0]);
        integer_to_char(valor1);      

    }
}
