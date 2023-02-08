#include "lib/include.h"

//Configuración de UART1 que corresponde al PB1 -> Tx y PB0 -> Rx  pag. 895

extern void Configurar_UART0(void)
{
    SYSCTL->RCGCUART  = (1<<1);   //Habilitamos UART1 pág 344
    SYSCTL->RCGCGPIO |= (1<<1);     //Habilitamos el puerto del GPIO pág 340
    GPIOB->AFSEL |= (1<<0) | (1<<1); //Habilitamos la función alternativa de los puertos pag 671
    GPIOB->DIR |= (1<<0) | (0<<1); //Habilitamos la dirección
    //GPIO Port Control (GPIOPCTL) PA0-> U0Rx PA1-> U0Tx pag.688
    GPIOB->PCTL |= (GPIOB->PCTL&0xFFFFFF00) | 0x00000011;// 
    GPIOB->DEN |= (1<<0) | (1<<1);// Habilitamos canales digitales
    //UART0 UART Control (UARTCTL) pag.918 DISABLE!!
    UART1->CTL |= (0<<9) | (0<<8) | (0<<0);


    // UART Integer Baud-Rate Divisor (UARTIBRD) pag.914
    /*
    BRD = 20,000,000 / (16*57600) = 21.7013
    UARTFBRD[DIVFRAC] = integer(.7013 * 64 + 0.5) = 45.3832
    */
    UART1->IBRD = 21;
    // UART Fractional Baud-Rate Divisor (UARTFBRD) pag.915
    UART1->FBRD = 46;
    //  UART Line Control (UARTLCRH) pag.916
    UART1->LCRH = (0x3<<5)|(1<<4);
    //  UART Clock Configuration(UARTCC) pag.939
    UART1->CC =(0<<0);
    //Disable UART0 UART Control (UARTCTL) pag.918
    UART1->CTL = (1<<0) | (1<<8) | (1<<9);

}

//Para recibir datos
extern char readChar(void)
{
    //UART FR flag pag 911
    //UART DR data 906
    int v;
    char c;
    while((UART0->FR & (1<<4)) != 0 );
    v = UART0->DR & 0xFF;
    c = v;
    return c;
}

//Para enviar dato/caracter
extern void printChar(char c)
{
    while((UART0->FR & (1<<5)) != 0 );
    UART0->DR = c;
}

//Enviar datos en cadena
extern void printString(char* string)
{
    while(*string)
    {
        printChar(*(string++));
    }
    printChar('\n');
}

//Recibir cadena 
extern char * readString(char delimitador)
{

   int i=0;
   char *string = (char *)calloc(10,sizeof(char));
   char c = readChar();
   while(c != delimitador)
   {
       *(string+i) = c;
       i++;
       if(i%10==0)
       {
           string = realloc(string,(i+10)*sizeof(char));
       }
       c = readChar();
   }

   return string;
}




