#include "fll.h"

/**********************************************************************
 * void init_FLL (int cl, long fsistema, unsigned int fcristal);
 *
 * Inicialización del FLL
 *
 * 		cl - capacidad de carga requerida por el cristal
 * 		fsistema - frecuencia del procesador (MCLK) en Hz
 * 		fcristal - frecuencia del cristal en Hz
 *********************************************************************/

void init_FLL (int cl, long fsistema, unsigned int fcristal){
	unsigned int cint, d, dco_div_bits;
	int nmas1;
	volatile int i, j;

	if (cl <= 3)						// 0pF < Cl =< 3pF?
		cint = XCAP0PF;
	else if (cl <= 7)					// 3pF < Cl =< 7pF?
		cint = XCAP10PF;
	else if (cl <= 9)					// 7pF < Cl =< 9pF?
		cint = XCAP14PF;
	else								// Cl > 9pF!
		cint = XCAP18PF;

	if ((fsistema/fcristal) < 121){
		d = 1;
		dco_div_bits= FLLD_1;			// fDCOCLK/1
	} else if ((fsistema/fcristal) < 240){
		d = 2;
		dco_div_bits= FLLD_2;			// fDCOCLK/2
	} else if ((fsistema/fcristal) < 480){
		d = 4;
		dco_div_bits= FLLD_4;			// fDCOCLK/4
	} else {
		d = 8;
		dco_div_bits= FLLD_8;			// fDCOCLK/8
	}

	nmas1 = (int) ((fsistema/fcristal)/d);

	if (fsistema < 3000)				// fsistema < 3MHz
		SCFI0 =    0 | dco_div_bits;
	else if (fsistema <  6000) 			// 3MHz <= fsistema <  6MHz
		SCFI0 = FN_2 | dco_div_bits;
	else if (fsistema <  9000) 			// 6MHz <= fsistema <  9MHz
		SCFI0 = FN_3 | dco_div_bits;
	else if (fsistema < 13000) 			// 9MHz <= fsistema < 13MHz
		SCFI0 = FN_4 | dco_div_bits;
	else
		SCFI0 = FN_8 | dco_div_bits;

	FLL_CTL0 = DCOPLUS | cint;
	SCFQCTL = nmas1 - 1;

	for (i= 32*d*nmas1; i > 0; i--)		// Tiempo para que el FLL+ se estabilice
		for (j= 8; j > 0; j--);

}

