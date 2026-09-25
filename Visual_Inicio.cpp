#include "Visual_Inicio.h"

using namespace std;

Visual_Inicio::Visual_Inicio(sf::RenderWindow& ventana,sf::Font& fuente): ventana(ventana), fuente(fuente){
	nombreJugador = "";
}

void Visual_Inicio::mostrar(){
	sf::Text titulo(fuente, "TETRIS", 60);
	
	sf::FloatRect limitesTitulo =titulo.getLocalBounds();
	
	titulo.setOrigin(sf::Vector2f(limitesTitulo.position.x +limitesTitulo.size.x / 2.0f,limitesTitulo.position.y +limitesTitulo.size.y / 2.0f));
	
	titulo.setPosition(sf::Vector2f(400.0f, 180.0f));
	
	titulo.setFillColor(sf::Color::White);
	
	ventana.draw(titulo);
	
	sf::Text textoNombre(fuente,"Nombre:",28);
	
	textoNombre.setPosition(sf::Vector2f(220.0f, 320.0f));
	
	textoNombre.setFillColor(sf::Color::White);
	
	ventana.draw(textoNombre);
	
	sf::RectangleShape cajaNombre;
	
	cajaNombre.setSize(sf::Vector2f(300.0f, 50.0f));
	
	cajaNombre.setPosition(sf::Vector2f(370.0f, 310.0f));
	
	cajaNombre.setFillColor(sf::Color(40, 40, 40));
	
	cajaNombre.setOutlineThickness(2.0f);
	
	cajaNombre.setOutlineColor(sf::Color::White);
	
	ventana.draw(cajaNombre);
	
	sf::Text textoJugador(fuente,nombreJugador,24);
	
	textoJugador.setPosition(sf::Vector2f(385.0f, 320.0f));
	
	textoJugador.setFillColor(sf::Color::White);
	
	ventana.draw(textoJugador);
	
	sf::Text boton(fuente,"JUGAR",30);
	
	sf::FloatRect limitesBoton = boton.getLocalBounds();
	
	boton.setOrigin(sf::Vector2f(limitesBoton.position.x +limitesBoton.size.x / 2.0f,limitesBoton.position.y +limitesBoton.size.y / 2.0f));
	
	boton.setPosition(sf::Vector2f(400.0f, 450.0f));
	
	boton.setFillColor(sf::Color::Green);
	
	ventana.draw(boton);
}


void Visual_Inicio::Procesar_Evento( const sf::Event& evento){
	
	if (const auto* texto = evento.getIf<sf::Event::TextEntered>()){
		
		char caracter =
			static_cast<char>(texto->unicode);
		
		if (caracter >= 32 && caracter <= 126 && nombreJugador.length() < 15){
			nombreJugador += caracter;
		}
	}

		if (const auto* tecla =	evento.getIf<sf::Event::KeyPressed>()){
			
			if (tecla->code == sf::Keyboard::Key::Backspace){
				
				if (!nombreJugador.empty()){
					nombreJugador.pop_back();
				}
			}
		}
}


string Visual_Inicio::getNombreJugador(){
	return nombreJugador;
}

bool Visual_Inicio::Presionar_Jugar( const sf::Event& evento){
	if (const auto* mouse =	evento.getIf<sf::Event::MouseButtonPressed>()){
		if (mouse->button == sf::Mouse::Button::Left){
			sf::Vector2i posicion =	mouse->position;
			
			if (posicion.x >= 300 && posicion.x <= 500 && posicion.y >= 420 && posicion.y <= 480){
				return true;
			}
		}
	}
	return false;
}
