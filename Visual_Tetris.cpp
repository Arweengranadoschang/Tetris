#include "Visual_Tetris.h"
#include <iostream>
#include <string>
using namespace std;

Visual_Tetris::Visual_Tetris(): inicio(ventana, fuente),gameOver(ventana, fuente, logica.getTablaPuntajes()){
	ventana.create(sf::VideoMode({800, 800}), "Tetris" );
	
	ventana.setFramerateLimit(60);
	if (!fuente.openFromFile("InterDisplay-Bold.ttf")){
		cout << "No se pudo cargar la fuente" << endl;
	}
	
	logica.crearPieza();
	tiempoFinal = 0;
	estado = INICIO;
}

void Visual_Tetris::ejecutar(){
	
	while (ventana.isOpen()){
		
		while (const optional evento = ventana.pollEvent()){
			
			if (evento->is<sf::Event::Closed>()){
				ventana.close();
			}
			if (estado == INICIO){
				
				inicio.Procesar_Evento(*evento);
				
				if (inicio.Presionar_Jugar(*evento)){
					if (!inicio.getNombreJugador().empty()){
						
						estado = JUEGO;
						
						Tiempo_Juego.restart();
						tiempo_Acumulado = sf::Time::Zero;
						reloj.restart();
					}
				}
				
				if (const auto* tecla = evento->getIf<sf::Event::KeyPressed>()){
					
					if (tecla->code == sf::Keyboard::Key::Enter){
						
						if (!inicio.getNombreJugador().empty()){
							
							estado = JUEGO;
							
							Tiempo_Juego.restart();
							tiempo_Acumulado = sf::Time::Zero;
							reloj.restart();
							
						}
					}
				}
			}
			
			else if (estado == JUEGO){
				
				if (Presionar_Pausa(*evento)){
					
					tiempo_Acumulado += Tiempo_Juego.getElapsedTime();
					
					estado = PAUSA;
					
					reloj.restart();
				}
				

				if (estado == JUEGO){
					
					if (const auto* tecla = evento->getIf<sf::Event::KeyPressed>()){
						
						if (tecla->code == sf::Keyboard::Key::Left){
							
							if (logica.getBombaActiva()){
								logica.mover_BombaIzquierda();
							}
							else{
								logica.moverIzquierda();
							}
						}
						
						if (tecla->code == sf::Keyboard::Key::Right){
							
							if (logica.getBombaActiva()){
								logica.mover_BombaDerecha();
							}
							else{
								logica.moverDerecha();
							}
						}
						
						if (tecla->code == sf::Keyboard::Key::Down){
							
							if (logica.getBombaActiva()){
								logica.bajar_Bomba();
							}
							else{
								logica.bajar();
							}
						}
						
						if (tecla->code == sf::Keyboard::Key::Up){
							
							if (!logica.getBombaActiva()){
								logica.rotar();
							}
						}
						
						if (tecla->code == sf::Keyboard::Key::Space){
							
							if (!logica.getBombaActiva()){
								logica.guardarPieza();
							}
						}
					}
				}
			}
			
			else if (estado == PAUSA){
				
				if (Presionar_Continuar(*evento)){
					
					estado = JUEGO;
					
					Tiempo_Juego.restart();
					
					reloj.restart();
				}
				
				if (const auto* tecla = evento->getIf<sf::Event::KeyPressed>()){
					
					if (tecla->code == sf::Keyboard::Key::Escape){
						
						estado = JUEGO;
						
						Tiempo_Juego.restart();
						
						reloj.restart();
					}
				}
			}
			
			else if (estado == GAME_OVER){
				
				if (gameOver.Presionar_Cerrar(*evento)){}
				
				else if (gameOver.Presionar_Salir(*evento)){
					ventana.close();
				}
				
				else if (gameOver.Presionar_Reiniciar(*evento)){
					
					logica.Reiniciar_Partida();
					
					estado = INICIO;
					
					tiempo_Acumulado = sf::Time::Zero;
					tiempoFinal = 0;
					
					reloj.restart();
					Tiempo_Juego.restart();	
				}
				
				else if (gameOver.Presionar_QuickSort(*evento)){
					
					TablaPuntajes& tabla = logica.getTablaPuntajes();
					
					if (tabla.getCantidad() > 0){
						
					    tabla.medir_QuickSort();
						
						tabla.Guardar_Archivo();
						
						gameOver.Ventana_Top10("QUICK SORT");
					}
				}
				
				else if (gameOver.Presionar_Insercion(*evento)){
					
					TablaPuntajes& tabla = logica.getTablaPuntajes();
					
					tabla.medir_Insercion();
					
					tabla.Guardar_Archivo();
					
					gameOver.Ventana_Top10("INSERCION");
				}
				
				if (const auto* tecla = evento->getIf<sf::Event::KeyPressed>()){
					
					if (tecla->code == sf::Keyboard::Key::Escape){
						ventana.close();
					}
				}
				
				else if (gameOver.Presionar_Replay(*evento)){
					
					if (logica.iniciar_Replay()){
						
						estado = REPLAY;
						
						reloj_Replay.restart();
					}
				}
			}
			
			else if (estado == REPLAY){
				
				if (const auto* tecla = evento->getIf<sf::Event::KeyPressed>()){
					
					if (tecla->code == sf::Keyboard::Key::Right){
						logica.replay_Siguiente();
					}
					
					if (tecla->code == sf::Keyboard::Key::Left){
						logica.replay_Anterior();
					}
					
					if (tecla->code == sf::Keyboard::Key::Escape){
						
						logica.terminar_Replay();
						
						estado = GAME_OVER;
					}
				}
			}
		}
		
		if (estado == JUEGO){
			
			if (reloj.getElapsedTime().asSeconds() >= logica.getVelocidadCaida()){
				
				logica.avanzar_Pieza();
				
				reloj.restart();
			}
			if (logica.getGame_Over()){
				
				tiempo_Acumulado += Tiempo_Juego.getElapsedTime();
				
				estado = GAME_OVER;
				
				tiempoFinal = static_cast<int>(tiempo_Acumulado.asSeconds());
				
				gameOver.Datos(inicio.getNombreJugador(),logica.getPuntaje());
				
				logica.Guardar_Puntaje(inicio.getNombreJugador().c_str(),logica.getPuntaje());
			}
		}
		
		if (estado == REPLAY){
			
			if (reloj_Replay.getElapsedTime().asSeconds() >= 0.35f){
				
				if (!logica.replay_Siguiente()){
					
					logica.terminar_Replay();
					
					estado = GAME_OVER;
				}
				
				reloj_Replay.restart();
			}
		}
				
		ventana.clear(sf::Color(15, 15, 15));
		
		if (estado == INICIO){
			
			inicio.mostrar();
		}
		
		else if (estado == JUEGO){
			
			Mostrar_Tablero();
			Mostrar_ColaPiezas();
			Mostrar_PiezaActual();
			Mostrar_Puntaje();
			Mostrar_Tiempo();
			Mostrar_Bomba();
			Mostrar_Hold();
			Mostrar_Boton_Pausa();
		}
		
		else if (estado == PAUSA){
			
			Mostrar_Tablero();
			Mostrar_ColaPiezas();
			Mostrar_PiezaActual();
			Mostrar_Puntaje();
			Mostrar_Tiempo();
			Mostrar_Bomba();
			Mostrar_Hold();
			
			Mostrar_Pantalla_Pausa();
		}
		
		else if (estado == GAME_OVER){
			
			gameOver.mostrar();
		}
		
		else if (estado == REPLAY){
			
			Mostrar_Replay();
		}
		
		ventana.display();
	}
}

