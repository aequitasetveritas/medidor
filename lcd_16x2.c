#include "lcd_16x2.h"

/**********************************************************************
 * void pulso_LCD (void)
 *
 * Esta función debe ser llamada cada vez que se
 * necesita informarle al LCD que escanee el bus de datos
 *********************************************************************/

void pulso_LCD (){				// 2000 ciclos de delay > 200 us
	LCD_OUT &= ~LCD_EN;		// EN pasa a 0
	__delay_cycles(2000);

	LCD_OUT |= LCD_EN;		// EN sube a 1
    __delay_cycles(2000);

    LCD_OUT &= ~LCD_EN;		// EN vuelve a 0
    __delay_cycles(2000);
}



/**********************************************************************
 * void init_LCD (void)
 *
 * Inicialización del LCD.
 *
 * NOTA:	Esta función no debe ser llamada 2 veces en el
 * módulo del display (caso de alimentación por separado
 * de uC y LCD)
 *********************************************************************/

void init_LCD (){
	LCD_DIR |= LCD_PIN_MASK;		// Seteo de los pines usados en el MSP430 y puesta a 0
	LCD_OUT &= ~LCD_PIN_MASK;
	
	__delay_cycles(1000000);		// Tiempo de espera para el encendido del LCD = 120 ms para f=8.388 MHz
	
	LCD_OUT |= LCD_D5;			// Puesto en modo de 4 bits
	pulso_LCD();

    enviarbyte_LCD(0x28, FALSE);	// Segunda parte del byte de inicialización en modo 4 bits, 2 lineas y formato 5x7 puntos
    __delay_cycles(10000);			// >1 ms de espera (f=8.388 MHz)

	enviarbyte_LCD(0x0E, FALSE);	// Encender cursor
	__delay_cycles(10000);			// >1 ms de espera (f=8.388 MHz)
	
	enviarbyte_LCD(0x01, FALSE);	// Limpia la pantalla
	__delay_cycles(100000);			// >10 ms de espera (f=8.388 MHz)
	
	enviarbyte_LCD(0x06, FALSE);	// Modo de incremento de dirección
}



/**********************************************************************
 * void enviarbyte_LCD (char byteaenviar, int esdato)
 *
 * Envía un byte por el bus de datos en el modo de 4 bits.
 * Esto requiere enviar el dato en dos paquetes, primero el
 * nibble MS y luego el LSN.
 *
 * 		byteaenviar - el byte a enviar
 *
 * 		esdato - 	TRUE si el byte es un caracter de datos
 * 					FALSE si es un comando
 *********************************************************************/

void enviarbyte_LCD (char byteaenviar, int esdato){
    LCD_OUT &= ~LCD_PIN_MASK;				// Borra todos los pines
	LCD_OUT |= ((byteaenviar & 0xF0) >> 4);	// Setea el MSN en el puerto de salida
 
    if (esdato == TRUE){
		LCD_OUT |= LCD_RS;
	}

	pulso_LCD();	// Habilita la lectura del dato enviado

	LCD_OUT &= ~LCD_PIN_MASK;
    LCD_OUT |= (byteaenviar & 0x0F);		// Setea el LSN en el puerto de salida

    if (esdato == TRUE){
		LCD_OUT |= LCD_RS;
	}

    pulso_LCD();	// Habilita la lectura del dato enviado
}



/**********************************************************************
 * void posicioncursor_LCD (char fila, char columna)
 *
 * Setea la posición del curson en pantalla
 *
 * 		fila - número de fila (desde 0)
 *
 * 		columna - número de columna (desde 0)
 *********************************************************************/

void posicioncursor_LCD (char fila, char columna){
	char direccion;

	if (fila == 0){				//
		direccion = 0;			//
    } else {					// Construcción de la dirección a partir de la fila y la columna
		direccion = 0x40;		//
	}							//
	direccion |= columna;		//

    enviarbyte_LCD(0x80 | direccion, FALSE);
}



/**********************************************************************
 * void limpiarpantalla_LCD (void)
 *
 * Borra la pantalla y devuelve el cursor a la posición
 * inicial.
 *********************************************************************/

void limpiarpantalla_LCD (){
	enviarbyte_LCD(0x01, FALSE);
	enviarbyte_LCD(0x02, FALSE);
}



/**********************************************************************
 * void imprimirstring_LCD(char *texto)
 *
 * Imprime una cadena de caracteres en pantalla
 *
 * 		texto - cadena de caracteres terminada en NULL
 *********************************************************************/

void imprimirstring_LCD (char *texto){
	char *c;
	
	c = texto;
    while ((c != 0) && (*c != 0)){
		enviarbyte_LCD(*c, TRUE);
		c++;
	}
}



/**********************************************************************
				PROGRAMA DE PRUEBA

int main (void){
    WDTCTL = WDTPW + WDTHOLD;		// Stop watchdog timer

    init_LCD();
    limpiarpantalla_LCD();
    imprimirstring_LCD("Hello World!");
    while (1){
    }
}
**********************************************************************/
