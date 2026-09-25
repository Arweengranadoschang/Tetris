#ifndef VISUAL_INICIO_H
#define VISUAL_INICIO_H
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class Visual_Inicio{
	
private:
	
	sf::RenderWindow& ventana;
	sf::Font& fuente;
	
	string nombreJugador;
	
public:
	
	Visual_Inicio(sf::RenderWindow& ventana,sf::Font& fuente);
	void mostrar();
	void Procesar_Evento(const sf::Event& evento);
	string getNombreJugador();
	bool Presionar_Jugar(const sf::Event& evento);
};


#endif
