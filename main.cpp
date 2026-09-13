#include<iostream>
#include "Piezas_Tetris.h"
#include "Tablero.h"

using namespace std;

int main (int argc, char *argv[]) {
	
	Tablero tablero;
	
	
	for (int columna = 0; columna < 10; columna++)
	{
		if (columna != 4 && columna != 5)
		{
			tablero.setCelda(19, columna, 'X');
		}
	}
	
	cout << "Tablero antes de colocar la pieza:" << endl;
	tablero.mostrar_Tablero();
	
	cout << endl;
	

	PiezaTetris pieza('O');
	
	
	pieza.setFila(17);
	pieza.setColumna(3);
	
	pieza.colocarEnTablero(tablero);
	
	cout << "Tablero despues de colocar la pieza:" << endl;
	tablero.mostrar_Tablero();
	
	cout << endl;
	
	
	tablero.eliminar_Filas_Completas();
	
	cout << "Tablero despues de eliminar filas completas:" << endl;
	tablero.mostrar_Tablero();
	
	return 0;
	
}

