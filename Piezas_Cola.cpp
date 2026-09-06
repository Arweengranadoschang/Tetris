#include "Piezas_cola.h"

ColaPiezas::ColaPiezas()
{
	frente = nullptr;
	final = nullptr;
}

void ColaPiezas::encolar(char pieza)
{
	NodoCola* nuevo = new NodoCola(pieza);
	
	if (estaVacia())
	{
		frente = nuevo;
		final = nuevo;
	}
	else
	{
		final->setSiguiente(nuevo);
		final = nuevo;
	}
}

char ColaPiezas::desencolar()
{
	if (estaVacia())
	{
		return '\0';
	}
	
	NodoCola* auxiliar = frente;
	char pieza = frente->getPieza();
	
	frente = frente->getSiguiente();
	
	if (frente == nullptr)
	{
		final = nullptr;
	}
	
	delete auxiliar;
	
	return pieza;
}

char ColaPiezas::verFrente()
{
	if (estaVacia())
	{
		return '\0';
	}
	
	return frente->getPieza();
}


char ColaPiezas::verPieza(int posicion)
{
	if (posicion < 0 || estaVacia())
	{
		return '\0';
	}
	
	NodoCola* auxiliar = frente;
	
	for (int i = 0; i < posicion; i++)
	{
		if (auxiliar->getSiguiente() == nullptr)
		{
			return '\0';
		}
		
		auxiliar = auxiliar->getSiguiente();
	}
	
	return auxiliar->getPieza();
}



bool ColaPiezas::estaVacia()
{
	return frente == nullptr;
}
