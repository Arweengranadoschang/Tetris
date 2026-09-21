#ifndef LOGICA_EVENTOSESPECIALES_H
#define LOGICA_EVENTOSESPECIALES_H
#include "Tablero.h"

class LogicaEventosEspeciales
{
private:
	bool bombaActiva;
	int filaBomba;
	int columnaBomba;
	bool puedeMoverBomba(Tablero& tablero, int nuevaFila, int nuevaColumna);
	bool doblePuntos_Activo;
	
	
	bool velocidad_Activa;
	float velocidad_Caida;
	
public:
	LogicaEventosEspeciales();
	
	void activarBomba();
	
	bool getBombaActiva();
	
	int getFilaBomba();
	int getColumnaBomba();
	
	void setFilaBomba(int fila);
	void setColumnaBomba(int columna);
	

	bool mover_BombaIzquierda(Tablero& tablero);
	bool mover_BombaDerecha(Tablero& tablero);
	bool bajar_Bomba(Tablero& tablero);
	
	void explotarBomba(Tablero& tablero);
	void colocarBomba(Tablero& tablero);
	
	void activarDoblePuntos();
	bool getDoblePuntosActivo();
	
	void activar_Velocidad();
	bool getVelocidad_Activa();
	float getVelocidad_Caida();
};

#endif
