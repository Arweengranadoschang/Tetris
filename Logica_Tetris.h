#ifndef LOGICA_TETRIS_H
#define LOGICA_TETRIS_H
#include "Tablero.h"
#include "Piezas_Tetris.h"
#include "Generador_Piezas.h"
#include "Pila_EnEspera.h"
#include "Registro_Movimientos.h"
#include "Puntaje.h"
#include "Cola_Evento.h"
#include "Logica_EventosEspeciales.h"
#include "Tabla_Puntaje.h"


class LogicaTetris{
private:
	Tablero tablero;
	GeneradorPiezas generador;
	PiezaTetris* piezaActual;
	PilaEnEspera pilaEnEspera;
	RegistroMovimientos registro;
	Puntaje puntaje;
	bool ejecutandoHistorial;
	ColaEventos colaEventos;
	LogicaEventosEspeciales eventosEspeciales;
	bool Game_Over;
	TablaPuntajes tablaPuntajes;
	bool replayActivo;
	int replayMovimiento;
	int replayTotal;
	
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
	void Reiniciar_Partida();
	void Cargar_TablaPuntajes();
	void Guardar_Puntaje(const char nombre[],int puntaje);
	TablaPuntajes& getTablaPuntajes();
	void GuardarEstadoMovimiento();
	bool iniciar_Replay();
	bool replay_Siguiente();
	bool replay_Anterior();
	void terminar_Replay();
	bool getReplayActivo();
	int getReplayMovimiento();
	int getReplayTotal();
	int getReplayFilaPieza();
	int getReplayColumnaPieza();
	int getReplayOrientacionPieza();
	char getReplayPieza();
	char getReplayPiezaEnEspera();
	char getReplayCeldaTablero(int fila, int columna);
	bool getReplayBombaActiva();
	int getReplayFilaBomba();
	int getReplayColumnaBomba();
	int getReplayPuntaje();
};

#endif
