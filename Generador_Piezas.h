#ifndef GENERADOR_PIEZAS_H
#define GENERADOR_PIEZAS_H
#include "Piezas_cola.h"

class GeneradorPiezas{
private:
	ColaPiezas cola;
	
public:
	GeneradorPiezas();
	char siguiente_Pieza();
	char ver_Pieza(int posicion);
	
	void generar_Bolsa();
	void asegurar_Piezas();
};
#endif
