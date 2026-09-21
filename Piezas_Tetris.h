#ifndef PIEZAS_TETRIS_H
#define PIEZAS_TETRIS_H

#include "Tablero.h"

class PiezaTetris{
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
	void setOrientacion(int orientacion);
	
	int getFila();
	int getColumna();
	
	void setFila(int fila);
	void setColumna(int columna);
	
	char getCelda(int fila, int columna);
	
	bool puede_Colocarse(Tablero& tablero, int nuevaFila, int nuevaColumna);
	bool mover_Izquierda(Tablero& tablero);
	bool mover_Derecha(Tablero& tablero);
	bool bajar(Tablero& tablero);
	bool rotar(Tablero& tablero);
	void colocar_Tablero(Tablero& tablero);
};

#endif
