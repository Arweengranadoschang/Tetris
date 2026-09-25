#include "Nodo_Movimientos.h"

NodoMovimiento::NodoMovimiento(){
	pieza = '\0';
	movimiento = '\0';
	anterior = nullptr;
	siguiente = nullptr;
	filaPieza = -1;
	columnaPieza = -1;
	orientacionPieza = -1;
	piezaEnEspera = '\0';
	bombaActiva = false;
	filaBomba = -1;
	columnaBomba = -1;
	puntaje = 0;
	
	for (int fila = 0; fila < 20; fila++){
		for (int columna = 0; columna < 10; columna++){
			tablero[fila][columna] = '\0';
		}
	}
}

NodoMovimiento::NodoMovimiento(char pieza, char movimiento){
	
	this->pieza = pieza;
	this->movimiento = movimiento;
	anterior = nullptr;
	siguiente = nullptr;
	filaPieza = -1;
	columnaPieza = -1;
	orientacionPieza = -1;
	piezaEnEspera = '\0';
	bombaActiva = false;
	filaBomba = -1;
	columnaBomba = -1;
	puntaje = 0;
	
	for (int fila = 0; fila < 20; fila++){
		for (int columna = 0; columna < 10; columna++){
			tablero[fila][columna] = '\0';
		}
	}
}

char NodoMovimiento::getPieza(){
	return pieza;
}

void NodoMovimiento::setPieza(char pieza){
	this->pieza = pieza;
}

char NodoMovimiento::getMovimiento(){
	return movimiento;
}

void NodoMovimiento::setMovimiento(char movimiento){
	this->movimiento = movimiento;
}

NodoMovimiento* NodoMovimiento::getAnterior(){
	return anterior;
}

void NodoMovimiento::setAnterior(NodoMovimiento* anterior){
	this->anterior = anterior;
}

NodoMovimiento* NodoMovimiento::getSiguiente(){
	return siguiente;
}

void NodoMovimiento::setSiguiente(NodoMovimiento* siguiente){
	this->siguiente = siguiente;
}

void NodoMovimiento::guardarEstado(char tablero[20][10],int filaPieza,int columnaPieza,int orientacionPieza,char piezaEnEspera,bool bombaActiva,int filaBomba,int columnaBomba,int puntaje)
{
	for (int fila = 0; fila < 20; fila++){
		for (int columna = 0; columna < 10; columna++){
			this->tablero[fila][columna] =
				tablero[fila][columna];
		}
	}
	
	this->filaPieza = filaPieza;
	this->columnaPieza = columnaPieza;
	this->orientacionPieza = orientacionPieza;
	this->piezaEnEspera = piezaEnEspera;
	this->bombaActiva = bombaActiva;
	this->filaBomba = filaBomba;
	this->columnaBomba = columnaBomba;
	this->puntaje = puntaje;
}

char NodoMovimiento::getCeldaTablero(int fila, int columna){
	if (fila < 0 || fila >= 20 ||columna < 0 || columna >= 10){
		return '\0';
	}
	
	return tablero[fila][columna];
}

int NodoMovimiento::getFilaPieza(){
	return filaPieza;
}

int NodoMovimiento::getColumnaPieza(){
	return columnaPieza;
}

int NodoMovimiento::getOrientacionPieza(){
	return orientacionPieza;
}

char NodoMovimiento::getPiezaEnEspera(){
	return piezaEnEspera;
}

bool NodoMovimiento::getBombaActiva(){
	return bombaActiva;
}

int NodoMovimiento::getFilaBomba(){
	return filaBomba;
}

int NodoMovimiento::getColumnaBomba(){
	return columnaBomba;
}

int NodoMovimiento::getPuntaje(){
	return puntaje;
}
