#include <iostream>
#include "Logica_Tetris.h"

using namespace std;

int main(int argc, char *argv[])
{
	LogicaTetris juego;
	
	juego.crearPieza();
	
	cout << "Pieza actual: "
		<< juego.getPiezaActual()
		<< endl;
	
	juego.moverIzquierda();
	juego.bajar();
	juego.rotar();
	
	juego.colocarPieza();
	
	cout << endl;
	cout << "MOVIMIENTOS REGISTRADOS:" << endl;
	
	juego.getRegistro().mostrar_Adelante();
	
	return 0;
}

