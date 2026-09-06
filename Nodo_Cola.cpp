#include "Nodo_Cola.h"
NodoCola::NodoCola(char pieza)
{
	this->pieza = pieza;
	this->siguiente = nullptr;
}

char NodoCola::getPieza()
{
	return pieza;
}

NodoCola* NodoCola::getSiguiente()
{
	return siguiente;
}

void NodoCola::setSiguiente(NodoCola* siguiente)
{
	this->siguiente = siguiente;
}
