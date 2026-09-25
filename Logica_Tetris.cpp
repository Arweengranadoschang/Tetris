#include "Logica_Tetris.h"
#include <iostream>

using namespace std;

LogicaTetris::LogicaTetris()
{
	piezaActual = nullptr;
	ejecutandoHistorial = false;
	prepararEventos();
	Game_Over = false;
	Cargar_TablaPuntajes();
	replayActivo = false;
	replayMovimiento = 0;
	replayTotal = 0;
	
}

LogicaTetris::~LogicaTetris(){
	if (piezaActual != nullptr){
		delete piezaActual;
	}
}

void LogicaTetris::crearPieza(){
	if (piezaActual != nullptr){
		delete piezaActual;
	}
	
	char tipo = generador.siguiente_Pieza();
	piezaActual = new PiezaTetris(tipo);
}

bool LogicaTetris::puedeCrearPieza(){
	if (piezaActual == nullptr){
		return false;
	}
	
	return piezaActual->puede_Colocarse(tablero, 0, 3);
}

bool LogicaTetris::jugarPieza(){
	crearPieza();
	
	if (!puedeCrearPieza()){
		return false;
	}
	
	while (bajar()){
	}
	
	colocarPieza();
	
	eliminarFilas();
	
	return true;
}

bool LogicaTetris::moverIzquierda(){
	if (piezaActual == nullptr)
		return false;
	
	bool movimientoRealizado =piezaActual->mover_Izquierda(tablero);
	
	if (movimientoRealizado && !ejecutandoHistorial){
		registro.registrarMovimiento(piezaActual->getTipo(),'I');
		
		GuardarEstadoMovimiento();
	}
	
	return movimientoRealizado;
}

bool LogicaTetris::moverDerecha(){
	if (piezaActual == nullptr)
		return false;
	
	bool movimientoRealizado =	piezaActual->mover_Derecha(tablero);
	
	if (movimientoRealizado && !ejecutandoHistorial){
		registro.registrarMovimiento(piezaActual->getTipo(), 'D' );
		
		GuardarEstadoMovimiento();
	}
	
	return movimientoRealizado;
}

bool LogicaTetris::bajar(){
	if (piezaActual == nullptr)
		return false;
	
	bool movimientoRealizado = piezaActual->bajar(tablero);
	
	if (movimientoRealizado && !ejecutandoHistorial){
		registro.registrarMovimiento(piezaActual->getTipo(),'B');
		
		GuardarEstadoMovimiento();
	}
	
	return movimientoRealizado;
}

void LogicaTetris::avanzar_Pieza(){
	if (Game_Over){
		return;
	}
	
	if (eventosEspeciales.getBombaActiva()){
		bajar_Bomba();
		return;
	}
	
	if (piezaActual == nullptr){
		crearPieza();
		
		if (!puedeCrearPieza()){
			Game_Over = true;
			
			delete piezaActual;
			piezaActual = nullptr;
			
		}
		
		return;
	}
	
	bool puedeBajar = piezaActual->bajar(tablero);
	
	if (puedeBajar){
		if (!ejecutandoHistorial){
			registro.registrarMovimiento(piezaActual->getTipo(),'B');
		}
		
		return;
	}
	colocarPieza();	
	eliminarFilas();
	
	
	if (eventosEspeciales.getBombaActiva()){
		return;
	}
	
	crearPieza();
	
	if (!puedeCrearPieza()){
		Game_Over = true;
		
		delete piezaActual;
		piezaActual = nullptr;
		
	}
}

bool LogicaTetris::rotar(){
	if (piezaActual == nullptr)
		return false;
	
	bool movimientoRealizado = piezaActual->rotar(tablero);
	
	if (movimientoRealizado && !ejecutandoHistorial){
		
		registro.registrarMovimiento(piezaActual->getTipo(),'R');
		
		GuardarEstadoMovimiento();
	}
	
	return movimientoRealizado;
}

void LogicaTetris::colocarPieza(){
	
	if (piezaActual != nullptr)	{
		piezaActual->colocar_Tablero(tablero);
		
		if (!ejecutandoHistorial){
			registro.registrarMovimiento(piezaActual->getTipo(),'C');
			
			GuardarEstadoMovimiento();
		}
	}
}

