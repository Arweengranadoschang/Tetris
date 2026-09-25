#ifndef VISUAL_GAMEOVER_H
#define VISUAL_GAMEOVER_H
#include <SFML/Graphics.hpp>
#include <string>
#include "Tabla_Puntaje.h"

using namespace std;

class Visual_GameOver{
private:
	
	sf::RenderWindow& ventana;
	sf::Font& fuente;
	
	string nombreJugador;
	int puntaje;
	TablaPuntajes& tablaPuntajes;
	
	bool Mostrar_Tabla;
	string Algoritmo_Usado;
	
	double tiempo_Ordenamiento;
	
public:
	
	Visual_GameOver(sf::RenderWindow& ventana, sf::Font& fuent,TablaPuntajes& tablaPuntajes);
	void mostrar();
	void Datos(string nombre,int puntaje);
	bool Presionar_Reiniciar(const sf::Event& evento);
	bool Presionar_Salir( const sf::Event& evento);
	bool Presionar_QuickSort(const sf::Event& evento);
	bool Presionar_Insercion(const sf::Event& evento);
	void Ventana_Top10(const string& algoritmo);
	bool Presionar_Cerrar(const sf::Event& evento);
	bool Presionar_Replay(const sf::Event& evento);
};


#endif
