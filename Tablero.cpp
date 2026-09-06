#include <iostream>
#include "Tablero.h"

using namespace std;

Tablero::Tablero()
{
	primeraFila = nullptr;
	
	NodoFilaTablero* anterior = nullptr;
	
	for (int i = 0; i < 20; i++)
	{
		NodoFilaTablero* nuevaFila = new NodoFilaTablero();
		
		if (primeraFila == nullptr)
		{
			primeraFila = nuevaFila;
		}
		else
		{
			anterior->setSiguiente(nuevaFila);
		}
		
		anterior = nuevaFila;
	}
}

char Tablero::getCelda(int fila, int columna)
{
	if (fila < 0 || fila >= 20 || columna < 0 || columna >= 10)
	{
		return '\0';
	}
	
	NodoFilaTablero* auxiliar = primeraFila;
	
	for (int i = 0; i < fila; i++)
	{
		auxiliar = auxiliar->getSiguiente();
	}
	
	return auxiliar->getCelda(columna);
}

void Tablero::setCelda(int fila, int columna, char valor)
{
	if (fila < 0 || fila >= 20 || columna < 0 || columna >= 10)
	{
		return;
	}
	
	NodoFilaTablero* auxiliar = primeraFila;
	
	for (int i = 0; i < fila; i++)
	{
		auxiliar = auxiliar->getSiguiente();
	}
	
	auxiliar->setCelda(columna, valor);
}

void Tablero::mostrar_Tablero()
{
	NodoFilaTablero* auxiliar = primeraFila;
	
	while (auxiliar != nullptr)
	{
		for (int columna = 0; columna < 10; columna++)
		{
			cout << auxiliar->getCelda(columna) << " ";
		}
		
		cout << endl;
		
		auxiliar = auxiliar->getSiguiente();
	}
}

bool Tablero::fila_Llena(int fila)
{
	if (fila < 0 || fila >= 20)
	{
		return false;
	}
	
	NodoFilaTablero* auxiliar = primeraFila;
	
	for (int i = 0; i < fila; i++)
	{
		auxiliar = auxiliar->getSiguiente();
	}
	
	return auxiliar->estaLlena();
}

void Tablero::eliminar_Fila(int fila)
{
	if (fila < 0 || fila >= 20)
	{
		return;
	}
	
	NodoFilaTablero* auxiliar = primeraFila;
	NodoFilaTablero* anterior = nullptr;
	
	for (int i = 0; i < fila; i++)
	{
		anterior = auxiliar;
		auxiliar = auxiliar->getSiguiente();
	}
	
	if (anterior == nullptr)
	{
		primeraFila = auxiliar->getSiguiente();
	}
	else
	{
		anterior->setSiguiente(auxiliar->getSiguiente());
	}
	
	delete auxiliar;
	
	NodoFilaTablero* nuevaFila = new NodoFilaTablero();
	
	nuevaFila->setSiguiente(primeraFila);
	primeraFila = nuevaFila;
}

void Tablero::eliminar_Filas_Completas()
{
	int fila = 0;
	
	while (fila < 20)
	{
		if (fila_Llena(fila))
		{
			eliminar_Fila(fila);
		}
		else
		{
			fila++;
		}
	}
}