void LogicaTetris::eliminarFilas(){
	int cantidadFilas =	tablero.eliminar_Filas_Completas();
	
	if (cantidadFilas > 0){
		int multiplicador = 1;
		
		if (eventosEspeciales.getDoblePuntosActivo()){
			multiplicador = 2;
		}
		
		puntaje.agregarPuntos(cantidadFilas,multiplicador);
		
		eventosEspeciales.consumirDoblePuntos();
	}
	
	revisarEventos();
}

Tablero& LogicaTetris::getTablero(){
	return tablero;
}

char LogicaTetris::getPiezaActual(){
	if (piezaActual == nullptr){
		return '\0';
	}
	
	return piezaActual->getTipo();
}

char LogicaTetris::getPiezaSiguiente(int posicion){
	return generador.ver_Pieza(posicion);
}

int LogicaTetris::getFilaPieza(){
	if (piezaActual == nullptr){
		return -1;
	}
	
	return piezaActual->getFila();
}

int LogicaTetris::getColumnaPieza(){
	if (piezaActual == nullptr){
		return -1;
	}
	
	return piezaActual->getColumna();
}

int LogicaTetris::getOrientacionPieza(){
	if (piezaActual == nullptr){
		return -1;
	}
	
	return piezaActual->getOrientacion();
}
void LogicaTetris::guardarPieza(){
	if (piezaActual == nullptr)
		return;
	
	char piezaGuardada = piezaActual->getTipo();
	
	if (pilaEnEspera.estaVacia()){
		pilaEnEspera.apilar(piezaGuardada);
		
		delete piezaActual;
		piezaActual = nullptr;
		
		crearPieza();
	}
	else{
		char piezaEnEspera = pilaEnEspera.desapilar();
		
		pilaEnEspera.apilar(piezaGuardada);
		
		delete piezaActual;
		
		piezaActual = new PiezaTetris(piezaEnEspera);
	}
	
	if (!ejecutandoHistorial){
		registro.registrarMovimiento(piezaActual->getTipo(),'H');
		
		GuardarEstadoMovimiento();
	}
}
char LogicaTetris::getPiezaEnEspera(){
	return pilaEnEspera.verCima();
}

RegistroMovimientos& LogicaTetris::getRegistro(){
	return registro;
}

bool LogicaTetris::deshacer(){
	if (piezaActual == nullptr){
		return false;
	}
	
	char movimiento =registro.getMovimientoActual();
	
	if (movimiento == '\0'){
		return false;
	}
	
	ejecutandoHistorial = true;
	
	bool resultado = false;
	
	if (movimiento == 'I'){
		resultado =piezaActual->mover_Derecha(tablero);
	}
	else if (movimiento == 'D'){
		resultado =piezaActual->mover_Izquierda(tablero);
	}
	else if (movimiento == 'B'){
		if (piezaActual->getFila() > 0){
			piezaActual->setFila(piezaActual->getFila() - 1);
			
			resultado = true;
		}
	}
	else if (movimiento == 'R'){
		int orientacionActual = piezaActual->getOrientacion();
		
		int orientacionAnterior = orientacionActual - 1;
		
		if (orientacionAnterior < 0){
			orientacionAnterior = 3;
		}
		
		piezaActual->setOrientacion(orientacionAnterior);
		resultado = true;
	}
	
	ejecutandoHistorial = false;
	
	if (resultado){
		return registro.deshacer();
	}
	
	return false;
}

bool LogicaTetris::rehacer(){
	if (piezaActual == nullptr){
		return false;
	}
	
	char movimiento = registro.getMovimientoSiguiente();
	
	if (movimiento == '\0'){
		return false;
	}
	
	ejecutandoHistorial = true;
	
	bool resultado = false;
	
	if (movimiento == 'I'){
		resultado = piezaActual->mover_Izquierda(tablero);
	}
	else if (movimiento == 'D'){
		resultado = piezaActual->mover_Derecha(tablero);
	}
	else if (movimiento == 'B'){
		resultado = piezaActual->bajar(tablero);
	}
	else if (movimiento == 'R'){
		resultado = piezaActual->rotar(tablero);
	}
	
	ejecutandoHistorial = false;
	
	if (resultado){
		return registro.rehacer();
	}
	
	return false;
}

int LogicaTetris::getPuntaje(){
	return puntaje.getPuntos();
}

void LogicaTetris::prepararEventos(){
	colaEventos.encolar('B', 500);
	colaEventos.encolar('D', 1000);
	colaEventos.encolar('V', 1500);	
}

