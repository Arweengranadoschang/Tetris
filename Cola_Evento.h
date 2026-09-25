#ifndef COLA_EVENTO_H
#define COLA_EVENTO_H
#include "Nodo_Evento.h"

class ColaEventos{
private:
	NodoEvento* frente;
	NodoEvento* final;
	
public:
	ColaEventos();
	
	void encolar(char tipoEvento, int activacion);
	NodoEvento* desencolar();
	char Tipo_Evento();
	int Activacion();
	bool estaVacia();
};


#endif
