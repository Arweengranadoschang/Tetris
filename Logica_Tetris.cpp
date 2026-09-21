#include "Logica_Tetris.h"
#include <iostream>

using namespace std;

LogicaTetris::LogicaTetris()
{
	piezaActual = nullptr;
	ejecutandoHistorial = false;
	
	prepararEventos();
	
	Game_Over = false;
}

LogicaTetris::~LogicaTetris()
{
	if (piezaActual != nullptr)
	{
		delete piezaActual;
	}
}

void LogicaTetris::crearPieza()
{
	if (piezaActual != nullptr)
	{
		delete piezaActual;
	}
	
	char tipo = generador.siguiente_Pieza();
	
	piezaActual = new PiezaTetris(tipo);
}

bool LogicaTetris::puedeCrearPieza()
{
	if (piezaActual == nullptr)
	{
		return false;
	}
	
	return piezaActual->puede_Colocarse(tablero, 0, 3);
}

bool LogicaTetris::jugarPieza()
{
	crearPieza();
	
	if (!puedeCrearPieza())
	{
		return false;
	}
	
	while (bajar())
	{
	}
	
	colocarPieza();
	
	eliminarFilas();
	
	return true;
}

bool LogicaTetris::moverIzquierda()
{
	if (piezaActual == nullptr)
	{
		return false;
	}
	
	bool movimientoRealizado =
		piezaActual->mover_Izquierda(tablero);
	
	if (movimientoRealizado && !ejecutandoHistorial)
	{
		registro.registrarMovimiento(
									 piezaActual->getTipo(), 'I');
	}
	
	return movimientoRealizado;
}

bool LogicaTetris::moverDerecha()
{
	if (piezaActual == nullptr)
	{
		return false;
	}
	
	bool movimientoRealizado =
		piezaActual->mover_Derecha(tablero);
	
	if (movimientoRealizado && !ejecutandoHistorial)
	{
		registro.registrarMovimiento(
									 piezaActual->getTipo(), 'D');
	}
	
	return movimientoRealizado;
}

bool LogicaTetris::bajar()
{
	if (piezaActual == nullptr)
	{
		return false;
	}
	
	bool movimientoRealizado =
		piezaActual->bajar(tablero);
	
	if (movimientoRealizado && !ejecutandoHistorial)
	{
		registro.registrarMovimiento(
									 piezaActual->getTipo(), 'B');
	}
	
	return movimientoRealizado;
}

void LogicaTetris::avanzar_Pieza()
{
	if (Game_Over)
	{
		return;
	}
	
	if (eventosEspeciales.getBombaActiva())
	{
		bajar_Bomba();
		return;
	}
	
	if (piezaActual == nullptr)
	{
		crearPieza();
		
		if (!puedeCrearPieza())
		{
			Game_Over = true;
			
			delete piezaActual;
			piezaActual = nullptr;
			
			cout << "GAME OVER" << endl;
		}
		
		return;
	}
	
	bool puedeBajar = piezaActual->bajar(tablero);
	
	if (puedeBajar)
	{
		if (!ejecutandoHistorial)
		{
			registro.registrarMovimiento(
										 piezaActual->getTipo(),
										 'B'
										 );
		}
		
		return;
	}
	
	
	colocarPieza();
	
	
	eliminarFilas();
	
	
	if (eventosEspeciales.getBombaActiva())
	{
		return;
	}
	
	
	crearPieza();
	
	if (!puedeCrearPieza())
	{
		Game_Over = true;
		
		delete piezaActual;
		piezaActual = nullptr;
		
		cout << "GAME OVER" << endl;
	}
}

bool LogicaTetris::rotar()
{
	if (piezaActual == nullptr)
	{
		return false;
	}
	
	bool movimientoRealizado =
		piezaActual->rotar(tablero);
	
	if (movimientoRealizado && !ejecutandoHistorial)
	{
		registro.registrarMovimiento(
									 piezaActual->getTipo(), 'R');
	}
	
	return movimientoRealizado;
}

void LogicaTetris::colocarPieza()
{
	if (piezaActual != nullptr)
	{
		piezaActual->colocar_Tablero(tablero);
		
		if (!ejecutandoHistorial)
		{
			registro.registrarMovimiento(
										 piezaActual->getTipo(), 'C');
		}
	}
}

void LogicaTetris::eliminarFilas()
{
	int cantidadFilas =
		tablero.eliminar_Filas_Completas();
	
	if (cantidadFilas > 0)
	{
		int multiplicador = 1;
		
		if (eventosEspeciales.getDoblePuntosActivo())
		{
			multiplicador = 2;
		}
		
		puntaje.agregarPuntos(
							  cantidadFilas,
							  multiplicador);
	}
	
	revisarEventos();
}

Tablero& LogicaTetris::getTablero()
{
	return tablero;
}

char LogicaTetris::getPiezaActual()
{
	if (piezaActual == nullptr)
	{
		return '\0';
	}
	
	return piezaActual->getTipo();
}

char LogicaTetris::getPiezaSiguiente(int posicion)
{
	return generador.ver_Pieza(posicion);
}

int LogicaTetris::getFilaPieza()
{
	if (piezaActual == nullptr)
	{
		return -1;
	}
	
	return piezaActual->getFila();
}

int LogicaTetris::getColumnaPieza()
{
	if (piezaActual == nullptr)
	{
		return -1;
	}
	
	return piezaActual->getColumna();
}

int LogicaTetris::getOrientacionPieza()
{
	if (piezaActual == nullptr)
	{
		return -1;
	}
	
	return piezaActual->getOrientacion();
}

