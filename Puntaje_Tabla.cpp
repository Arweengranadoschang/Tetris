#include "Puntaje_Tabla.h"

PuntajeTabla::PuntajeTabla()
{
	puntos = 0;
}

void PuntajeTabla::agregarPuntos(int cantidadFilas, int multiplicador)
{
	puntos = puntos + (cantidadFilas * 100 * multiplicador);
}

int PuntajeTabla::getPuntos()
{
	return puntos;
}
