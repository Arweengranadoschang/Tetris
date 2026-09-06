#ifndef REGISTRO_MOVIMIENTOS_H
#define REGISTRO_MOVIMIENTOS_H
#include "Nodo_Movimientos.h"

class RegistroMovimientos
{
private:
	NodoMovimiento* primero;
	NodoMovimiento* ultimo;
	NodoMovimiento* actual;
	
public:
	RegistroMovimientos();
	
	void registrarMovimiento(char pieza, char movimiento);
	
	
	void mostrar_Adelante();
	void mostrar_Atras();
	
	bool deshacer();
	bool rehacer();
};

#endif
