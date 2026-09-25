#include "Logica_EventosEspeciales.h"
using namespace std;

LogicaEventosEspeciales::LogicaEventosEspeciales(){

	bombaActiva = false;
	filaBomba = 0;
	columnaBomba = 4;
	
	doblePuntos_Activo = false;
	jugadasDoblePuntos = 0;
	
	velocidad_Activa = false;
	velocidad_Caida = 2.0f;
	
	inicioVelocidad = chrono::steady_clock::now();
}

void LogicaEventosEspeciales::activarBomba(){
	bombaActiva = true;
	filaBomba = 0;
	columnaBomba = 4;
}

bool LogicaEventosEspeciales::getBombaActiva(){
	return bombaActiva;
}

int LogicaEventosEspeciales::getFilaBomba(){
	return filaBomba;
}

int LogicaEventosEspeciales::getColumnaBomba(){
	return columnaBomba;
}

void LogicaEventosEspeciales::setFilaBomba(int fila){
	filaBomba = fila;
}

void LogicaEventosEspeciales::setColumnaBomba(int columna){
	columnaBomba = columna;
}

bool LogicaEventosEspeciales::puedeMoverBomba(Tablero& tablero,int nuevaFila, int nuevaColumna)
{
	if (nuevaFila < 0 || nuevaFila >= 20)
	{
		return false;
	}
	
	if (nuevaColumna < 0 || nuevaColumna >= 10)
	{
		return false;
	}
	
	if (tablero.getCelda(nuevaFila, nuevaColumna) != '.')
	{
		return false;
	}
	
	return true;
}

bool LogicaEventosEspeciales::mover_BombaIzquierda( Tablero& tablero){
	if (!bombaActiva){
		return false;
	}
	
	if (puedeMoverBomba(tablero,filaBomba,columnaBomba - 1)){
		columnaBomba--;
		return true;
	}
	return false;
}

bool LogicaEventosEspeciales::mover_BombaDerecha(Tablero& tablero){
	if (!bombaActiva){
		return false;
	}
	
	if (puedeMoverBomba(tablero,filaBomba,columnaBomba + 1)){
		columnaBomba++;
		return true;
	}
     return false;
}

bool LogicaEventosEspeciales::bajar_Bomba( Tablero& tablero){
	if (!bombaActiva){
		return false;
	}
	
	if (puedeMoverBomba(tablero,filaBomba + 1,columnaBomba)){
		filaBomba++;
		return true;
	}
		
    return false;
}

void LogicaEventosEspeciales::colocarBomba(Tablero& tablero){
	if (!bombaActiva){
		return;
	}
	
	explotarBomba(tablero);
}

void LogicaEventosEspeciales::explotarBomba(Tablero& tablero){
	for (int fila = filaBomba - 1;fila <= filaBomba + 1;fila++)	{
		for (int columna = columnaBomba - 1;columna <= columnaBomba + 1; columna++)	{
			if (fila >= 0 && fila < 20 && columna >= 0 && columna < 10)	{
				tablero.setCelda(fila,columna,'.');
			}
		}
	}
	
	bombaActiva = false;
}

void LogicaEventosEspeciales::activarDoblePuntos(){
	doblePuntos_Activo = true;
	
	
	jugadasDoblePuntos = 2;
}

bool LogicaEventosEspeciales::getDoblePuntosActivo(){
	return doblePuntos_Activo;
}

void LogicaEventosEspeciales::consumirDoblePuntos(){
	if (!doblePuntos_Activo)	{
		return;
	}
	
	jugadasDoblePuntos--;
	
	if (jugadasDoblePuntos <= 0){
		jugadasDoblePuntos = 0;
		doblePuntos_Activo = false;
	}
}

void LogicaEventosEspeciales::activar_Velocidad(){
	velocidad_Activa = true;

	velocidad_Caida = 0.5f;
	
	
	inicioVelocidad = chrono::steady_clock::now();
}

void LogicaEventosEspeciales::revisar_TiempoVelocidad(){
	if (!velocidad_Activa){
		return;
	}
	
	chrono::steady_clock::time_point ahora = chrono::steady_clock::now();
	
	chrono::duration<double> tiempoTranscurrido = ahora - inicioVelocidad;
	
	if (tiempoTranscurrido.count() >= 15.0){
		velocidad_Activa = false;
		
		velocidad_Caida = 2.0f;
	}
}

bool LogicaEventosEspeciales::getVelocidad_Activa(){
	revisar_TiempoVelocidad();
	
	return velocidad_Activa;
}

float LogicaEventosEspeciales::getVelocidad_Caida(){
	revisar_TiempoVelocidad();
	
	return velocidad_Caida;
}
