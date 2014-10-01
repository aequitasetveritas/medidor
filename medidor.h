#ifndef MEDIDOR_H_
#define MEDIDOR_H_

#include <msp430.h>
#include <stdio.h>
#include <string.h>
#include "esp430ce1a.h"
#include "lcd_16x2.h"

/***** Defines del mapeo a los puertos y pines del MSP430 *****/

#define LATCH_EN	BIT0

/***** Definición de tipos y constantes *****/

#define POT_2_20 	0x00100000
#define POT_2_16 	0x00010000
#define POT_2_14 	0x00004000
#define RAIZ_2 	1.414213562
#define PI 		3.141592654

#define ENERGIA_LISTA	0x0001
#define DESCARGA_DATOS	0x0002

struct strings_salida{
	char energia_activa[17];
	char potencia_activa[17];
	char factor_potencia[17];
	char frecuencia[17];
	char vrms[17];
	char irms[17];
	char vpico[17];
	char ipico[17];
};



/***** Declaración de funciones *****/

void crear_cadenas (void);
void imprimirpantalla1(void);
void imprimirpantalla2(void);
void imprimirpantalla3(void);

#endif /* MEDIDOR_H_ */
