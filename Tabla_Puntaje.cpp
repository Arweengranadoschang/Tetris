#include "Tabla_Puntaje.h"
#include <cstring>
#include <fstream>
#include <chrono>

using namespace std;

TablaPuntajes::TablaPuntajes(){
	cantidad = 0;
	
	for (int i = 0; i < 10; i++){
		puntajes[i] = 0;
		nombres[i][0] = '\0';
	}
}

void TablaPuntajes::agregarPuntaje(const char nombre[], int puntaje){
	
		if (cantidad < 10){
			strcpy(nombres[cantidad], nombre);
			puntajes[cantidad] = puntaje;
			
			cantidad++;
		}
		else{
			if (puntaje > puntajes[9]){
				strcpy(nombres[9], nombre);
				puntajes[9] = puntaje;
			}
		}
}

int TablaPuntajes::getCantidad(){
	return cantidad;
}

const char* TablaPuntajes::getNombre(int posicion){
	if (posicion < 0 || posicion >= cantidad){
		return "";
	}
	
	return nombres[posicion];
}

int TablaPuntajes::getPuntaje(int posicion){
	if (posicion < 0 || posicion >= cantidad){
		return 0;
	}
	
	return puntajes[posicion];
}

void TablaPuntajes::Insercion(){
	
	for (int i = 1; i < cantidad; i++){
		int puntaje_Actual = puntajes[i];
		
		char nombre_Actual[100];
		strcpy(nombre_Actual, nombres[i]);
		
		int j = i - 1;
		
		while (j >= 0 && puntajes[j] < puntaje_Actual){
			puntajes[j + 1] = puntajes[j];
			
			strcpy(nombres[j + 1], nombres[j]);
			
			j--;
		}
		
		puntajes[j + 1] = puntaje_Actual;
		
		strcpy(nombres[j + 1], nombre_Actual);
	}
}

void TablaPuntajes::QuickSort(int izquierda, int derecha){
	if (izquierda >= derecha){
		return;
	}
	
	int i = izquierda;
	int j = derecha;
	
	
	int pivote = puntajes[izquierda];
	
	while (i <= j){
		
		while (puntajes[i] > pivote){
			i++;
		}
		
		
		while (puntajes[j] < pivote){
			j--;
		}
		
		if (i <= j){
			
			int auxiliarPuntaje = puntajes[i];
			
			puntajes[i] = puntajes[j];
			puntajes[j] = auxiliarPuntaje;
			
			char auxiliarNombre[50];
			
			strcpy(auxiliarNombre, nombres[i]);
			strcpy(nombres[i], nombres[j]);
			strcpy(nombres[j], auxiliarNombre);
			
			i++;
			j--;
		}
	}
	
	
	if (izquierda < j){
		QuickSort(izquierda, j);
	}
	
	
	if (i < derecha){
		QuickSort(i, derecha);
	}
}
void TablaPuntajes::Guardar_Archivo(){
	ofstream archivo("puntajes.txt");
	
	if (!archivo.is_open()){
		return;
	}
	
	for (int i = 0; i < cantidad; i++){
		
		archivo << nombres[i]<< " "<< puntajes[i]<< endl;
	}
	
	archivo.close();
}

void TablaPuntajes::Cargar_Archivo(){

	ifstream archivo("puntajes.txt");
	if (!archivo.is_open()){
		return;
	}
	
	cantidad = 0;
	
	while (cantidad < 10 && archivo >> nombres[cantidad] >> puntajes[cantidad]){
		cantidad++;
	}
		archivo.close();
}

void TablaPuntajes::medir_Insercion(){
	
	auto inicio = chrono::high_resolution_clock::now();
	Insercion();
	auto fin = chrono::high_resolution_clock::now();
	chrono::duration<double> tiempo = fin - inicio;
	tiempo_Insercion = tiempo.count();
}

void TablaPuntajes::medir_QuickSort(){
	
	auto inicio = chrono::high_resolution_clock::now();
	if (cantidad > 0){
		QuickSort(0, cantidad - 1);
	}
	
	auto fin = chrono::high_resolution_clock::now();
	chrono::duration<double> tiempo = fin - inicio;
	tiempo_QuickSort = tiempo.count();
}

double TablaPuntajes::getTiempoInsercion(){
	return tiempo_Insercion;
}

double TablaPuntajes::getTiempoQuickSort(){
	return tiempo_QuickSort;
}

