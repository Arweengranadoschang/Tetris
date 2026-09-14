#ifndef LOGICA_TETRIS_H
#define LOGICA_TETRIS_H

#include "Tablero.h"
#include "Piezas_Tetris.h"
#include "Generador_Piezas.h"
#include "Pila_EnEspera.h"
#include "Registro_Movimientos.h"

class LogicaTetris
{
private:
	Tablero tablero;
	GeneradorPiezas generador;
	PiezaTetris* piezaActual;
	PilaEnEspera pilaEnEspera;
	RegistroMovimientos registro;
	bool ejecutandoHistorial;
	
public:
	LogicaTetris();
	~LogicaTetris();
	
	void crearPieza();
	
	bool jugarPieza();
	bool puedeCrearPieza();
	
	bool moverIzquierda();
	bool moverDerecha();
	bool bajar();
	bool rotar();
	
	void colocarPieza();
	void eliminarFilas();
	
	Tablero& getTablero();
	char getPiezaActual();
	int getFilaPieza();
	int getColumnaPieza();
	int getOrientacionPieza();
	
	void guardarPieza();
	char getPiezaEnEspera();
	
	RegistroMovimientos& getRegistro();
	
	bool deshacer();
	bool rehacer();
};

#endif
