#ifndef LOGICA_TETRIS_H
#define LOGICA_TETRIS_H

#include "Tablero.h"
#include "Piezas_Tetris.h"
#include "Generador_Piezas.h"
#include "Pila_EnEspera.h"
#include "Registro_Movimientos.h"
#include "Puntaje_Tabla.h"
#include "Cola_Evento.h"
#include "Logica_EventosEspeciales.h"


class LogicaTetris
{
private:
	Tablero tablero;
	GeneradorPiezas generador;
	PiezaTetris* piezaActual;
	PilaEnEspera pilaEnEspera;
	RegistroMovimientos registro;
	PuntajeTabla puntaje;
	bool ejecutandoHistorial;
	ColaEventos colaEventos;
	LogicaEventosEspeciales eventosEspeciales;
	bool Game_Over;
	
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
	char getPiezaSiguiente(int posicion);
	int getFilaPieza();
	int getColumnaPieza();
	int getOrientacionPieza();
	
	
	void guardarPieza();
	char getPiezaEnEspera();
	
	RegistroMovimientos& getRegistro();
	
	bool deshacer();
	bool rehacer();
	
	int getPuntaje();
	void prepararEventos();
	void revisarEventos();
	
	bool getBombaActiva();
	
	int getFilaBomba();
	int getColumnaBomba();
	
	bool mover_BombaIzquierda();
	bool mover_BombaDerecha();
	bool bajar_Bomba();
	
	void colocarBomba();
	bool getDoblePuntosActivo();
	
	char getCeldaPiezaActual(int fila, int columna);
	void avanzar_Pieza();
	bool getGame_Over();
	
	float getVelocidadCaida();
};

#endif