void LogicaTetris::revisarEventos(){
	
	while (!colaEventos.estaVacia() && puntaje.getPuntos() >= colaEventos.Activacion()){
		NodoEvento* evento = colaEventos.desencolar();
		
		char tipo = evento->getTipoEvento();
		int activacion = evento->getActivacion();
		
		cout << "Evento activado: " << tipo<< " en "<< activacion<< " puntos"<< endl;
		
		if (tipo == 'B'){
			eventosEspeciales.activarBomba();
		}
		else if (tipo == 'D'){
			eventosEspeciales.activarDoblePuntos();
		}
		else if (tipo == 'V'){
			eventosEspeciales.activar_Velocidad();
		}
				
		colaEventos.encolar(tipo, activacion + 1500);
		delete evento;
	}
	
}

bool LogicaTetris::getBombaActiva(){
	return eventosEspeciales.getBombaActiva();
}

int LogicaTetris::getFilaBomba(){
	return eventosEspeciales.getFilaBomba();
}

int LogicaTetris::getColumnaBomba(){
	return eventosEspeciales.getColumnaBomba();
}

bool LogicaTetris::mover_BombaIzquierda(){
	
	bool resultado = eventosEspeciales.mover_BombaIzquierda(tablero);
	
	if (resultado && !ejecutandoHistorial){
		registro.registrarMovimiento('\0', 'A');
		GuardarEstadoMovimiento();
	}
	
	return resultado;
}
bool LogicaTetris::mover_BombaDerecha(){ 
	
	bool resultado = eventosEspeciales.mover_BombaDerecha(tablero);
	
	if (resultado && !ejecutandoHistorial)
	{
		registro.registrarMovimiento('\0', 'E');
		GuardarEstadoMovimiento();
	}
	
	return resultado;
}

bool LogicaTetris::bajar_Bomba(){
	if (!eventosEspeciales.getBombaActiva())
		return false;
	
	bool pudoBajar = eventosEspeciales.bajar_Bomba(tablero);
	
	if (pudoBajar){
		if (!ejecutandoHistorial){
			registro.registrarMovimiento('\0', 'F');
			GuardarEstadoMovimiento();
		}
		
		return true;
	}
	
	eventosEspeciales.colocarBomba(tablero);
	
	if (!ejecutandoHistorial){
		registro.registrarMovimiento('\0', 'X');
		GuardarEstadoMovimiento();
	}
	
	crearPieza();
	
	if (!puedeCrearPieza()){
		Game_Over = true;
		
		delete piezaActual;
		piezaActual = nullptr;
	}
	
	return false;
}

void LogicaTetris::colocarBomba(){
	eventosEspeciales.colocarBomba(tablero);
}

bool LogicaTetris::getDoblePuntosActivo(){
	return eventosEspeciales.getDoblePuntosActivo();
}

char LogicaTetris::getCeldaPiezaActual(int fila,int columna){
	if (piezaActual == nullptr){
		return '\0';
	}
	
	return piezaActual->getCelda(fila,columna);
}

bool LogicaTetris::getGame_Over(){
	return Game_Over;
}

float LogicaTetris::getVelocidadCaida(){
	return eventosEspeciales.getVelocidad_Caida();
}
void LogicaTetris::Reiniciar_Partida(){
	
	if (piezaActual != nullptr){
		delete piezaActual;
		piezaActual = nullptr;
	}
	
	tablero = Tablero();
	generador = GeneradorPiezas();
	pilaEnEspera = PilaEnEspera();
	registro.limpiar();
	puntaje = Puntaje();
	colaEventos = ColaEventos();
	eventosEspeciales = LogicaEventosEspeciales();
	prepararEventos();
	ejecutandoHistorial = false;
	Game_Over = false;
	crearPieza();
	replayActivo = false;
	replayMovimiento = 0;
	replayTotal = 0;
}

void LogicaTetris::Cargar_TablaPuntajes(){
	tablaPuntajes.Cargar_Archivo();
}
void LogicaTetris::Guardar_Puntaje(const char nombre[],int puntajeFinal){
	tablaPuntajes.agregarPuntaje(nombre,puntajeFinal);
}
TablaPuntajes& LogicaTetris::getTablaPuntajes(){
	return tablaPuntajes;
}

