#ifndef PIEZAS_COLA_H
#define PIEZAS_COLA_H
#include "Nodo_Cola.h"

class ColaPiezas
{
private:
	NodoCola* frente;
	NodoCola* final;
	
public:
	ColaPiezas();
	
	void encolar(char pieza);
	char desencolar();
	
	char verFrente();
	char verPieza(int posicion);
	
	bool estaVacia();
};





#endif
