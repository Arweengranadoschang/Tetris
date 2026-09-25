#ifndef PUNTAJE_TABLA_H
#define PUNTAJE_TABLA_H

class Puntaje
{
private:
	int puntos;
	
public:
	Puntaje();
	void agregarPuntos(int cantidadFilas, int multiplicador = 1);
	int getPuntos();
};

#endif
