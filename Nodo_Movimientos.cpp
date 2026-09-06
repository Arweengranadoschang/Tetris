#include "Nodo_Movimientos.h"

NodoMovimiento::NodoMovimiento()
{
	pieza = '\0';
	movimiento = '\0';
	anterior = nullptr;
	siguiente = nullptr;
}

NodoMovimiento::NodoMovimiento(char pieza, char movimiento)
{
	this->pieza = pieza;
	this->movimiento = movimiento;
	anterior = nullptr;
	siguiente = nullptr;
}

char NodoMovimiento::getPieza()
{
	return pieza;
}

void NodoMovimiento::setPieza(char pieza)
{
	this->pieza = pieza;
}

char NodoMovimiento::getMovimiento()
{
	return movimiento;
}

void NodoMovimiento::setMovimiento(char movimiento)
{
	this->movimiento = movimiento;
}

NodoMovimiento* NodoMovimiento::getAnterior()
{
	return anterior;
}

void NodoMovimiento::setAnterior(NodoMovimiento* anterior)
{
	this->anterior = anterior;
}

NodoMovimiento* NodoMovimiento::getSiguiente()
{
	return siguiente;
}

void NodoMovimiento::setSiguiente(NodoMovimiento* siguiente)
{
	this->siguiente = siguiente;
}
