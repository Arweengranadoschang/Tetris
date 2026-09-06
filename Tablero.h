#ifndef TABLERO_H
#define TABLERO_H
#include "Nodo_Fila_Tablero.h"

class Tablero
{
private:
	NodoFilaTablero* primeraFila;
	
public:
	Tablero();
	
	char getCelda(int fila, int columna);
	void setCelda(int fila, int columna, char valor);
	
	void mostrar_Tablero();
	bool fila_Llena(int fila);
	void eliminar_Fila(int fila);
	void eliminar_Filas_Completas();
};

#endif
