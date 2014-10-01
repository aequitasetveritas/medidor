#include "esp430ce1a.h"

/***** Declaración e inicialización de variables *****/

#pragma DATA_SECTION(parametros_esp_flash,".infoA")
const struct t_parametros_esp parametros_esp_flash = {		// Estructuras para el guardado de los parámetros en la flash
	defESP430_CTRL0,
	defEVENT,
	defPHASECORR1,
	defPHASECORR2,
	defV1OFFSET,
	defI1OFFSET,
	defI2OFFSET,
	defADAPTI1,
	defADAPTI2,
	defGAINCORR1,
	defGAINCORR2,
	{defPOFFSET1_LO, defPOFFSET1_HI},
	{defPOFFSET2_LO, defPOFFSET2_HI},
	{defINTRPTLEVL_LO, defINTRPTLEVL_HI},
	defCALCYCLCNT,
	{defSTARTCURR_FRAC,	defSTARTCURR_INT},
	defNOMFREQ,
	defVDROPCYCLS,
	defRATIOTAMP,
	defITAMP,
	defVDROPLEVEL,
	defVPEAKLEVEL,
	defIPEAKLEVEL,
	defDCREMPER,
};

#pragma DATA_SECTION(constantes_esp_flash,".infoA")
const struct t_constantes_esp constantes_esp_flash = {
	defkV1,
	defkI1,
	defkI2,
	defkE,
	defCz,
};

struct t_parametros_esp parametros_esp;		// Estructuras para los parámetros en RAM
struct t_constantes_esp constantes_esp;
struct t_resultados_esp resultados_esp;

unsigned int version_firmware = 0;				// Guarda la versión del firmware del ESP430
unsigned int modo_ESP = modeIDLE;				// Modo de operación del ESP430
double energia_total;							// Contador de energía total





/***** Definición de funciones *****/

/**********************************************************************
 * void init_AFE (void)
 *
 * Inicialización del analog front end (módulo SD16),
 * previa a la inicialización del ESP430
 *********************************************************************/

void init_AFE (void){
	ESPCTL &= ~ESPEN;		// Deshabilito el ESP430 para configurar el SD16

	SD16CTL = SD16SSEL_1 | SD16DIV_3 | SD16REFON;		// SMCLK/8 (para poder entrar a los modos de bajo consumo)
	SD16INCTL0 = SD16INCH_0 | SD16GAIN_8;				// Conversor 0 -> I1 = shunt
	SD16INCTL1 = SD16INCH_0 | SD16GAIN_1;				// Conversor 1 -> I2 = sensor efecto Hall
	SD16INCTL2 = SD16INCH_0 | SD16GAIN_1;				// Conversor 2 -> V1 = línea
	SD16CCTL0 = SD16OSR_256;							// Oversampling ratio = 256, formato complemento a 2
	SD16CCTL1 = SD16OSR_256;
	SD16CCTL2 = SD16OSR_256;
}





/**********************************************************************
 * void init_ESP (unsigned char flashvar)
 *
 * Inicialización del módulo ESP430CE1A
 *
 * 		flashvar - 	indicador de si hay que pasar a RAM
 * 					parámetros guardados en la flash
 * 					de información
 *********************************************************************/

void init_ESP (unsigned char flashvar){
	ESPCTL |= ESPEN;		// Habilito el módulo
	MBCTL = 0;				// Control de las interrupciones del mailbox

	if ((ESP430_STAT0 & ACTIVEFG) != 0 ) {			// Está en modo ACTIVE
		MBOUT1 = modeRESET;
		MBOUT0 = mRESET;						// Reseteo
		while ((ESP430_STAT0 & ACTIVEFG) != 0);		// Espero a que pase de RESET a INIT y de INIT a IDLE
	}

	MBOUT0 = mSWVERSION;	// Pregunta la versión del firmware del ESP430

	while ((MBCTL & IN0IFG) == 0);
	while (MBIN0 != mSWRDY);		// Se queda esperando la respuesta en el mailbox

	version_firmware = MBIN1;

	init_parametros_ESP(flashvar);
	MBCTL = IN0IE;			// Habilita interrupciones por mensajes en el mailbox IN0
}





