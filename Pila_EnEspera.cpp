#include "Pila_EnEspera.h"

PilaEnEspera::PilaEnEspera()
{
	cima = nullptr;
}

void PilaEnEspera::apilar(char pieza)
{
	if (!estaVacia())
	{
		return;
	}
	NodoPila* nuevo = new NodoPila(pieza);
	
	nuevo->setSiguiente(cima);
	cima = nuevo;
}

char PilaEnEspera::desapilar()
{
	if (estaVacia())
	{
		return '\0';
	}
	
	NodoPila* auxiliar = cima;
	char pieza = cima->getPieza();
	
	cima = cima->getSiguiente();
	
	delete auxiliar;
	
	return pieza;
}

char PilaEnEspera::verCima()
{
	if (estaVacia())
	{
		return '\0';
	}
	
	return cima->getPieza();
}

bool PilaEnEspera::estaVacia()
{
	return cima == nullptr;
}