void Visual_Tetris::Mostrar_Tablero(){
	
	for (int fila = 0; fila < 20; fila++){
		for (int columna = 0; columna < 10; columna++){
			sf::RectangleShape celda;
			
			celda.setSize(sf::Vector2f(tamanoCelda - 1.0f,tamanoCelda - 1.0f));
			
			celda.setPosition(sf::Vector2f(posicionX + columna * tamanoCelda,posicionY + fila * tamanoCelda));
			
			char contenido = logica.getTablero().getCelda(fila, columna);
			
			if (contenido == '\0' || contenido == '.'){
				celda.setFillColor(sf::Color(30, 30, 30));
			}
			else{
				sf::Color color;
				
				switch (contenido){
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
			
			celda.setOutlineColor(sf::Color(100, 100, 100));
			
			ventana.draw(celda);
		}
	}
}

void Visual_Tetris::Mostrar_ColaPiezas(){
	const float posicionColaY = posicionY + altoTablero + 40.0f;
	
	for (int i = 0; i < 3; i++){
		char tipo = logica.getPiezaSiguiente(i);
		
		if (tipo == '\0'){
			continue;
		}
		
		PiezaTetris pieza(tipo);
		float posicionPiezaX =245.0f + i * 155.0f;
		Mostrar_Pieza(pieza,posicionPiezaX,posicionColaY);
	}
}

void Visual_Tetris::Mostrar_Pieza(PiezaTetris& pieza,float x,float y){
	const float tamanoPieza = 15.0f;
	const float tamanoEspacio = 70.0f;
	
	sf::Color color;
	
	switch (pieza.getTipo()){
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
	
	for (int fila = 0; fila < 4; fila++){
		for (int columna = 0; columna < 4; columna++){
			if (pieza.getCelda(fila, columna) == pieza.getTipo()){
				if (fila < filaMinima){
					filaMinima = fila;
				}
				
				if (fila > filaMaxima){
					filaMaxima = fila;
				}
				
				if (columna < columnaMinima){
					columnaMinima = columna;
				}
				
				if (columna > columnaMaxima){
					columnaMaxima = columna;
				}
			}
		}
	}
	
	float anchoFigura =(columnaMaxima - columnaMinima + 1)* tamanoPieza;
	
	float altoFigura =(filaMaxima - filaMinima + 1)* tamanoPieza;
	
	float inicioX = x + (tamanoEspacio - anchoFigura) / 2.0f;
	
	float inicioY = y + (tamanoEspacio - altoFigura) / 2.0f;
	
	for (int fila = 0; fila < 4; fila++){
		for (int columna = 0; columna < 4; columna++){
			char celda = pieza.getCelda(fila, columna);
			
			if (celda != pieza.getTipo()){
				continue;
			}
			
			sf::RectangleShape bloque;
			
			bloque.setSize(sf::Vector2f(tamanoPieza - 1.0f,tamanoPieza - 1.0f));
			
			bloque.setPosition(sf::Vector2f(inicioX +(columna - columnaMinima)* tamanoPieza,inicioY +(fila - filaMinima)* tamanoPieza));
			
			bloque.setFillColor(color);
			
			bloque.setOutlineThickness(1.0f);
			
			bloque.setOutlineColor(sf::Color::White);
			
			ventana.draw(bloque);
		}
	}
}

void Visual_Tetris::Mostrar_PiezaActual(){
	char tipo = logica.getPiezaActual();
	
	if (tipo == '\0'){
		return;
	}
	
	int filaPieza = logica.getFilaPieza();
	int columnaPieza = logica.getColumnaPieza();
	
	sf::Color color;
	
	switch (tipo){
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
	
	for (int fila = 0; fila < 4; fila++){
		for (int columna = 0; columna < 4; columna++){
			char celda =
				logica.getCeldaPiezaActual(fila, columna);
			
			if (celda != tipo){
				continue;
			}
			
			sf::RectangleShape bloque;
			
			bloque.setSize(sf::Vector2f(tamanoCelda - 1.0f,tamanoCelda - 1.0f));
			
			bloque.setPosition(sf::Vector2f(posicionX +(columnaPieza + columna) * tamanoCelda,posicionY +(filaPieza + fila) * tamanoCelda));
			
			bloque.setFillColor(color);
			
			bloque.setOutlineThickness(1.0f);
			
			bloque.setOutlineColor(sf::Color::White);
			
			ventana.draw(bloque);
		}
	}
}
void Visual_Tetris::Mostrar_Puntaje(){
	
	sf::Text texto(fuente, "PUNTAJE: " + std::to_string(logica.getPuntaje()), 24);
	
	texto.setPosition(sf::Vector2f(30.0f, 30.0f));
	
	texto.setFillColor(sf::Color::White);
	
	ventana.draw(texto);
}
void Visual_Tetris::Mostrar_Tiempo(){
	
	int segundos;
	
	if (logica.getGame_Over()){
		segundos = tiempoFinal;
	}
	else if (estado == PAUSA){
		segundos = static_cast<int>(tiempo_Acumulado.asSeconds());
	}
	else{
		sf::Time tiempoActual = tiempo_Acumulado + Tiempo_Juego.getElapsedTime();
		
		segundos = static_cast<int>(tiempoActual.asSeconds());
		
		tiempoFinal = segundos;
	}
	
	int minutos = segundos / 60;
	int segundosRestantes = segundos % 60;
	
	string tiempo = "TIEMPO: " + to_string(minutos) + ":";
	
	if (segundosRestantes < 10){
		tiempo += "0";
	}
	
	tiempo += to_string(segundosRestantes);
	
	sf::Text texto(fuente, tiempo, 24);
	
	texto.setPosition(sf::Vector2f(620.0f, 30.0f));
	
	texto.setFillColor(sf::Color::White);
	
	ventana.draw(texto);
}

void Visual_Tetris::Mostrar_Bomba(){
	if (!logica.getBombaActiva()){
		return;
	}
	
	int fila = logica.getFilaBomba();
	int columna = logica.getColumnaBomba();
	
	float x = posicionX + columna * tamanoCelda;
	float y = posicionY + fila * tamanoCelda;
	
	sf::CircleShape bomba(tamanoCelda / 2.5f);
	
	bomba.setPosition(sf::Vector2f(x + tamanoCelda / 2.0f - tamanoCelda / 2.5f,y + tamanoCelda / 2.0f - tamanoCelda / 2.5f));
	
	bomba.setFillColor(sf::Color::Red);
	
	ventana.draw(bomba);
}

void Visual_Tetris::Mostrar_Hold()
{
	sf::Text titulo(fuente, "HOLD", 20);
	
	titulo.setPosition(sf::Vector2f(125.0f, posicionY + altoTablero + 20.0f));
	
	titulo.setFillColor(sf::Color::White);
	
	ventana.draw(titulo);
	
	char tipo = logica.getPiezaEnEspera();
	
	if (tipo == '\0'){
		return;
	}
	
	PiezaTetris pieza(tipo);
	Mostrar_Pieza(pieza,125.0f,posicionY + altoTablero + 45.0f);
}

void Visual_Tetris::Mostrar_Replay(){
	Mostrar_Tablero_Replay();
	Mostrar_Pieza_Replay();
	Mostrar_Bomba_Replay();
	
	sf::Text titulo(fuente,"REPLAY",30);
	
	titulo.setPosition(sf::Vector2f(350.0f, 20.0f));
	
	ventana.draw(titulo);
	
	sf::Text instrucciones(fuente,"<- ATRAS    -> ADELANTE    ESC SALIR",18);
	
	instrucciones.setPosition( sf::Vector2f(210.0f, 500.0f));
	
	ventana.draw(instrucciones);
	
	sf::Text movimiento(fuente,"MOVIMIENTO: " + to_string(logica.getReplayMovimiento()) + " / " + to_string(logica.getReplayTotal()), 20);
	
	movimiento.setPosition(sf::Vector2f(290.0f, 540.0f));
	
	ventana.draw(movimiento);
	
	sf::Text puntaje(fuente,"PUNTAJE: " + to_string(logica.getReplayPuntaje()), 22);
	
	puntaje.setPosition(sf::Vector2f(30.0f, 30.0f));
	
	ventana.draw(puntaje);
}

void Visual_Tetris::Mostrar_Tablero_Replay(){
	for (int fila = 0; fila < 20; fila++){
		for (int columna = 0; columna < 10; columna++){
			sf::RectangleShape celda;
			
			celda.setSize(sf::Vector2f(tamanoCelda - 1.0f,tamanoCelda - 1.0f));
			
			celda.setPosition(sf::Vector2f(posicionX + columna * tamanoCelda, posicionY + fila * tamanoCelda));
			
			char contenido = logica.getReplayCeldaTablero(fila,columna);
			
			if (contenido == '\0' ||contenido == '.'){
				celda.setFillColor(sf::Color(30, 30, 30));
			}
			else{
				sf::Color color;
				
				switch (contenido){
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
			celda.setOutlineColor(sf::Color(100, 100, 100));
			ventana.draw(celda);
		}
	}
}

void Visual_Tetris::Mostrar_Pieza_Replay(){
	char tipo = logica.getReplayPieza();
	
	if (tipo == '\0')
		return;
	
	int filaPieza = logica.getReplayFilaPieza();
	
	int columnaPieza = logica.getReplayColumnaPieza();
	
	int orientacion = logica.getReplayOrientacionPieza();
	
	if (filaPieza < 0 ||columnaPieza < 0 ||orientacion < 0){
		return;
	}
	
	PiezaTetris pieza(tipo);
	
	pieza.setOrientacion(orientacion);
	
	sf::Color color;
	
	switch (tipo){
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
	
	for (int fila = 0; fila < 4; fila++){
		for (int columna = 0; columna < 4; columna++){
			if (pieza.getCelda(fila, columna) != tipo)
				continue;
			
			sf::RectangleShape bloque;
			
			bloque.setSize(sf::Vector2f(tamanoCelda - 1.0f,tamanoCelda - 1.0f));
			
			bloque.setPosition(sf::Vector2f(posicionX +(columnaPieza + columna) * tamanoCelda, posicionY + (filaPieza + fila) * tamanoCelda));
			
			bloque.setFillColor(color);
			
			bloque.setOutlineThickness(1.0f);
			
			bloque.setOutlineColor(sf::Color::White);
			
			ventana.draw(bloque);
		}
	}
}
void Visual_Tetris::Mostrar_Bomba_Replay(){
	if (!logica.getReplayBombaActiva())
    return;
	
	int fila = logica.getReplayFilaBomba();
	
	int columna = logica.getReplayColumnaBomba();
	
	if (fila < 0 || columna < 0)
	return;
	
	float x = posicionX + columna * tamanoCelda;
	
	float y = posicionY + fila * tamanoCelda;
	
	sf::CircleShape bomba(tamanoCelda / 2.5f);
	
	bomba.setPosition(sf::Vector2f(x + tamanoCelda / 2.0f - tamanoCelda / 2.5f, y + tamanoCelda / 2.0f - tamanoCelda / 2.5f));
	
	bomba.setFillColor(sf::Color::Red);
	
	ventana.draw(bomba);
}

void Visual_Tetris::Mostrar_Boton_Pausa(){
	sf::RectangleShape boton(sf::Vector2f(180.0f, 55.0f));
	
	boton.setPosition(sf::Vector2f(310.0f, 710.0f));
	
	boton.setFillColor(sf::Color(80, 80, 80));
	
	boton.setOutlineThickness(2.0f);
	
	boton.setOutlineColor(sf::Color::White);
	
	ventana.draw(boton);
	
	sf::Text texto(fuente, "PAUSAR",22);
	
	texto.setPosition( sf::Vector2f(360.0f, 725.0f));
	
	texto.setFillColor( sf::Color::White);
	
	ventana.draw(texto);
}

bool Visual_Tetris::Presionar_Pausa(const sf::Event& evento){
	if (const auto* mouse = evento.getIf<sf::Event::MouseButtonPressed>()){
		if (mouse->button == sf::Mouse::Button::Left){
			sf::Vector2i posicion = sf::Mouse::getPosition(ventana);
			
			if (posicion.x >= 310 && posicion.x <= 490 && posicion.y >= 710 && posicion.y <= 765){
				return true;
			}
		}
	}
		
	return false;
}

void Visual_Tetris::Mostrar_Pantalla_Pausa(){
	
	sf::RectangleShape fondo(sf::Vector2f(800.0f, 800.0f));
	
	fondo.setPosition(sf::Vector2f(0.0f, 0.0f));
	
	fondo.setFillColor(sf::Color(0, 0, 0, 210));
	
	ventana.draw(fondo);
	
	sf::Text titulo(fuente,"PAUSA",50);
	
	titulo.setPosition(sf::Vector2f(325.0f, 250.0f));
	
	titulo.setFillColor(sf::Color::White);
	
	ventana.draw(titulo);
	
	sf::RectangleShape boton(sf::Vector2f(220.0f, 60.0f));
	
	boton.setPosition(sf::Vector2f(290.0f, 350.0f));
	
	boton.setFillColor(sf::Color(80, 80, 80));
	
	boton.setOutlineThickness(2.0f);
	
	boton.setOutlineColor(sf::Color::White);
	
	ventana.draw(boton);
	
	sf::Text texto(fuente, "CONTINUAR",24);
	
	texto.setPosition(sf::Vector2f(335.0f, 368.0f));
	
	texto.setFillColor(sf::Color::White);
	
	ventana.draw(texto);
}

bool Visual_Tetris::Presionar_Continuar(const sf::Event& evento){
	if (const auto* mouse = evento.getIf<sf::Event::MouseButtonPressed>()){
		if (mouse->button == sf::Mouse::Button::Left){
			sf::Vector2i posicion = sf::Mouse::getPosition(ventana);
			
			if (posicion.x >= 290 && posicion.x <= 510 && posicion.y >= 350 && posicion.y <= 410){
				return true;
			}
		}
	}
		
		return false;
}