/**********************************************************************
 * void init_ESP_parametros (unsigned char flashvar)
 *
 * Carga de los parámetros del ESP430CE1A definidos
 * en el header parametros.h
 *
 * 		flashvar - 	indicador de si hay que pasar a RAM
 * 					parámetros guardados en la flash
 * 					de información
 *********************************************************************/

void init_parametros_ESP (unsigned char flashvar){
	if (flashvar) {
		parametros_esp = parametros_esp_flash;
		constantes_esp = constantes_esp_flash;
	}

	setear_parametro(mSET_CTRL0, parametros_esp.parESP430_CTRL0);
	setear_parametro(mSET_EVENT, parametros_esp.parEVENT);
//	setear_parametro(mSET_PHASECORR1, parametros_esp.parPHASECORR1);
//	setear_parametro(mSET_PHASECORR2, parametros_esp.parPHASECORR2);
//	setear_parametro(mSET_V1OFFSET, parametros_esp.parV1OFFSET);
//	setear_parametro(mSET_I1OFFSET, parametros_esp.parI1OFFSET);
//	setear_parametro(mSET_I2OFFSET, parametros_esp.parI2OFFSET);
	setear_parametro(mSET_ADAPTI1, parametros_esp.parADAPTI1);
	setear_parametro(mSET_ADAPTI2, parametros_esp.parADAPTI2);
//	setear_parametro(mSET_GAINCORR1, parametros_esp.parGAINCORR1);
//	setear_parametro(mSET_GAINCORR2, parametros_esp.parGAINCORR2);
//	setear_parametro(mSET_POFFSET1_LO, parametros_esp.parPOFFSET1.w[0]);
//	setear_parametro(mSET_POFFSET1_HI, parametros_esp.parPOFFSET1.w[1]);
//	setear_parametro(mSET_POFFSET2_LO, parametros_esp.parPOFFSET2.w[0]);
//	setear_parametro(mSET_POFFSET2_HI, parametros_esp.parPOFFSET2.w[1]);
	setear_parametro(mSET_INTRPTLEVL_LO, parametros_esp.parINTRPTLEVL.w[0]);
	setear_parametro(mSET_INTRPTLEVL_HI, parametros_esp.parINTRPTLEVL.w[1]);
	setear_parametro(mSET_CALCYCLCNT, parametros_esp.parCALCYCLCNT);
	setear_parametro(mSET_STARTCURR_FRAC, parametros_esp.parSTARTCURR.w[0]);
	setear_parametro(mSET_STARTCURR_INT, parametros_esp.parSTARTCURR.w[1]);
	setear_parametro(mSET_NOMFREQ, parametros_esp.parNOMFREQ);
	setear_parametro(mSET_VDROPCYCLS, parametros_esp.parVDROPCYCLS);
	setear_parametro(mSET_RATIOTAMP, parametros_esp.parRATIOTAMP);
	setear_parametro(mSET_ITAMP, parametros_esp.parITAMP);
	setear_parametro(mSET_VDROPLEVEL, parametros_esp.parVDROPLEVEL);
	setear_parametro(mSET_VPEAKLEVEL, parametros_esp.parVPEAKLEVEL);
	setear_parametro(mSET_IPEAKLEVEL, parametros_esp.parIPEAKLEVEL);
	setear_parametro(mSET_DCREMPER, parametros_esp.parDCREMPER);
}





/**********************************************************************
 * void setear_parametro (unsigned int parametro, unsigned int dato)
 *
 * Seteo del parámetro especificado y su valor
 *
 * 		parametro = Parámetro a ser seteado en su registro
 * 		dato = dato correspondiente a ese parámetro
 *********************************************************************/

void setear_parametro (unsigned int parametro, unsigned int dato){
	_DINT();

	MBOUT1 = dato;
	MBOUT0 = parametro;

	while ((MBCTL & IN0IFG) == 0);
	while ((MBIN0 != mPARAMSET) || (MBIN1 != parametro));

	_EINT();
}





/**********************************************************************
 * void obtener_resultados (void)
 *
 * Descarga todos los resultados de los registros retorno y los
 * guarda en una estructura global t_resultados_esp
 *********************************************************************/

