#ifndef ESP430CE1A_H_
#define ESP430CE1A_H_

#include <msp430.h>
#include "parametros.h"

/***** Definición de tipos y constantes *****/

union t_u_long_word{
	unsigned int w[2];
	unsigned long l;
};

union t_s_long_word{
	unsigned int w[2];
	signed long l;
};

struct t_parametros_esp{
	int parESP430_CTRL0;
	int parEVENT;
	int parPHASECORR1;
	int parPHASECORR2;
	int parV1OFFSET;
	int parI1OFFSET;
	int parI2OFFSET;
	unsigned int parADAPTI1;
	unsigned int parADAPTI2;
	unsigned int parGAINCORR1;
	unsigned int parGAINCORR2;
	union t_s_long_word parPOFFSET1;
	union t_s_long_word parPOFFSET2;
	union t_u_long_word parINTRPTLEVL;
	unsigned int parCALCYCLCNT;
	union t_u_long_word parSTARTCURR;
	unsigned int parNOMFREQ;
	unsigned int parVDROPCYCLS;
	unsigned int parRATIOTAMP;
	unsigned int parITAMP;
	unsigned int parVDROPLEVEL;
	unsigned int parVPEAKLEVEL;
	unsigned int parIPEAKLEVEL;
	unsigned int parDCREMPER;
};

struct t_resultados_esp{
	unsigned int retESP430_STAT0;
	unsigned int retESP430_STAT1;
	int retWAVEFSV1;
	int retWAVEFSI1;
	int retWAVEFSI2;
	union t_s_long_word retACTENERGY1;
	union t_s_long_word retACTENERGY2;
	union t_s_long_word retREACTENERGY;
	union t_s_long_word retAPPENERGY;
	union t_s_long_word retACTENSPER1;
	union t_s_long_word retACTENSPER2;
	unsigned int retPOWERFCT;
//	int retCAPIND;			// No es usado en el MSP430FE427A, para hallar phi se usa POWERFCT y el signo de la energía reactiva
	unsigned int retMAINSPERIOD;
	unsigned int retV1RMS;
	union t_u_long_word retIRMS;
	unsigned int retVPEAK;
	unsigned int retIPEAK;
	union t_u_long_word retLINECYCLCNT;
	union t_u_long_word retNMBMEAS;
};

struct t_constantes_esp{
	float kV1;
	float kI1;
	float kI2;
	float kE;
	float Cz;
};



/***** Declaración de funciones *****/

void init_AFE (void);
void init_ESP (unsigned char flashvar);
void init_parametros_ESP (unsigned char flashvar);
void obtener_resultados (void);
void setear_parametro (unsigned int parametro, unsigned int dato);
unsigned int leer_parametro (unsigned int parametro);
void comenzar_medicion (void);
void detener_medicion (void);

#endif /* ESP430CE1A_H_ */
