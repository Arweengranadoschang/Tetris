#ifndef VISUAL_TETRIS_H
#define VISUAL_TETRIS_H

#include <SFML/Graphics.hpp>
#include <optional>

#include "Logica_Tetris.h"
#include "Piezas_Tetris.h"

class Visual_Tetris
{
private:
	
	sf::RenderWindow ventana;
	sf::Font fuente;
	sf::Clock reloj;
	LogicaTetris logica;
	sf::Clock Tiempo_Juego;
	int tiempoFinal;
	
	const float tamanoCelda = 20.0f;
	const float anchoTablero = 200.0f;
	const float altoTablero = 400.0f;
	
	
	const float posicionX = 300.0f;
	const float posicionY = 80.0f;

	void Mostrar_Tablero();
	void Mostrar_ColaPiezas();
	void Mostrar_Pieza(PiezaTetris& pieza, float x, float y);
	void Mostrar_PiezaActual();
	void Mostrar_Puntaje();
	void Mostrar_Tiempo();
	void Mostrar_GameOver();
	void Mostrar_Bomba();
	void Mostrar_Hold();
	
	
public:
	Visual_Tetris();
	
	void ejecutar();
};

#endif
