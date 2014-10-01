#ifndef PARAMETROS_H_
#define PARAMETROS_H_

#include <msp430.h>
#include "medidor.h"


/***** Defines de los parárametros para los registros *****/

#define defESP430_CTRL0 		/*I2CMRR | V1FILTER | NE1 | CURR_I2 | MB*/           V1FILTER | NE1 | CURR_I2 | MB
#define defEVENT			ENRDYFG
#define defPHASECORR1		0x0
#define defPHASECORR2 		0x0
#define defV1OFFSET 		0x0
#define defI1OFFSET 		0x0
#define defI2OFFSET 		0x0
#define defADAPTI1 			POT_2_14
#define defADAPTI2 			(defkI2 / defkI1 * POT_2_14)
#define defGAINCORR1 		0x0
#define defGAINCORR2 		0x0
#define defPOFFSET1_LO 		0x0
#define defPOFFSET1_HI 		0x0
#define defPOFFSET2_LO 		0x0
#define defPOFFSET2_HI 		0x0
#define defINTRPTLEVL_LO		0x8000
#define defINTRPTLEVL_HI		0x0000
#define defCALCYCLCNT 		50
#define defSTARTCURR_FRAC	(defSTARTCURR & 0xFFFF)
#define defSTARTCURR_INT		((defSTARTCURR & 0xFFFF0000) >> 16)
#define defNOMFREQ 			50
#define defVDROPCYCLS 		5
#define defRATIOTAMP 		(1.2 * POT_2_14)
#define defITAMP 			(1/defkI1)
#define defVDROPLEVEL 		(220 * RAIZ_2 * 0.8 / defkV1)
#define defVPEAKLEVEL 		(220 * RAIZ_2 * 1.1 / defkV1)
#define defIPEAKLEVEL 		(40 * RAIZ_2 /defkI1)
#define defDCREMPER 		0x0

#define defSTARTCURR 		(unsigned long) (0.1/defkI1 * POT_2_16)


/***** Defines de las constantes del medidor *****/

#define defkV1 	(float) 0.012213321
#define defkI1 	(float) 0.002147948
#define defkI2 	(float) 0.00217986
#define defkE 		(defkI1 * defkV1)
#define defCz		(1 / defkE)


#endif /* PARAMETROS_H_ */
