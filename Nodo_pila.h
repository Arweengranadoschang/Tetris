#ifndef NODO_PILA_H
#define NODO_PILA_H

class NodoPila
{
private:
	char pieza;
	NodoPila* siguiente;
	
public:
	NodoPila();
	NodoPila(char pieza);
	
	char getPieza();
	void setPieza(char pieza);
	
	NodoPila* getSiguiente();
	void setSiguiente(NodoPila* siguiente);
};


#endif
