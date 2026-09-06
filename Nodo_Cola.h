#ifndef NODO_COLA_H
#define NODO_COLA_H

class NodoCola
{
private:
	char pieza;
	NodoCola* siguiente;
	
public:
	NodoCola(char pieza);
	
	char getPieza();
	NodoCola* getSiguiente();
	
	void setSiguiente(NodoCola* siguiente);
};


#endif
