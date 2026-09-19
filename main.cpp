#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main(int argc, char *argv[])
{
	sf::RenderWindow ventana( sf::VideoMode({800, 600}), "Tetris - Prueba SFML" );
	
	while (ventana.isOpen()) {
		while (auto evento = ventana.pollEvent()) {
			if (evento->is<sf::Event::Closed>()) {
				ventana.close(); 
			} 
		}
	}
	ventana.clear(); 
	ventana.display();
}


