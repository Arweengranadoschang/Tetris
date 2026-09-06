#include<iostream>
#include "Generador_Piezas.h"
#include "Pila_EnEspera.h"
using namespace std;

int main (int argc, char *argv[]) {
	
	GeneradorPiezas generador;
	PilaEnEspera espera;
	
	char actual = generador.siguientePieza();
	
	cout << "Pieza actual: " << actual << endl;
	
	// Guardar la pieza actual en Hold
	espera.apilar(actual);
	
	cout << "Pieza guardada en Hold: "
		<< espera.verCima() << endl;
	
	// Sacamos otra pieza para simular que seguimos jugando
	actual = generador.siguientePieza();
	
	cout << "Nueva pieza actual: " << actual << endl;
	
	// Simulamos el intercambio
	char guardada = espera.desapilar();
	
	espera.apilar(actual);
	
	actual = guardada;
	
	cout << "Despues del intercambio:" << endl;
	cout << "Pieza actual: " << actual << endl;
	cout << "Pieza en Hold: " << espera.verCima() << endl;
	
	return 0;

}

