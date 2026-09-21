#include "Visual_Tetris.h"
#include <iostream>
#include <string>
using namespace std;

Visual_Tetris::Visual_Tetris()
{
	ventana.create(sf::VideoMode({800, 800}), "Tetris" );
	
	ventana.setFramerateLimit(60);
	if (!fuente.openFromFile("InterDisplay-Bold.ttf"))
	{
		cout << "No se pudo cargar la fuente" << endl;
	}
	
	
	logica.crearPieza();
	tiempoFinal = 0;
}

void Visual_Tetris::ejecutar()
{
	while (ventana.isOpen())
	{
		while (const std::optional evento = ventana.pollEvent())
		{
			if (evento->is<sf::Event::Closed>())
			{
				ventana.close();
			}
			
			if (const auto* tecla = evento->getIf<sf::Event::KeyPressed>())
			{
				if (tecla->code == sf::Keyboard::Key::Left)
				{
					if (logica.getBombaActiva())
					{
						logica.mover_BombaIzquierda();
					}
					else
					{
						logica.moverIzquierda();
					}
				}
				
				if (tecla->code == sf::Keyboard::Key::Right)
				{
					if (logica.getBombaActiva())
					{
						logica.mover_BombaDerecha();
					}
					else
					{
						logica.moverDerecha();
					}
				}
				
				if (tecla->code == sf::Keyboard::Key::Down)
				{
					if (logica.getBombaActiva())
					{
						logica.bajar_Bomba();
					}
					else
					{
						logica.bajar();
					}
				}
				
				if (tecla->code == sf::Keyboard::Key::Up)
				{
					if (!logica.getBombaActiva())
					{
						logica.rotar();
					}
				}
				if (tecla->code == sf::Keyboard::Key::Space)
				{
					if (!logica.getBombaActiva())
					{
						logica.guardarPieza();
					}
				}
				
			}
		}
		
		if (reloj.getElapsedTime().asSeconds() >=
			logica.getVelocidadCaida())
		{
			logica.avanzar_Pieza();
			reloj.restart();
		}
		
		ventana.clear();
		
		Mostrar_Tablero();
		Mostrar_ColaPiezas();
		Mostrar_PiezaActual();
		Mostrar_Puntaje();
		Mostrar_Tiempo();
		Mostrar_GameOver();
		Mostrar_Bomba();
		Mostrar_Hold();
		
		ventana.display();
	}
}

void Visual_Tetris::Mostrar_Tablero()
{
	for (int fila = 0; fila < 20; fila++)
	{
		for (int columna = 0; columna < 10; columna++)
		{
			sf::RectangleShape celda;
			
			celda.setSize(
						  sf::Vector2f(
									   tamanoCelda - 1.0f,
									   tamanoCelda - 1.0f
									   )
						  );
			
			celda.setPosition(
							  sf::Vector2f(
										   posicionX + columna * tamanoCelda,
										   posicionY + fila * tamanoCelda
										   )
							  );
			
			char contenido =
				logica.getTablero().getCelda(fila, columna);
			
			if (contenido == '\0')
			{
				celda.setFillColor(
								   sf::Color(30, 30, 30)
								   );
			}
			else
			{
				sf::Color color;
				
				switch (contenido)
				{
				case 'I':
					color = sf::Color::Yellow;
					break;
					
				case 'O':
					color = sf::Color::Red;
					break;
					
				case 'T':
					color = sf::Color(255, 165, 0);
					break;
					
				case 'S':
					color = sf::Color::Green;
					break;
					
				case 'Z':
					color = sf::Color::Blue;
					break;
					
				case 'J':
					color = sf::Color(128, 0, 128);
					break;
					
				case 'L':
					color = sf::Color(255, 105, 180);
					break;
					
				default:
					color = sf::Color::White;
					break;
				}
				
				celda.setFillColor(color);
			}
			
			celda.setOutlineThickness(1.0f);
			
			celda.setOutlineColor(
								  sf::Color(100, 100, 100)
								  );
			
			ventana.draw(celda);
		}
	}
}