void LogicaTetris::GuardarEstadoMovimiento(){
	char estadoTablero[20][10];
	
	for (int fila = 0; fila < 20; fila++){
		for (int columna = 0; columna < 10; columna++){
			estadoTablero[fila][columna] =
				tablero.getCelda(fila, columna);
		}
	}
	
	int filaPieza = -1;
	int columnaPieza = -1;
	int orientacionPieza = -1;
	char pieza = '\0';
	
	if (piezaActual != nullptr){
		pieza = piezaActual->getTipo();
		filaPieza = piezaActual->getFila();
		columnaPieza = piezaActual->getColumna();
		orientacionPieza = piezaActual->getOrientacion();
	}
	
	registro.guardarEstadoActual(estadoTablero,filaPieza,columnaPieza,orientacionPieza,pilaEnEspera.verCima(),eventosEspeciales.getBombaActiva(),eventosEspeciales.getFilaBomba(), eventosEspeciales.getColumnaBomba(),puntaje.getPuntos());
}

bool LogicaTetris::iniciar_Replay(){
	
	NodoMovimiento* primero = registro.getPrimero();
	
	if (primero == nullptr)
		return false;
	
	replayActivo = true;
	replayMovimiento = 0;
	registro.ir_Primero();
	return true;
}

bool LogicaTetris::replay_Siguiente(){
	if (!replayActivo)
		return false;
	
	if (!registro.rehacer())
		return false;
	
	replayMovimiento++;
	
	return true;
}

bool LogicaTetris::replay_Anterior(){
	if (!replayActivo)
		return false;
	
	if (!registro.deshacer())
		return false;
	
	if (replayMovimiento > 0)
		replayMovimiento--;
	
	return true;
}

void LogicaTetris::terminar_Replay(){
	replayActivo = false;
	
	registro.ir_Ultimo();
	
	NodoMovimiento* actual = registro.getActual();
	
	if (actual == nullptr)
		return;
	
	replayMovimiento = 0;
}
bool LogicaTetris::getReplayActivo(){
	return replayActivo;
}

int LogicaTetris::getReplayMovimiento(){
	return replayMovimiento;
}

int LogicaTetris::getReplayTotal(){
	int cantidad = 0;
	
	NodoMovimiento* auxiliar =registro.getPrimero();
	
	while (auxiliar != nullptr)	{
		cantidad++;
		
		auxiliar = auxiliar->getSiguiente();
	}
	
	return cantidad;
}

int LogicaTetris::getReplayFilaPieza(){
	
	NodoMovimiento* nodo =	registro.getActual();
	
	if (nodo == nullptr)
		return -1;
	
	return nodo->getFilaPieza();
}

int LogicaTetris::getReplayColumnaPieza(){
	
	NodoMovimiento* nodo = registro.getActual();
	
	if (nodo == nullptr)
		return -1;
	
	return nodo->getColumnaPieza();
}

int LogicaTetris::getReplayOrientacionPieza(){
	
	NodoMovimiento* nodo = registro.getActual();
	
	if (nodo == nullptr)
		return -1;
	
	return nodo->getOrientacionPieza();
}

char LogicaTetris::getReplayPieza(){
	NodoMovimiento* nodo = registro.getActual();
	
	if (nodo == nullptr)
		return '\0';
	
	return nodo->getPieza();
}

char LogicaTetris::getReplayPiezaEnEspera(){
	NodoMovimiento* nodo = registro.getActual();
	
	if (nodo == nullptr)
		return '\0';
	
	return nodo->getPiezaEnEspera();
}

char LogicaTetris::getReplayCeldaTablero(int fila, int columna)
{
	NodoMovimiento* nodo = registro.getActual();
	
	if (nodo == nullptr)
		return '\0';
	
	return nodo->getCeldaTablero(fila,columna);
}

bool LogicaTetris::getReplayBombaActiva(){
	NodoMovimiento* nodo =	registro.getActual();
	
	if (nodo == nullptr)
		return false;
	
	return nodo->getBombaActiva();
}

int LogicaTetris::getReplayFilaBomba(){
	NodoMovimiento* nodo =	registro.getActual();
	
	if (nodo == nullptr)
		return -1;
	
	return nodo->getFilaBomba();
}

int LogicaTetris::getReplayColumnaBomba(){
	NodoMovimiento* nodo =	registro.getActual();
	
	if (nodo == nullptr)
		return -1;
	
	return nodo->getColumnaBomba();
}

int LogicaTetris::getReplayPuntaje(){
	NodoMovimiento* nodo = registro.getActual();
	
	if (nodo == nullptr)
		return 0;
	
	return nodo->getPuntaje();
}