void obtener_resultados (void){
	resultados_esp.retESP430_STAT0 = ESP430_STAT0;
	resultados_esp.retESP430_STAT1 = ESP430_STAT1;
	resultados_esp.retWAVEFSV1 = WAVEFSV1;
	resultados_esp.retWAVEFSI1 = WAVEFSI1;
	resultados_esp.retWAVEFSI2 = WAVEFSI2;
	resultados_esp.retACTENERGY1.w[0] = ACTENERGY1_LO;
	resultados_esp.retACTENERGY1.w[1] = ACTENERGY1_HI;
	resultados_esp.retACTENERGY2.w[0] = ACTENERGY2_LO;
	resultados_esp.retACTENERGY2.w[1] = ACTENERGY2_HI;
	resultados_esp.retREACTENERGY.w[0] = REACTENERGY_LO;
	resultados_esp.retREACTENERGY.w[1] = REACTENERGY_HI;
	resultados_esp.retAPPENERGY.w[0] = APPENERGY_LO;
	resultados_esp.retAPPENERGY.w[1] = APPENERGY_HI;
	resultados_esp.retACTENSPER1.w[0] = ACTENSPER1_LO;
	resultados_esp.retACTENSPER1.w[1] = ACTENSPER1_HI;
	resultados_esp.retACTENSPER2.w[0] = ACTENSPER2_LO;
	resultados_esp.retACTENSPER2.w[1] = ACTENSPER2_HI;
	resultados_esp.retPOWERFCT = POWERFCT;
//	resultados_esp.retCAPIND = CAPIND;		// No disponible para el MSP430FE427A
	resultados_esp.retMAINSPERIOD = MAINSPERIOD;
	resultados_esp.retV1RMS = V1RMS;
	resultados_esp.retIRMS.w[0] = IRMS_LO;
	resultados_esp.retIRMS.w[1] = IRMS_HI;
	resultados_esp.retVPEAK = VPEAK;
	resultados_esp.retIPEAK = IPEAK;
	resultados_esp.retLINECYCLCNT.w[0] = LINECYCLCNT_LO;
	resultados_esp.retLINECYCLCNT.w[1] = LINECYCLCNT_HI;
	resultados_esp.retNMBMEAS.w[0] = NMBMEAS_LO;
	resultados_esp.retNMBMEAS.w[1] = NMBMEAS_HI;
}





/**********************************************************************
 * unsigned int leer_parametro (unsigned int parametro)
 *
 * Lectura de un registro de retorno
 *
 * 		parametro = Parámetro a ser leido
 * 		devolución = Parámetro leído
 *********************************************************************/

unsigned int leer_parametro (unsigned int parametro){
	unsigned int temp;

	_DINT();

	MBOUT1 = parametro;
	MBOUT0 = mREAD_PARAM;

	while ((MBCTL & IN0IFG) == 0);
	while (MBIN0 != mPARAMRDY);
	temp = MBIN1;     	// Guardo en una variable temporal para evitar sobreescritura

	_EINT();
	return (temp);
}





/**********************************************************************
 * void comenzar_medicion (void)
 *
 * Inicio de la medición de energía (pasaje a modo MEASURE)
 *********************************************************************/

void comenzar_medicion (void){
  energia_total = 0;

  MBCTL = IN0IE;			// Habilita las interrupciones para el mailbox IN0 (donde llegan los "comandos" de retorno)

  MBOUT1 = modeMEASURE;
  MBOUT0 = mSET_MODE;
  modo_ESP = modeMEASURE;
  _EINT();
}





/**********************************************************************
 * void detener_medicion (void)
 *
 * Detención de la medición de energía (pasaje a modo IDLE)
 *********************************************************************/

void detener_medicion (void){
	_DINT();
	if ((ESP430_STAT0 & ACTIVEFG) != 0){		// Me aseguro que está activo antes de querer pasar a IDLE
		MBOUT1 = modeIDLE;
		MBOUT0 = mSET_MODE;
		while ((ESP430_STAT0 & ACTIVEFG) != 0) ;
	}
	modo_ESP = modeIDLE;
	_EINT();
}
