#include "medidor.h"

/***** Declaración e inicialización de variables *****/

extern struct t_resultados_esp resultados_esp;
extern struct t_constantes_esp constantes_esp;
extern _iq15 energia_intermedia;
extern _iq10 energia_total;
unsigned int banderas_sistema;
struct strings_salida cadenas_resultados;



/***** Definición de funciones *****/

/**********************************************************************
 * void crear_cadenas (void)
 *
 * Crea las cadenas de caracteres listas para imprimir en el display
 * o para mandar a la memoria flash
 *********************************************************************/

void crear_cadenas (void){
	long auxiliarlong;
	_iq16 auxiliariq16, potenciaact;
	_iq10 auxiliariq10;
	char auxiliarstring[10];
	char flagI2oI1[2];

	if (resultados_esp.retESP430_STAT0 & I2GTI1FG)
		flagI2oI1[0] = 'L';
	else flagI2oI1[0] = 'N';
	flagI2oI1[1] = '\0';

	auxiliariq16 = _IQ16mpyI32(constantes_esp.kE_PF32, resultados_esp.retACTENERGY1.l);		// Paso a Ws
	energia_intermedia += _IQtoIQ15(auxiliariq16);									// Acumulo en Ws
	potenciaact = auxiliariq16;

	auxiliarlong = _IQ15int(energia_intermedia);			// Me quedo con la parte entera

	if (auxiliarlong >= 36000){						// energia_intermedia [Ws] supera los 0.01 kWh?
		energia_intermedia -= _IQ15(auxiliarlong);		// Vacío la parte entera de energia_intermedia
		auxiliariq10 = _IQ10(auxiliarlong);			// Convierto lo que va a ser acumulado a iq10
		auxiliariq10 = _IQ10div(auxiliariq10, _IQ10(3600));	// Lo paso a Wh
		auxiliariq10 = _IQ10div(auxiliariq10, _IQ10(1000));	// Y ahora a kWh
		energia_total += auxiliariq10;				// Y por último acumulo en energia_total
	}	// Si energia_intermedia no supera los 0.01 kWh no hay que acumular nada todavía en energia_total

	// String de energía activa acumulada expresada en kWh
	strcpy(cadenas_resultados.energia_activa, "E=");
	_IQ10toa(auxiliarstring, "%8.2f", energia_total);
	strcat(cadenas_resultados.energia_activa, auxiliarstring);
	strcat(cadenas_resultados.energia_activa, " kWh");

	// String de potencia activa expresada en W
	strcpy(cadenas_resultados.potencia_activa, "P = ");
	_IQ16toa(auxiliarstring, "%5.2f", potenciaact);
	strcat(cadenas_resultados.potencia_activa, auxiliarstring);
	strcat(cadenas_resultados.potencia_activa, " W");

	// String del factor de potencia
	strcpy(cadenas_resultados.factor_potencia, "FP = ");
	_Q14toa(auxiliarstring, "%1.4f", (_q14) resultados_esp.retPOWERFCT);
	strcat(cadenas_resultados.factor_potencia, auxiliarstring);
	if (resultados_esp.retREACTENERGY.l >= 0){
		strcat(cadenas_resultados.factor_potencia, " IND");
	} else {
		strcat(cadenas_resultados.factor_potencia, " CAP");
	}

	// String de frecuencia de línea expresada en Hz
	auxiliariq10 = _IQ10div(_IQ10mpy(_IQ10(4096), _IQ10(256)), _IQ10(resultados_esp.retMAINSPERIOD));
	strcpy(cadenas_resultados.frecuencia, "f = ");
	_IQ10toa(auxiliarstring, "%2.1f", auxiliariq10);
	strcat(cadenas_resultados.frecuencia, auxiliarstring);
	strcat(cadenas_resultados.frecuencia, " Hz");

	// String de tensión de línea expresada en V
	strcpy(cadenas_resultados.vrms, "Vrms = ");
	_IQ16toa(auxiliarstring, "%3.1f", _IQ16mpy(_IQ16(resultados_esp.retV1RMS), constantes_esp.kV1_PF32));
	strcat(cadenas_resultados.vrms, auxiliarstring);
	strcat(cadenas_resultados.vrms, " V");

	// String de tensión pico de línea expresada en V
	strcpy(cadenas_resultados.vpico, "Vp = ");
	_IQ16toa(auxiliarstring, "%3.1f", _IQ16mpy(_IQ16(resultados_esp.retVPEAK), constantes_esp.kV1_PF32));
	strcat(cadenas_resultados.vpico, auxiliarstring);
	strcat(cadenas_resultados.vpico, " V");

	// String de corriente del neutro (shunt) o vivo (sensor E.H.) expresada en A
	strcpy(cadenas_resultados.irms, "I");
	strcat(cadenas_resultados.irms, flagI2oI1);
	strcat(cadenas_resultados.irms, "rms = ");
	_IQ16toa(auxiliarstring, "%2.3f", _IQ16mpy(resultados_esp.retIRMS.l, constantes_esp.kI1_PF32));
	strcat(cadenas_resultados.irms, auxiliarstring);
	strcat(cadenas_resultados.irms, " A");

	// String de corriente pico del neutro (shunt) o vivo (sensor E.H.) expresada en A
	strcpy(cadenas_resultados.irms, "I");
	strcat(cadenas_resultados.irms, flagI2oI1);
	strcat(cadenas_resultados.irms, "p = ");
	_IQ16toa(auxiliarstring, "%2.3f", _IQ16mpy(_IQ16(resultados_esp.retIPEAK), constantes_esp.kI1_PF32));
	strcat(cadenas_resultados.irms, auxiliarstring);
	strcat(cadenas_resultados.irms, " A");
}





