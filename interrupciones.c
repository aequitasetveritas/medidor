#include "interrupciones.h"

/**********************************************************************
 * ESP430 interrupt service routine
 *
 * Detecta el origen de la interrupción, si la medición está lista
 * actualiza las banderas de sistema para que el programa principal
 * tome las acciones correspondientes en el main
 *********************************************************************/

#pragma vector = ESP430_VECTOR
__interrupt void ESP430_isr (void){
	unsigned int msj_comando;
	unsigned int msj_dato;

	msj_comando = MBIN0;
	msj_dato = MBIN1;

	if (msj_comando == mEVENT){
		if ((msj_dato & ENRDYFG) != 0) banderas_sistema |= ENERGIA_LISTA;
	}

	LPM0_EXIT;
}

