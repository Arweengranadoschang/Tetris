#ifndef NODO_MOVIMIENTOS_H
#define NODO_MOVIMIENTOS_H

class NodoMovimiento
{
private:
	char pieza;
	char movimiento;
	
	NodoMovimiento* anterior;
	NodoMovimiento* siguiente;
	
public:
	NodoMovimiento();
	NodoMovimiento(char pieza, char movimiento);
	
	char getPieza();
	void setPieza(char pieza);
	
	char getMovimiento();
	void setMovimiento(char movimiento);
	
	NodoMovimiento* getAnterior();
	void setAnterior(NodoMovimiento* anterior);
	
	NodoMovimiento* getSiguiente();
	void setSiguiente(NodoMovimiento* siguiente);
};

#endif
