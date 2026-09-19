#include "Cola_Evento.h"

ColaEventos::ColaEventos()
{
	frente = nullptr;
	final = nullptr;
}

bool ColaEventos::estaVacia()
{
	return frente == nullptr;
}
void ColaEventos::encolar(char tipoEvento, int activacion)
{
	NodoEvento* nuevo = new NodoEvento(tipoEvento, activacion);
	
	
	if (estaVacia())
	{
		frente = nuevo;
		final = nuevo;
		return;
	}
	
	
	if (activacion < frente->getActivacion())
	{
		nuevo->setSiguiente(frente);
		frente = nuevo;
		return;
	}
	
	
	NodoEvento* actual = frente;
	
	while (actual->getSiguiente() != nullptr &&
		   actual->getSiguiente()->getActivacion() <= activacion)
	{
		actual = actual->getSiguiente();
	}
	
	nuevo->setSiguiente(actual->getSiguiente());
	actual->setSiguiente(nuevo);
	
	
	if (nuevo->getSiguiente() == nullptr)
	{
		final = nuevo;
	}
}
NodoEvento* ColaEventos::desencolar()
{
	if (estaVacia())
	{
		return nullptr;
	}
	
	NodoEvento* auxiliar = frente;
	
	frente = frente->getSiguiente();
	
	if (frente == nullptr)
	{
		final = nullptr;
	}
	
	auxiliar->setSiguiente(nullptr);
	
	return auxiliar;
}
char ColaEventos::verTipoEvento()
{
	if (estaVacia())
	{
		return '\0';
	}
	
	return frente->getTipoEvento();
}

int ColaEventos::verActivacion()
{
	if (estaVacia())
	{
		return -1;
	}
	
	return frente->getActivacion();
}
