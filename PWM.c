#include "lib/include.h"

/* Pag. 1672
  Tomando el módulo 0 del PWM1 Generador 0 ->  PF1
  Tomando el módulo 0 del PWM2 Generador 1 ->  PF2
  Tomando el módulo 0 del PWM4 Generador 2 ->  PG0*/

extern void Configura_Reg_PWM0(uint16_t freq)
{
    SYSCTL->RCGCPWM |= (1<<0); //Enable reloj del modulo PWM0 correspondiente al experimento 2
    SYSCTL->RCGCGPIO |= (1<<6) | (1<<5); //Habilitamos el GPIOG y GPIOF según lo requerido para el experimento 2
    
    GPIOG_AHB->AFSEL |= (1<<0); //Habilitamos la función alternativa pág 770 PG0 
    GPIOF_AHB->AFSEL |= (1<<1) | (1<<2); //Habilitamos la función alternativa pág 770 PF1 y PF2
  
    GPIOG_AHB->DIR = (1<<0);//Configura i/o PG0
    GPIOF_AHB->DIR = (1<<1) | (1<<2);//Configura i/o PF1 y PF2
    
    GPIOG_AHB->PCTL |= (GPIOG_AHB->PCTL&0xFFFFFFF0) | 0x00000006; //Combinado con la tabla de la pág 1808 y el registro PCTL decimos que es PWM pág 788 PG0
    GPIOF_AHB->PCTL |= (GPIOF_AHB->PCTL&0xFFFFF00F) | 0x00000660; //Combinado con la tabla de la pág 1808 y el registro PCTL decimos que es PWM pág 788 PF1 y PF2
    
    GPIOG_AHB->DEN |= (1<<0); //Para indicar si es digital o no PG0
    GPIOF_AHB->DEN |= (1<<1) | (1<<2); //Para indicar si es digital o no PF1 PF2
    
    PWM0->CC = (1<<8) | (0<<2) | (1<<1) | (0<<0);//Se Habilita el divisor porque salen 50 mil cuentas que no caben en los 16 bits del contador del PWM, 20 millinoes/ 50 = 400 mil cuentas
    
    PWM0->_0_CTL = (0<<0);//Desactivamos el gen 0 del PWM0 pag. 1708
    PWM0->_1_CTL = (0<<0);//Desactivamos el gen 1 del PWM0 pag. 1708
    PWM0->_2_CTL = (0<<0);//Desactivamos el gen 2 del PWM0 pag. 1708
  
   PWM0->_0_GENB |= (0X2<<2)|(0X3<<10)|(0x0<<0);//Establecemos el modo de trabajo de cuenta regresiva además de poner el PWMB en alto cuando el contador coincide con el comparador B 
   PWM0->_1_GENA |= (0X2<<2)|(0X3<<6)|(0x0<<0); //Establecemos el modo de trabajo de cuenta regresiva además de poner el PWMA en alto cuando el contador coincide con el comparador A 
   PWM0->_2_GENA |= (0X2<<2)|(0X3<<6)|(0x0<<0); //Establecemos el modo de trabajo de cuenta regresiva además de poner el PWMA en alto cuando el contador coincide con el comparador A 

    PWM0->_0_LOAD = 50000;// Cuentas = ((Frecuencia de reloj/8)/Frecuencia PWM) Cuentas = ((20000000/8)/50) = 50000
    PWM0->_1_LOAD = 50000;
    PWM0->_2_LOAD = 50000;
    
    PWM0->_0_CMPB = 5000;//Cuentas para 2 ms
    PWM0->_1_CMPA = 5000;           
    PWM0->_2_CMPA = 5000;

    //Habilitar generadores a usar
    PWM0->_0_CTL = (1<<0);
    PWM0->_1_CTL = (1<<0);
    PWM0->_2_CTL = (1<<0);
    
    PWM0->ENABLE = (1<<1) | (1<<2) | (1<<4);//Se habilita el PWM que se usa PWM1, PWM2 y PWM4 pag. 1247 y 1233     
}