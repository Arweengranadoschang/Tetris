#include "Nodo_Fila_Tablero.h"

NodoFilaTablero::NodoFilaTablero()
{
	for (int i = 0; i < 10; i++)
	{
		celdas[i] = '.';
	}
	
	siguiente = nullptr;
}

char NodoFilaTablero::getCelda(int posicion)
{
	if (posicion < 0 || posicion >= 10)
	{
		return '\0';
	}
	
	return celdas[posicion];
}

void NodoFilaTablero::setCelda(int posicion, char valor)
{
	if (posicion < 0 || posicion >= 10)
	{
		return;
	}
	
	celdas[posicion] = valor;
}
bool NodoFilaTablero::estaLlena()
{
	for (int i = 0; i < 10; i++)
	{
		if (celdas[i] == '.')
		{
			return false;
		}
	}
	
	return true;
}

NodoFilaTablero* NodoFilaTablero::getSiguiente()
{
	return siguiente;
}

void NodoFilaTablero::setSiguiente(NodoFilaTablero* siguiente)
{
	this->siguiente = siguiente;
}
