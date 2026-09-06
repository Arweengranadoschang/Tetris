#include "Generador_Piezas.h"
#include <cstdlib>

GeneradorPiezas::GeneradorPiezas()
{
	generarBolsa();
}

void GeneradorPiezas::generarBolsa()
{
	char piezas[7] = {'I', 'O', 'T', 'S', 'Z', 'J', 'L'};
	
	for (int i = 6; i > 0; i--)
	{
		int posicion = rand() % (i + 1);
		
		char auxiliar = piezas[i];
		piezas[i] = piezas[posicion];
		piezas[posicion] = auxiliar;
	}
	
	for (int i = 0; i < 7; i++)
	{
		cola.encolar(piezas[i]);
	}
	
	
}
char GeneradorPiezas::siguientePieza()
{
	if (cola.estaVacia())
	{
		generarBolsa();
	}
	
	return cola.desencolar();
	
}

char GeneradorPiezas::verPieza(int posicion)
{
	return cola.verPieza(posicion);
}
