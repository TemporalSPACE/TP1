/* Inclusi?n de cabeceras de bibliotecas de c?digo */
#include <avr/io.h> // Definici?n de Registros del microcontrolador
#define F_CPU 16000000UL // Especifico la frecuencia de reloj del MCU en 16MHz
#include <util/delay.h> // Retardos por software ? Macros: depende de F_CPU

void dibujarDigito(int num){
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

/* Funci?n main */
int main (void)
{
	/* Setup */
	DDRC = 0xFF; // seteo todo como salida
	DDRB = 0xFF; // Setea el puerto B como salida
	/* Loop */
	//char num = 0;
	char q;
	int cont = 0;
	// Reemplazar por variable en delay

	while(1)
	{
		q = 0b00000001;

		PORTC = q;
		dibujarDigito((cont / 1000)%10);
		_delay_ms(25);
		q = (q << 1);

		PORTC = q;
		dibujarDigito((cont / 100)%10);
		_delay_ms(25);
		q = (q << 1);

		PORTC = q;
		dibujarDigito((cont / 10)%10);
		_delay_ms(25);
		q = (q << 1);

		PORTC = q;
		dibujarDigito(cont % 10);
		_delay_ms(25);
		q = (q << 1);

		cont++;
	}
	/* Punto de finalizaci?n del programa (NO se debe llegar a este lugar) */
	return 0;
}