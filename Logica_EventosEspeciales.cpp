#include "Logica_EventosEspeciales.h"

LogicaEventosEspeciales::LogicaEventosEspeciales()
{
	bombaActiva = false;
	filaBomba = 0;
	columnaBomba = 4;
	
	doblePuntos_Activo = false;
	
	velocidad_Activa = false;
	velocidad_Caida = 2.0f;
}

void LogicaEventosEspeciales::activarBomba()
{
	bombaActiva = true;
	
	filaBomba = 0;
	columnaBomba = 4;
}

bool LogicaEventosEspeciales::getBombaActiva()
{
	return bombaActiva;
}

int LogicaEventosEspeciales::getFilaBomba()
{
	return filaBomba;
}

int LogicaEventosEspeciales::getColumnaBomba()
{
	return columnaBomba;
}

void LogicaEventosEspeciales::setFilaBomba(int fila)
{
	filaBomba = fila;
}

void LogicaEventosEspeciales::setColumnaBomba(int columna)
{
	columnaBomba = columna;
}

bool LogicaEventosEspeciales::puedeMoverBomba(
											  Tablero& tablero,
											  int nuevaFila,
											  int nuevaColumna)
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

bool LogicaEventosEspeciales::mover_BombaIzquierda(Tablero& tablero)
{
	if (!bombaActiva)
	{
		return false;
	}
	
	if (puedeMoverBomba(tablero, filaBomba, columnaBomba - 1))
	{
		columnaBomba--;
		return true;
	}
	
	return false;
}

bool LogicaEventosEspeciales::mover_BombaDerecha(Tablero& tablero)
{
	if (!bombaActiva)
	{
		return false;
	}
	
	if (puedeMoverBomba(tablero, filaBomba, columnaBomba + 1))
	{
		columnaBomba++;
		return true;
	}
	
	return false;
}

bool LogicaEventosEspeciales::bajar_Bomba(Tablero& tablero)
{
	if (!bombaActiva)
	{
		return false;
	}
	
	if (puedeMoverBomba(tablero, filaBomba + 1, columnaBomba))
	{
		filaBomba++;
		return true;
	}
	
	return false;
}

void LogicaEventosEspeciales::colocarBomba(Tablero& tablero)
{
	if (!bombaActiva)
	{
		return;
	}
	
	explotarBomba(tablero);
}

void LogicaEventosEspeciales::explotarBomba(Tablero& tablero)
{
	for (int fila = filaBomba - 1; fila <= filaBomba + 1; fila++)
	{
		for (int columna = columnaBomba - 1;
		columna <= columnaBomba + 1;
		columna++)
		{
			if (fila >= 0 && fila < 20 &&
				columna >= 0 && columna < 10)
			{
				tablero.setCelda(fila, columna, '.');
			}
		}
	}
	
	bombaActiva = false;
}

void LogicaEventosEspeciales::activarDoblePuntos()
{
	doblePuntos_Activo = true;
}

bool LogicaEventosEspeciales::getDoblePuntosActivo()
{
	return doblePuntos_Activo;
}

void LogicaEventosEspeciales::activar_Velocidad()
{
	velocidad_Activa = true;
	velocidad_Caida = 0.5f;
}

bool LogicaEventosEspeciales::getVelocidad_Activa()
{
	return velocidad_Activa;
}

float LogicaEventosEspeciales::getVelocidad_Caida()
{
	return velocidad_Caida;
}