void Visual_Tetris::Mostrar_ColaPiezas()
{
	const float posicionColaY =
		posicionY + altoTablero + 40.0f;
	
	for (int i = 0; i < 3; i++)
	{
		char tipo = logica.getPiezaSiguiente(i);
		
		if (tipo == '\0')
		{
			continue;
		}
		
		PiezaTetris pieza(tipo);
		
		float posicionPiezaX =
			245.0f + i * 155.0f;
		
		Mostrar_Pieza(
					 pieza,
					 posicionPiezaX,
					 posicionColaY
					 );
	}
}

void Visual_Tetris::Mostrar_Pieza(PiezaTetris& pieza,float x,float y){
	const float tamanoPieza = 15.0f;
	const float tamanoEspacio = 70.0f;
	
	sf::Color color;
	
	switch (pieza.getTipo())
	{
	case 'I':
		color = sf::Color::Yellow;
		break;
		
	case 'O':
		color = sf::Color::Red;
		break;
		
	case 'T':
		color = sf::Color(255, 165, 0);
		break;
		
	case 'S':
		color = sf::Color::Green;
		break;
		
	case 'Z':
		color = sf::Color::Blue;
		break;
		
	case 'J':
		color = sf::Color(128, 0, 128);
		break;
		
	case 'L':
		color = sf::Color(255, 105, 180);
		break;
		
	default:
		color = sf::Color::White;
		break;
	}
	
	int filaMinima = 4;
	int filaMaxima = -1;
	int columnaMinima = 4;
	int columnaMaxima = -1;
	
	for (int fila = 0; fila < 4; fila++)
	{
		for (int columna = 0; columna < 4; columna++)
		{
			if (pieza.getCelda(fila, columna) == pieza.getTipo())
			{
				if (fila < filaMinima)
				{
					filaMinima = fila;
				}
				
				if (fila > filaMaxima)
				{
					filaMaxima = fila;
				}
				
				if (columna < columnaMinima)
				{
					columnaMinima = columna;
				}
				
				if (columna > columnaMaxima)
				{
					columnaMaxima = columna;
				}
			}
		}
	}
	
	float anchoFigura =
		(columnaMaxima - columnaMinima + 1)
		* tamanoPieza;
	
	float altoFigura =
		(filaMaxima - filaMinima + 1)
		* tamanoPieza;
	
	float inicioX =
		x + (tamanoEspacio - anchoFigura) / 2.0f;
	
	float inicioY =
		y + (tamanoEspacio - altoFigura) / 2.0f;
	
	for (int fila = 0; fila < 4; fila++)
	{
		for (int columna = 0; columna < 4; columna++)
		{
			char celda =
				pieza.getCelda(fila, columna);
			
			if (celda != pieza.getTipo())
			{
				continue;
			}
			
			sf::RectangleShape bloque;
			
			bloque.setSize(
						   sf::Vector2f(
										tamanoPieza - 1.0f,
										tamanoPieza - 1.0f
										)
						   );
			
			bloque.setPosition(
							   sf::Vector2f(
											inicioX +
											(columna - columnaMinima)
											* tamanoPieza,
											
											inicioY +
											(fila - filaMinima)
											* tamanoPieza
											)
							   );
			
			bloque.setFillColor(color);
			
			bloque.setOutlineThickness(1.0f);
			
			bloque.setOutlineColor(
								   sf::Color::White
								   );
			
			ventana.draw(bloque);
		}
	}
}

