/* Inclusi?n de cabeceras de bibliotecas de c?digo */
#include <avr/io.h> // Definici?n de Registros del microcontrolador
#define F_CPU 16000000UL // Especifico la frecuencia de reloj del MCU en 16MHz
#include <util/delay.h> // Retardos por software ? Macros: depende de F_CPU
#define DELAY 2.5 // Retardo en milisegundos de cada display de 7 segentos

// Metodo que se encarga de setear los displays para mostrar los numeros
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

// Funcion para la lectura de los botones con control de rebote
uint8_t leerEntrada(int* cont, int corriendo){
	
		static uint8_t START = 0; // Guarda el estado del boton de Start
		static uint8_t STOP = 0; // Guarda el estado del boton de Stop
		static uint8_t RESET = 0; // Guarda el estado del boton de Reset
	
		// Contabilizan el numero de veces seguidas que el boton ha sido presionado
		static int contSTART = 0;
		static int contSTOP = 0;
		static int contRESET = 0;
		
		// Establece las mascaras de los botones
		START = PIND & 0b00000001;
		STOP = PIND & 0b00000010;
		RESET = PIND & 0b00000100;
		
		// Si presiona el boton de START
		if (START) {
			contSTART++;
			
			// Si el contador alcanza el numero 3 se considera el boton presionado
			if (contSTART == 3) {
				// Reanudo el timer
				corriendo = 1;
				START = 0;
			}
		}
		else {
			contSTART = 0;
		}
		
		// Si presiona el boton de STOP
		if (STOP){
			contSTOP++;
			
			// Si el contador alcanza el numero 3 se considera el boton presionado
			if (contSTOP == 3) {
				// Detiene el timer
				corriendo = 0;
				STOP = 0;
			}
		}
		else {
			contSTOP = 0;
		}
		
		// Si presiona el boton de RESET
		if (RESET) {
			contRESET++;
			
			// Si el contador alcanza el numero 3 se considera el boton presionado
			if (contRESET == 3) {
				// Hace el RESET:
				// - Se detiene el timer
				// - Se resetea el contador interno
	
				corriendo = 0;
				*cont = 0;	
				RESET = 0;			
			}
		}
		else {
			contRESET = 0;
		}
		
		return corriendo;
}

/* Funcion main */
int main (void)
{
	/* Setup */
	DDRD = 0xF8; // Seteamos los 3 bits menos signicativos como entrada (bit de RESET, bit de STOP y bit de START)
	DDRC = 0xFF; // Seteamos todos los bits como salida
	DDRB = 0xFF; // Seteamos todos los bits como salida

	uint8_t q; // Nibble de control de encendido de los displays
	int cont = 0; // Contador del reloj en centesimas de segundo
	uint8_t corriendo = 0;

	/* Loop */
	while(1)
	{		
			
		q = 0b00000001; // Establece para el encendido del primer display
		PORTC = q; // Activa el primer display
		dibujarDigito((cont / 1000)%10);
		
		_delay_ms(DELAY);
		
		q = (q << 1); // Establece para el encendido del segundo display
		PORTC = q; // Activa el segundo display
		dibujarDigito((cont / 100)%10);
		
		_delay_ms(DELAY);
		
		q = (q << 1); // Establece para el encendido del tercer display
		PORTC = q; // Activa el tercer display
		dibujarDigito((cont / 10)%10);
		
		_delay_ms(DELAY);
		
		q = (q << 1); // Establece para el encendido del cuarto display
		PORTC = q; // Activa el cuarto display
		dibujarDigito(cont % 10);
		
		_delay_ms(DELAY);

		corriendo = leerEntrada(&cont, corriendo);
		
		if (corriendo) 
			cont++;
	}
	return 0;
}