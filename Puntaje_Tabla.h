#ifndef PUNTAJE_TABLA_H
#define PUNTAJE_TABLA_H

class PuntajeTabla
{
private:
	int puntos;
	
public:
	PuntajeTabla();
	
	void agregarPuntos(int cantidadFilas, int multiplicador = 1);
	
	int getPuntos();
};

#endif
