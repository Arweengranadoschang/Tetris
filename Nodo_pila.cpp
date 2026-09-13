#include "Nodo_Pila.h"

NodoPila::NodoPila()
{
	pieza = '\0';
	siguiente = nullptr;
}

NodoPila::NodoPila(char pieza)
{
	this->pieza = pieza;
	siguiente = nullptr;
}

char NodoPila::getPieza()
{
	return pieza;
}

void NodoPila::setPieza(char pieza)
{
	this->pieza = pieza;
}

NodoPila* NodoPila::getSiguiente()
{
	return siguiente;
}

void NodoPila::setSiguiente(NodoPila* siguiente)
{
	this->siguiente = siguiente;
}
