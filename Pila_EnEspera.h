#ifndef PILA_ENESPERA_H
#define PILA_ENESPERA_H

#include "Nodo_Pila.h"

class PilaEnEspera
{
private:
	NodoPila* cima;
	
public:
	PilaEnEspera();
	
	void apilar(char pieza);
	char desapilar();
	
	char verCima();
	bool estaVacia();
};

#endif
