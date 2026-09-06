#include<iostream>
#include "Tablero.h"

using namespace std;

int main (int argc, char *argv[]) {
	
	Tablero tablero;
	
	for (int columna = 0; columna < 10; columna++)
	{
		tablero.setCelda(5, columna, 'T');
		tablero.setCelda(6, columna, 'T');
	}
	
	cout << "Antes de eliminar:" << endl;
	tablero.mostrar_Tablero();
	
	cout << endl;
	
	tablero.eliminar_Filas_Completas();
	
	cout << "Despues de eliminar:" << endl;
	tablero.mostrar_Tablero();
	
	return 0;

}

