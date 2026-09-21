#ifndef NODO_EVENTO_H
#define NODO_EVENTO_H

class NodoEvento{
private:
	char tipoEvento;
	int activacion;
	NodoEvento* siguiente;
	
public:
	NodoEvento(char tipoEvento, int activacion);
	
	char getTipoEvento();
	int getActivacion();
	
	NodoEvento* getSiguiente();
	void setSiguiente(NodoEvento* siguiente);
};
#endif
