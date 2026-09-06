#include <iostream>
#include "Registro_Movimientos.h"

using namespace std;

RegistroMovimientos::RegistroMovimientos()
{
	primero = nullptr;
	ultimo = nullptr;
	actual = nullptr;
}

void RegistroMovimientos::registrarMovimiento(char pieza, char movimiento)
{
	NodoMovimiento* nuevo = new NodoMovimiento(pieza, movimiento);
	
	if (primero == nullptr)
	{
		primero = nuevo;
		ultimo = nuevo;
		actual = nuevo;
	}
	else
	{
		ultimo->setSiguiente(nuevo);
		nuevo->setAnterior(ultimo);
		
		ultimo = nuevo;
		actual = nuevo;
	}
}

bool RegistroMovimientos::deshacer()
{
	if (actual == nullptr)
	{
		return false;
	}
	
	if (actual->getAnterior() == nullptr)
	{
		return false;
	}
	
	actual = actual->getAnterior();
	
	return true;
}

bool RegistroMovimientos::rehacer()
{
	if (actual == nullptr)
	{
		return false;
	}
	
	if (actual->getSiguiente() == nullptr)
	{
		return false;
	}
	
	actual = actual->getSiguiente();
	
	return true;
}

void RegistroMovimientos::mostrar_Adelante()
{
	NodoMovimiento* auxiliar = primero;
	
	while (auxiliar != nullptr)
	{
		cout << auxiliar->getPieza()
			<< "-"
			<< auxiliar->getMovimiento()
			<< endl;
		
		auxiliar = auxiliar->getSiguiente();
	}
}

void RegistroMovimientos::mostrar_Atras()
{
	NodoMovimiento* auxiliar = ultimo;
	
	while (auxiliar != nullptr)
	{
		cout << auxiliar->getPieza()
			<< "-"
			<< auxiliar->getMovimiento()
			<< endl;
		
		auxiliar = auxiliar->getAnterior();
	}
}
