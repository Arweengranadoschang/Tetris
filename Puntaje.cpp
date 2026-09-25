#include "Puntaje.h"

Puntaje::Puntaje()
{
	puntos = 0;
}

void Puntaje::agregarPuntos(int cantidadFilas, int multiplicador)
{
	puntos = puntos + (cantidadFilas * 100 * multiplicador);
}

int Puntaje::getPuntos()
{
	return puntos;
}
