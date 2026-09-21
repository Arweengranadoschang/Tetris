#include "Piezas_Tetris.h"

PiezaTetris::PiezaTetris(char tipo){
	this->tipo = tipo;
	
	orientacion = 0;
	
	fila = 0;
	columna = 3;
	
	for (int orientacion = 0; orientacion < 4; orientacion++){
		for (int fila = 0; fila < 4; fila++){
			for (int columna = 0; columna < 4; columna++){
				formas[orientacion][fila][columna] = '.';
			}
		}
	}
	
	if (tipo == 'I'){
		formas[0][1][0] = 'I';
		formas[0][1][1] = 'I';
		formas[0][1][2] = 'I';
		formas[0][1][3] = 'I';
		
		formas[1][0][2] = 'I';
		formas[1][1][2] = 'I';
		formas[1][2][2] = 'I';
		formas[1][3][2] = 'I';
		
		formas[2][2][0] = 'I';
		formas[2][2][1] = 'I';
		formas[2][2][2] = 'I';
		formas[2][2][3] = 'I';
		
		formas[3][0][1] = 'I';
		formas[3][1][1] = 'I';
		formas[3][2][1] = 'I';
		formas[3][3][1] = 'I';
	}
	else if (tipo == 'O'){
		for (int i = 0; i < 4; i++){
			formas[i][1][1] = 'O';
			formas[i][1][2] = 'O';
			formas[i][2][1] = 'O';
			formas[i][2][2] = 'O';
		}
	}
	else if (tipo == 'T'){
		formas[0][1][1] = 'T';
		formas[0][2][0] = 'T';
		formas[0][2][1] = 'T';
		formas[0][2][2] = 'T';
		
		formas[1][1][1] = 'T';
		formas[1][2][1] = 'T';
		formas[1][3][1] = 'T';
		formas[1][2][2] = 'T';
		
		formas[2][1][0] = 'T';
		formas[2][1][1] = 'T';
		formas[2][1][2] = 'T';
		formas[2][2][1] = 'T';
		
		formas[3][1][0] = 'T';
		formas[3][1][1] = 'T';
		formas[3][0][1] = 'T';
		formas[3][2][1] = 'T';
	}
	else if (tipo == 'S'){
		formas[0][1][1] = 'S';
		formas[0][1][2] = 'S';
		formas[0][2][0] = 'S';
		formas[0][2][1] = 'S';
		
		formas[1][1][1] = 'S';
		formas[1][2][1] = 'S';
		formas[1][2][2] = 'S';
		formas[1][3][2] = 'S';
		
		formas[2][2][1] = 'S';
		formas[2][2][2] = 'S';
		formas[2][3][0] = 'S';
		formas[2][3][1] = 'S';
		
		formas[3][0][1] = 'S';
		formas[3][1][1] = 'S';
		formas[3][1][2] = 'S';
		formas[3][2][2] = 'S';
	}
	else if (tipo == 'Z'){
		formas[0][1][0] = 'Z';
		formas[0][1][1] = 'Z';
		formas[0][2][1] = 'Z';
		formas[0][2][2] = 'Z';
		
		formas[1][1][2] = 'Z';
		formas[1][2][1] = 'Z';
		formas[1][2][2] = 'Z';
		formas[1][3][1] = 'Z';
		
		formas[2][2][0] = 'Z';
		formas[2][2][1] = 'Z';
		formas[2][3][1] = 'Z';
		formas[2][3][2] = 'Z';
		
		formas[3][0][1] = 'Z';
		formas[3][1][0] = 'Z';
		formas[3][1][1] = 'Z';
		formas[3][2][0] = 'Z';
	}
	else if (tipo == 'J'){
		formas[0][1][0] = 'J';
		formas[0][2][0] = 'J';
		formas[0][2][1] = 'J';
		formas[0][2][2] = 'J';
		
		formas[1][1][1] = 'J';
		formas[1][1][2] = 'J';
		formas[1][2][1] = 'J';
		formas[1][3][1] = 'J';
		
		formas[2][1][0] = 'J';
		formas[2][1][1] = 'J';
		formas[2][1][2] = 'J';
		formas[2][2][2] = 'J';
		
		formas[3][0][1] = 'J';
		formas[3][1][1] = 'J';
		formas[3][2][0] = 'J';
		formas[3][2][1] = 'J';
	}
	else if (tipo == 'L'){
		formas[0][1][2] = 'L';
		formas[0][2][0] = 'L';
		formas[0][2][1] = 'L';
		formas[0][2][2] = 'L';
		
		formas[1][1][1] = 'L';
		formas[1][2][1] = 'L';
		formas[1][3][1] = 'L';
		formas[1][3][2] = 'L';
		
		formas[2][1][0] = 'L';
		formas[2][1][1] = 'L';
		formas[2][1][2] = 'L';
		formas[2][2][0] = 'L';
		
		formas[3][0][0] = 'L';
		formas[3][0][1] = 'L';
		formas[3][1][1] = 'L';
		formas[3][2][1] = 'L';
	}
}

