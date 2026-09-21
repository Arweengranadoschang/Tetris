#include "Generador_Piezas.h"
#include <cstdlib>
#include <ctime>

GeneradorPiezas::GeneradorPiezas(){
	srand(time(0));
	generar_Bolsa();
}

void GeneradorPiezas::generar_Bolsa(){
	
	char piezas[7] = {'I', 'O', 'T', 'S', 'Z', 'J', 'L'};
	
	for (int i = 6; i > 0; i--){
		int posicion = rand() % (i + 1);
		
		char auxiliar = piezas[i];
		piezas[i] = piezas[posicion];
		piezas[posicion] = auxiliar;
	}
	
	for (int i = 0; i < 7; i++){
		cola.encolar(piezas[i]);
	}
}

char GeneradorPiezas::siguiente_Pieza(){

	char pieza = cola.desencolar();
	
	asegurar_Piezas();
	
	return pieza;	
}

char GeneradorPiezas::ver_Pieza(int posicion){
	
	
	asegurar_Piezas();
	
	
	return cola.verPieza(posicion);
}

void GeneradorPiezas::asegurar_Piezas(){
	
	if (cola.verPieza(6) == '\0'){
		generar_Bolsa();
	}
}
