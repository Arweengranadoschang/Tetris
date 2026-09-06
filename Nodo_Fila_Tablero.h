#ifndef NODO_FILA_TABLERO_H
#define NODO_FILA_TABLERO_H

class NodoFilaTablero
{
private:
	char celdas[10];
	NodoFilaTablero* siguiente;
	
public:
	NodoFilaTablero();
	
	char getCelda(int posicion);
	void setCelda(int posicion, char valor);
	
	NodoFilaTablero* getSiguiente();
	void setSiguiente(NodoFilaTablero* siguiente);
	
	bool estaLlena();
};

#endif