void Visual_Tetris::Mostrar_PiezaActual()
{
	char tipo = logica.getPiezaActual();
	
	if (tipo == '\0')
	{
		return;
	}
	
	int filaPieza = logica.getFilaPieza();
	int columnaPieza = logica.getColumnaPieza();
	
	sf::Color color;
	
	switch (tipo)
	{
	case 'I':
		color = sf::Color::Yellow;
		break;
		
	case 'O':
		color = sf::Color::Red;
		break;
		
	case 'T':
		color = sf::Color(255, 165, 0);
		break;
		
	case 'S':
		color = sf::Color::Green;
		break;
		
	case 'Z':
		color = sf::Color::Blue;
		break;
		
	case 'J':
		color = sf::Color(128, 0, 128);
		break;
		
	case 'L':
		color = sf::Color(255, 105, 180);
		break;
		
	default:
		color = sf::Color::White;
		break;
	}
	
	for (int fila = 0; fila < 4; fila++)
	{
		for (int columna = 0; columna < 4; columna++)
		{
			char celda =
				logica.getCeldaPiezaActual(fila, columna);
			
			if (celda != tipo)
			{
				continue;
			}
			
			sf::RectangleShape bloque;
			
			bloque.setSize(
						   sf::Vector2f(
										tamanoCelda - 1.0f,
										tamanoCelda - 1.0f
										)
						   );
			
			bloque.setPosition(
							   sf::Vector2f(
											posicionX +
											(columnaPieza + columna) * tamanoCelda,
											
											posicionY +
											(filaPieza + fila) * tamanoCelda
											)
							   );
			
			bloque.setFillColor(color);
			
			bloque.setOutlineThickness(1.0f);
			
			bloque.setOutlineColor(
								   sf::Color::White
								   );
			
			ventana.draw(bloque);
		}
	}
}
void Visual_Tetris::Mostrar_Puntaje()
{
	sf::Text texto(fuente, "PUNTAJE: " + std::to_string(logica.getPuntaje()), 24);
	
	texto.setPosition(
					  sf::Vector2f(30.0f, 30.0f)
					  );
	
	texto.setFillColor(sf::Color::White);
	
	ventana.draw(texto);
}

void Visual_Tetris::Mostrar_Tiempo()
{
	int segundos;
	
	if (logica.getGame_Over())
	{
		segundos = tiempoFinal;
	}
	else
	{
		segundos =
			Tiempo_Juego.getElapsedTime().asSeconds();
		
		tiempoFinal = segundos;
	}
	
	int minutos = segundos / 60;
	int segundosRestantes = segundos % 60;
	
	std::string tiempo =
		"TIEMPO: " +
		to_string(minutos) +
		":";
	
	if (segundosRestantes < 10)
	{
		tiempo += "0";
	}
	
	tiempo += to_string(segundosRestantes);
	
	sf::Text texto(fuente, tiempo, 24);
	
	texto.setPosition(
					  sf::Vector2f(620.0f, 30.0f)
					  );
	
	texto.setFillColor(sf::Color::White);
	
	ventana.draw(texto);
}

void Visual_Tetris::Mostrar_GameOver()
{
	if (!logica.getGame_Over())
	{
		return;
	}
	
	sf::Text texto(fuente,"GAME OVER",32);
	
	texto.setFillColor(sf::Color::Red);
	
	sf::FloatRect limites = texto.getLocalBounds();
	
	texto.setOrigin(sf::Vector2f(limites.position.x + limites.size.x / 2.0f,limites.position.y + limites.size.y / 2.0f));
	
	texto.setPosition(sf::Vector2f(400.0f,40.0f));
	
	ventana.draw(texto);
}

void Visual_Tetris::Mostrar_Bomba()
{
	if (!logica.getBombaActiva())
	{
		return;
	}
	
	int fila = logica.getFilaBomba();
	int columna = logica.getColumnaBomba();
	
	float x = posicionX + columna * tamanoCelda;
	float y = posicionY + fila * tamanoCelda;
	
	sf::CircleShape bomba(tamanoCelda / 2.5f);
	
	bomba.setPosition(
					  sf::Vector2f(
								   x + tamanoCelda / 2.0f - tamanoCelda / 2.5f,
								   y + tamanoCelda / 2.0f - tamanoCelda / 2.5f
								   )
					  );
	
	bomba.setFillColor(sf::Color::Red);
	
	ventana.draw(bomba);
}

void Visual_Tetris::Mostrar_Hold()
{
	sf::Text titulo(fuente, "HOLD", 20);
	
	titulo.setPosition(
					   sf::Vector2f(125.0f, posicionY + altoTablero + 20.0f)
					   );
	
	titulo.setFillColor(sf::Color::White);
	
	ventana.draw(titulo);
	
	char tipo = logica.getPiezaEnEspera();
	
	if (tipo == '\0')
	{
		return;
	}
	
	PiezaTetris pieza(tipo);
	
	Mostrar_Pieza(
				  pieza,
				  125.0f,
				  posicionY + altoTablero + 45.0f
				  );
}
