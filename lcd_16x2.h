#include <msp430.h>

/***** Defines del mapeo a los puertos y pines del MSP430 *****/

#define     LCD_DIR               P1DIR
#define     LCD_OUT               P1OUT

#define     LCD_PIN_RS            BIT4          // P1.4
#define     LCD_PIN_EN            BIT5          // P1.5
#define     LCD_PIN_D7            BIT3          // P1.3
#define     LCD_PIN_D6            BIT2          // P1.2
#define     LCD_PIN_D5            BIT1          // P1.1
#define     LCD_PIN_D4            BIT0          // P1.0

#define     LCD_PIN_MASK  ((LCD_PIN_RS | LCD_PIN_EN | LCD_PIN_D7 | LCD_PIN_D6 | LCD_PIN_D5 | LCD_PIN_D4))

#define     FALSE                 0
#define     TRUE                  1


/***** Declaración de funciones *****/

void pulso_LCD (void);
void init_LCD (void);
void enviarbyte_LCD (char byteaenviar, int esdato);
void posicioncursor_LCD (char fila, char columna);
void limpiarpantalla_LCD (void);
void imprimirstring_LCD(char *texto);