/**********************************************************************
 * void imprimirpantalla1 (void)
 *
 * Contiene el manejo del latch y del LCD para presentar en pantalla
 * energía activa y factor de potencia
 *********************************************************************/

void imprimirpantalla1 (void){
	unsigned int prelcd;		// Variable para guardar el estado del puerto 1 previo al uso del LCD

	P2OUT &= ~LATCH_EN;
	prelcd = P1OUT;
	limpiarpantalla_LCD();
	imprimirstring_LCD(cadenas_resultados.energia_activa);
	posicioncursor_LCD(1,0);
	imprimirstring_LCD(cadenas_resultados.factor_potencia);
	P1OUT = prelcd;
	P2OUT |= LATCH_EN;
}





/**********************************************************************
 * void imprimirpantalla2 (void)
 *
 * Contiene el manejo del latch y del LCD para presentar en pantalla
 * tensión de línea eficaz y frecuencia
 *********************************************************************/

void imprimirpantalla2 (void){
	unsigned int prelcd;		// Variable para guardar el estado del puerto 1 previo al uso del LCD

	P2OUT &= ~LATCH_EN;
	prelcd = P1OUT;
	limpiarpantalla_LCD();
	imprimirstring_LCD(cadenas_resultados.vrms);
	posicioncursor_LCD(1,0);
	imprimirstring_LCD(cadenas_resultados.frecuencia);
	P1OUT = prelcd;
	P2OUT |= LATCH_EN;
}





/**********************************************************************
 * void imprimirpantalla3 (void)
 *
 * Contiene el manejo del latch y del LCD para presentar en pantalla
 * corriente eficaz (la mayor entre vivo y neutro) y potencia
 * activa consumida actualmente
 *********************************************************************/

void imprimirpantalla3 (void){
	unsigned int prelcd;		// Variable para guardar el estado del puerto 1 previo al uso del LCD

	P2OUT &= ~LATCH_EN;
	prelcd = P1OUT;
	limpiarpantalla_LCD();
	imprimirstring_LCD(cadenas_resultados.potencia_activa);
	posicioncursor_LCD(1,0);
	imprimirstring_LCD(cadenas_resultados.irms);
	P1OUT = prelcd;
	P2OUT |= LATCH_EN;
}
