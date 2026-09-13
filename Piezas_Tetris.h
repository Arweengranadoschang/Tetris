#ifndef PIEZAS_TETRIS_H
#define PIEZAS_TETRIS_H
#include "Tablero.h"

class PiezaTetris
{
private:
	char tipo;
	int orientacion;
	int fila;
	int columna;
	
	char formas[4][4][4];
	
public:
	PiezaTetris(char tipo);
	
	char getTipo();
	int getOrientacion();
	
	int getFila();
	int getColumna();
	
	void setFila(int fila);
	void setColumna(int columna);
	

	
	char getCelda(int fila, int columna);
	
	bool puedeColocarse(Tablero& tablero, int nuevaFila, int nuevaColumna);
	bool moverIzquierda(Tablero& tablero);
	bool moverDerecha(Tablero& tablero);
	bool bajar(Tablero& tablero);
	bool rotar(Tablero& tablero);
	void colocarEnTablero(Tablero& tablero);
};

#endif
