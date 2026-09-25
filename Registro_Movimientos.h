#ifndef REGISTRO_MOVIMIENTOS_H
#define REGISTRO_MOVIMIENTOS_H

#include "Nodo_Movimientos.h"

class RegistroMovimientos{
private:
	
	NodoMovimiento* primero;
	NodoMovimiento* ultimo;
	NodoMovimiento* actual;
	
	void eliminarDesde(NodoMovimiento* nodo);
	
	
public:
	RegistroMovimientos();
	~RegistroMovimientos();
	void registrarMovimiento(char pieza, char movimiento);
	void guardarEstadoActual( char tablero[20][10],int filaPieza,int columnaPieza,int orientacionPieza,char piezaEnEspera,bool bombaActiva,int filaBomba,int columnaBomba,int puntaje);
	void mostrar_Adelante();
	void mostrar_Atras();
	bool deshacer();
	bool rehacer();
	char getMovimientoActual();
	char getMovimientoSiguiente();
	NodoMovimiento* getPrimero();
	NodoMovimiento* getActual();
	void ir_Primero();
	void ir_Ultimo();
	void limpiar();
};


#endif
