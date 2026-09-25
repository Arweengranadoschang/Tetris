#ifndef VISUAL_TETRIS_H
#define VISUAL_TETRIS_H

#include <SFML/Graphics.hpp>
#include <optional>

#include "Logica_Tetris.h"
#include "Piezas_Tetris.h"
#include "Visual_Inicio.h"
#include "Visual_GameOver.h"

class Visual_Tetris{
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
	void Mostrar_Bomba();
	void Mostrar_Hold();
	
	enum Estado_Pantalla
	{
		INICIO,
		JUEGO,
		GAME_OVER,
		REPLAY,
		PAUSA
	};
	
	Estado_Pantalla estado;
	Visual_Inicio inicio;
	Visual_GameOver gameOver;
	void Mostrar_Replay();
	void Mostrar_Tablero_Replay();
	void Mostrar_Pieza_Replay();
	void Mostrar_Bomba_Replay();
	sf::Clock reloj_Replay;
	void Mostrar_Boton_Pausa();
	void Mostrar_Pantalla_Pausa();
	bool Presionar_Pausa(const sf::Event& evento);
	bool Presionar_Continuar(const sf::Event& evento);
	sf::Time tiempo_Acumulado;
	
public:
	Visual_Tetris();
	void ejecutar();
};

#endif
