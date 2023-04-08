/* Inclusión de cabeceras de bibliotecas de código */
#include <avr/io.h> // Definición de Registros del microcontrolador
#define F_CPU 16000000UL // Especifico la frecuencia de reloj del MCU en 16MHz
#include <util/delay.h> // Retardos por software – Macros: depende de F_CPU
/* Función main */
int main (void)
{
	/* Setup */
	DDRC = 0; // 11111101 De acuerdo al valor del PINC0, DDRC va a tener un 0 en el bit0 o bit1
	DDRB = 0xFF; // Setea el puerto B como salida
	/* Loop */
	char num = 0;
	while(1)
	{
		if (PINC & (1<<PINC0)) // Si el PINC0 esta en 1
		{
			//PORTB = 0b1111111; 
			_delay_ms(10);
			num++;
			if(num==10){num=0;}
			PORTB = 0x00; 
			_delay_ms(10); 
		}
		else
		{
			switch (num){
				case 0:
					PORTB = 0b00111111;
					break;
				case 1:
					PORTB = 0b00000110;
					break;
				case 2:
				PORTB = 0b01011011;
				break;
				case 3:
				PORTB = 0b01001111;
				break;
				case 4:
				PORTB = 0b01100110;
				break;
				case 5:
				PORTB = 0b01101101;
				break;
				case 6:
				PORTB = 0b01111101;
				break;
				case 7:
				PORTB = 0b00000111;
				break;
				case 8:
				PORTB = 0b01111111;
				break;
				case 9:
				PORTB = 0b01101111;
				break;
			}
		}
	}
	/* Punto de finalización del programa (NO se debe llegar a este lugar) */
	return 0;
}

