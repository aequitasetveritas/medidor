#include "medidor.h"

/***** Declaración e inicialización de variables *****/

extern struct t_resultados_esp resultados_esp;
extern struct t_constantes_esp constantes_esp;
extern double energia_total;
unsigned int banderas_sistema;
struct strings_salida cadenas_resultados;



/***** Definición de funciones *****/

/**********************************************************************
 * void crear_cadenas (void){
 *
 * Crea las cadenas de caracteres listas para imprimir en el display
 * o para mandar a la memoria flash
 *********************************************************************/

void crear_cadenas (void){
	float auxiliarfloat, potencia;
	unsigned int auxiliarint;
	int flagI2oI1;

	if (resultados_esp.retESP430_STAT0 & I2GTI1FG){
		flagI2oI1 = 2;
	} else flagI2oI1 = 1;

	auxiliarfloat = ((float) resultados_esp.retACTENERGY1.l / POT_2_16);
	potencia = auxiliarfloat / constantes_esp.Cz;
	energia_total += potencia / 3600;				// Acumulo la energia en Wh (variable global)

	// Energia expresada en Wh
	if (energia_total < 1000){
		sprintf(cadenas_resultados.energia_activa,"E = %d.%02u Wh",
				(int) energia_total, (unsigned int) ((energia_total - (int) energia_total)*100 ));
	} else {		// Energia expresada en kWh
		sprintf(cadenas_resultados.energia_activa,"E = %d.%02u kWh",
						((int) energia_total)/1000, (unsigned int) ((energia_total - (int) energia_total)/10 ));
	}

	// Potencia activa expresada en kW
	sprintf(cadenas_resultados.potencia_activa,"P = %d.%02u kW",
						((int) potencia)/1000, (unsigned int) ((potencia - (int) potencia)/10));

	// Tensión de línea expresada en V
	sprintf(cadenas_resultados.vrms,"Vrms = %d V", (unsigned int) (resultados_esp.retV1RMS * constantes_esp.kV1));

	// Corriente del neutro (shunt) expresada en A
//	auxiliarint = (unsigned int) (((float) resultados_esp.retIRMS.w[1]) * constantes_esp.kI1);
//	sprintf(cadenas_resultados.irms,"I%drms = %u A", flagI2oI1, auxiliarint);

}
