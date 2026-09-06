#ifndef GENERADOR_PIEZAS_H
#define GENERADOR_PIEZAS_H
#include "Piezas_cola.h"

class GeneradorPiezas
{
private:
	ColaPiezas cola;
	
public:
	GeneradorPiezas();
	char siguientePieza();
	char verPieza(int posicion);
	
	void generarBolsa();
};

#endif
