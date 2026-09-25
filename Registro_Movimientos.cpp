#include <iostream>
#include "Registro_Movimientos.h"

using namespace std;

RegistroMovimientos::RegistroMovimientos(){
	primero = nullptr;
	ultimo = nullptr;
	actual = nullptr;
}

RegistroMovimientos::~RegistroMovimientos(){
	limpiar();
}

void RegistroMovimientos::eliminarDesde(NodoMovimiento* nodo){
	if (nodo == nullptr){
		return;
	}
	
	NodoMovimiento* auxiliar = nodo;
	
	while (auxiliar != nullptr){
		NodoMovimiento* siguiente = auxiliar->getSiguiente();
		
		delete auxiliar;
		
		auxiliar = siguiente;
	}
}

void RegistroMovimientos::registrarMovimiento(char pieza,char movimiento){

	if (actual != nullptr && actual->getSiguiente() != nullptr){
		NodoMovimiento* futuro = actual->getSiguiente();
		
		actual->setSiguiente(nullptr);		
		ultimo = actual;
		eliminarDesde(futuro);
	}
	
	NodoMovimiento* nuevo =	new NodoMovimiento(pieza, movimiento);
	
	if (primero == nullptr){
		primero = nuevo;
		ultimo = nuevo;
		actual = nuevo;
	}
	else{
		ultimo->setSiguiente(nuevo);
		nuevo->setAnterior(ultimo);
		ultimo = nuevo;
		actual = nuevo;
	}
}

void RegistroMovimientos::guardarEstadoActual(char tablero[20][10],int filaPieza,int columnaPieza,int orientacionPieza,char piezaEnEspera, bool bombaActiva,int filaBomba,int columnaBomba,int puntaje){
	if (actual == nullptr){
		return;
	}
	
	actual->guardarEstado(tablero,filaPieza,columnaPieza,orientacionPieza,piezaEnEspera,bombaActiva,filaBomba,columnaBomba,puntaje);
}

bool RegistroMovimientos::deshacer(){
	if (actual == nullptr){
		return false;
	}
	
	if (actual->getAnterior() == nullptr){
		return false;
	}
	
	actual = actual->getAnterior();
	
	return true;
}

bool RegistroMovimientos::rehacer(){
	
	if (actual == nullptr){
		return false;
	}
	
	if (actual->getSiguiente() == nullptr){
		return false;
	}
	
	actual = actual->getSiguiente();
	
	return true;
}

void RegistroMovimientos::mostrar_Adelante(){
	
	NodoMovimiento* auxiliar = primero;
	
	while (auxiliar != nullptr){
		
		cout << auxiliar->getPieza()<< "-"<< auxiliar->getMovimiento()<< endl;
		auxiliar = auxiliar->getSiguiente();
	}
}

void RegistroMovimientos::mostrar_Atras(){
	NodoMovimiento* auxiliar = ultimo;
	
	while (auxiliar != nullptr){
		
		cout << auxiliar->getPieza()<< "-"	<< auxiliar->getMovimiento()<< endl;
		auxiliar = auxiliar->getAnterior();
	}
}

char RegistroMovimientos::getMovimientoActual(){
	if (actual == nullptr){
		return '\0';
	}
	
	return actual->getMovimiento();
}

char RegistroMovimientos::getMovimientoSiguiente(){
	if (actual == nullptr ||actual->getSiguiente() == nullptr){
		return '\0';
	}
	
	return actual->getSiguiente()->getMovimiento();
}

NodoMovimiento* RegistroMovimientos::getPrimero(){
	return primero;
}

NodoMovimiento* RegistroMovimientos::getActual(){
	return actual;
}

void RegistroMovimientos::ir_Primero(){
	actual = primero;
}

void RegistroMovimientos::ir_Ultimo(){
	actual = ultimo;
}
void RegistroMovimientos::limpiar()
{
	NodoMovimiento* auxiliar = primero;
	
	while (auxiliar != nullptr)
	{
		NodoMovimiento* siguiente =	auxiliar->getSiguiente();
		
		delete auxiliar;
		auxiliar = siguiente;
	}
	
	primero = nullptr;
	ultimo = nullptr;
	actual = nullptr;
}
