#ifndef TABLA_PUNTAJE_H
#define TABLA_PUNTAJE_H

#include <chrono>

class TablaPuntajes{
private:
	char nombres[10][50];
	int puntajes[10];
	int cantidad;
	double tiempo_Insercion;
	double tiempo_QuickSort;
	
public:
	TablaPuntajes();
	void agregarPuntaje(const char nombre[], int puntaje);
	int getCantidad();
	const char* getNombre(int posicion);
	int getPuntaje(int posicion);
	void Insercion();
	void QuickSort(int izquierda, int derecha);
	void Guardar_Archivo();
	void Cargar_Archivo();
	void medir_QuickSort();
	void medir_Insercion();
	double getTiempoQuickSort();
	double getTiempoInsercion();
		
};
#endif
