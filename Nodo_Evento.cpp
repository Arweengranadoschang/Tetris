#include "Nodo_Evento.h"

NodoEvento::NodoEvento(char tipoEvento, int activacion){
	this->tipoEvento = tipoEvento;
	this->activacion = activacion;
	siguiente = nullptr;
}

char NodoEvento::getTipoEvento(){
	return tipoEvento;
}

int NodoEvento::getActivacion(){
	return activacion;
}

NodoEvento* NodoEvento::getSiguiente(){
	return siguiente;
}

void NodoEvento::setSiguiente(NodoEvento* siguiente){
	this->siguiente = siguiente;
}