void LogicaTetris::guardarPieza()
{
	if (piezaActual == nullptr)
	{
		return;
	}
	
	char piezaGuardada =
		piezaActual->getTipo();
	
	if (pilaEnEspera.estaVacia())
	{
		pilaEnEspera.apilar(piezaGuardada);
		
		delete piezaActual;
		
		piezaActual = nullptr;
		
		crearPieza();
	}
	else
	{
		char piezaEnEspera =
			pilaEnEspera.desapilar();
		
		pilaEnEspera.apilar(piezaGuardada);
		
		delete piezaActual;
		
		piezaActual =
			new PiezaTetris(piezaEnEspera);
	}
}

char LogicaTetris::getPiezaEnEspera()
{
	return pilaEnEspera.verCima();
}

RegistroMovimientos& LogicaTetris::getRegistro()
{
	return registro;
}

bool LogicaTetris::deshacer()
{
	if (piezaActual == nullptr)
	{
		return false;
	}
	
	char movimiento =
		registro.getMovimientoActual();
	
	if (movimiento == '\0')
	{
		return false;
	}
	
	ejecutandoHistorial = true;
	
	bool resultado = false;
	
	if (movimiento == 'I')
	{
		resultado =
			piezaActual->mover_Derecha(tablero);
	}
	else if (movimiento == 'D')
	{
		resultado =
			piezaActual->mover_Izquierda(tablero);
	}
	else if (movimiento == 'B')
	{
		if (piezaActual->getFila() > 0)
		{
			piezaActual->setFila(
								 piezaActual->getFila() - 1);
			
			resultado = true;
		}
	}
	else if (movimiento == 'R')
	{
		int orientacionActual =
			piezaActual->getOrientacion();
		
		int orientacionAnterior =
			orientacionActual - 1;
		
		if (orientacionAnterior < 0)
		{
			orientacionAnterior = 3;
		}
		
		piezaActual->setOrientacion(
									orientacionAnterior);
		
		resultado = true;
	}
	
	ejecutandoHistorial = false;
	
	if (resultado)
	{
		return registro.deshacer();
	}
	
	return false;
}

bool LogicaTetris::rehacer()
{
	if (piezaActual == nullptr)
	{
		return false;
	}
	
	char movimiento =
		registro.getMovimientoSiguiente();
	
	if (movimiento == '\0')
	{
		return false;
	}
	
	ejecutandoHistorial = true;
	
	bool resultado = false;
	
	if (movimiento == 'I')
	{
		resultado =
			piezaActual->mover_Izquierda(tablero);
	}
	else if (movimiento == 'D')
	{
		resultado =
			piezaActual->mover_Derecha(tablero);
	}
	else if (movimiento == 'B')
	{
		resultado =
			piezaActual->bajar(tablero);
	}
	else if (movimiento == 'R')
	{
		resultado =
			piezaActual->rotar(tablero);
	}
	
	ejecutandoHistorial = false;
	
	if (resultado)
	{
		return registro.rehacer();
	}
	
	return false;
}

int LogicaTetris::getPuntaje()
{
	return puntaje.getPuntos();
}

void LogicaTetris::prepararEventos()
{
	colaEventos.encolar('B', 500);
	colaEventos.encolar('D', 1000);
	colaEventos.encolar('V', 1500);
	
	colaEventos.encolar('B', 2000);
	colaEventos.encolar('D', 2500);
	colaEventos.encolar('V', 3000);
}

void LogicaTetris::revisarEventos()
{
	while (!colaEventos.estaVacia() &&
		   puntaje.getPuntos() >=
		   colaEventos.Activacion())
	{
		NodoEvento* evento =
			colaEventos.desencolar();
		
		cout << "Evento activado: "
			<< evento->getTipoEvento()
			<< endl;
		
		if (evento->getTipoEvento() == 'B')
		{
			eventosEspeciales.activarBomba();
		}
		else if (evento->getTipoEvento() == 'D')
		{
			eventosEspeciales.activarDoblePuntos();
		}
		else if (evento->getTipoEvento() == 'V')
		{
			eventosEspeciales.activar_Velocidad();
		}
		
		delete evento;
	}
}

bool LogicaTetris::getBombaActiva()
{
	return eventosEspeciales.getBombaActiva();
}

int LogicaTetris::getFilaBomba()
{
	return eventosEspeciales.getFilaBomba();
}

int LogicaTetris::getColumnaBomba()
{
	return eventosEspeciales.getColumnaBomba();
}

bool LogicaTetris::mover_BombaIzquierda()
{
	return eventosEspeciales
		.mover_BombaIzquierda(tablero);
}

bool LogicaTetris::mover_BombaDerecha()
{
	return eventosEspeciales
		.mover_BombaDerecha(tablero);
}

bool LogicaTetris::bajar_Bomba()
{
	if (!eventosEspeciales.getBombaActiva())
	{
		return false;
	}
	
	bool pudoBajar = eventosEspeciales.bajar_Bomba(tablero);
	
	if (!pudoBajar)
	{
		eventosEspeciales.colocarBomba(tablero);
	}
	
	return pudoBajar;
}

void LogicaTetris::colocarBomba()
{
	eventosEspeciales.colocarBomba(tablero);
}

bool LogicaTetris::getDoblePuntosActivo()
{
	return eventosEspeciales
		.getDoblePuntosActivo();
}

char LogicaTetris::getCeldaPiezaActual(
									   int fila,
									   int columna)
{
	if (piezaActual == nullptr)
	{
		return '\0';
	}
	
	return piezaActual->getCelda(
								 fila,
								 columna);
}

bool LogicaTetris::getGame_Over()
{
	return Game_Over;
}

float LogicaTetris::getVelocidadCaida()
{
	return eventosEspeciales.getVelocidad_Caida();
}