char PiezaTetris::getTipo(){
	return tipo;
}

int PiezaTetris::getOrientacion(){
	return orientacion;
}

int PiezaTetris::getFila(){
	return fila;
}

int PiezaTetris::getColumna(){
	return columna;
}

void PiezaTetris::setFila(int fila){
	this->fila = fila;
}

void PiezaTetris::setColumna(int columna){
	this->columna = columna;
}

char PiezaTetris::getCelda(int fila, int columna){
	if (fila < 0 || fila >= 4 || columna < 0 || columna >= 4){
		return '\0';
	}
	
	return formas[orientacion][fila][columna];
}

bool PiezaTetris::puede_Colocarse(Tablero& tablero, int nuevaFila, int nuevaColumna){
	
	for (int filaPieza = 0; filaPieza < 4; filaPieza++){
		for (int columnaPieza = 0; columnaPieza < 4; columnaPieza++){
			char celda = formas[orientacion][filaPieza][columnaPieza];
			
			if (celda != '.'){
				
				int filaTablero = nuevaFila + filaPieza;
				int columnaTablero = nuevaColumna + columnaPieza;
				
				if (filaTablero < 0 || filaTablero >= 20){
					return false;
				}
				
				if (columnaTablero < 0 || columnaTablero >= 10){
					return false;
				}
				
				if (tablero.getCelda(filaTablero, columnaTablero) != '.'){
					return false;
				}
			}
		}
	}
	
	return true;
}


bool PiezaTetris::mover_Izquierda(Tablero& tablero){
	if (puede_Colocarse(tablero, fila, columna - 1)){
		columna--;
		return true;
	}
	
	return false;
}

bool PiezaTetris::mover_Derecha(Tablero& tablero){
	if (puede_Colocarse(tablero, fila, columna + 1)){
		columna++;
		return true;
	}
	
	return false;
}

bool PiezaTetris::bajar(Tablero& tablero){
	if (puede_Colocarse(tablero, fila + 1, columna)){
		fila++;
		return true;
	}
	
	return false;
}

bool PiezaTetris::rotar(Tablero& tablero){
	int nuevaOrientacion = orientacion + 1;
	
	if (nuevaOrientacion == 4){
		nuevaOrientacion = 0;
	}
	
	int orientacionAnterior = orientacion;
	
	orientacion = nuevaOrientacion;
	
	if (puede_Colocarse(tablero, fila, columna)){
		return true;
	}
	
	orientacion = orientacionAnterior;
	
	return false;
}

void PiezaTetris::colocar_Tablero(Tablero& tablero){
	
	for (int filaPieza = 0; filaPieza < 4; filaPieza++){
		for (int columnaPieza = 0; columnaPieza < 4; columnaPieza++){
			char celda = formas[orientacion][filaPieza][columnaPieza];
			
			if (celda != '.'){
				int filaTablero = fila + filaPieza;
				int columnaTablero = columna + columnaPieza;
				
				tablero.setCelda(filaTablero, columnaTablero, celda);
			}
		}
	}
}
void PiezaTetris::setOrientacion(int nuevaOrientacion){
	if (nuevaOrientacion >= 0 && nuevaOrientacion < 4){
		orientacion = nuevaOrientacion;
	}
}
