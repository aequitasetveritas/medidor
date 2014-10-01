#include <msp430.h>
//#include <stdio.h>
#include "IQmathLib.h"
#include "QmathLib.h"
#include "fll.h"
#include "lcd_16x2.h"
#include "esp430ce1a.h"
#include "interrupciones.h"
#include "medidor.h"
#include "parametros.h"


extern unsigned int version_firmware;
extern struct t_parametros_esp parametros_esp;
extern struct t_constantes_esp constantes_esp;
extern struct t_resultados_esp resultados_esp;
extern struct strings_salida cadenas_resultados;

char buff[17];

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer

	init_FLL(10, 8388608, 32768);
	init_LCD();
	init_AFE();
	init_ESP(1);
	
	P2DIR |= LATCH_EN;
	P2OUT |= LATCH_EN;
	P1OUT |= BIT3;
	P2OUT &= ~LATCH_EN;

	limpiarpantalla_LCD();
	_IQ16toa(buff, "%3.1f", _IQ16(version_firmware));
	imprimirstring_LCD("Firmware ESP430:");
	posicioncursor_LCD(1,0);
	imprimirstring_LCD(buff);
	__delay_cycles(10000000);
	comenzar_medicion();

	P2OUT |= BIT0;

	while(1){
		LPM0;

		if ((banderas_sistema & ENERGIA_LISTA) != 0){
			banderas_sistema &= ~ENERGIA_LISTA;
			obtener_resultados();
			crear_cadenas();
			P1OUT ^= BIT3;

			imprimirpantalla1();
			imprimirpantalla2();
			imprimirpantalla3();

			/********** MOSTRAR ALGUN RESULTADO ********/

		}
	}

	return 0;
}
