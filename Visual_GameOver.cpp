#include "Visual_GameOver.h"

using namespace std;

Visual_GameOver::Visual_GameOver(sf::RenderWindow& ventana,sf::Font& fuente,  TablaPuntajes& tablaPuntajes): ventana(ventana), fuente(fuente), tablaPuntajes(tablaPuntajes){
	nombreJugador = "";
	puntaje = 0;
	Mostrar_Tabla = false;
	Algoritmo_Usado = "";
	tiempo_Ordenamiento = 0.0;	
}

void Visual_GameOver::Datos( string nombre, int puntaje){
	nombreJugador = nombre;
	this->puntaje = puntaje;
}
void Visual_GameOver::mostrar()
{
	ventana.clear(sf::Color::Black);
	

	sf::Text textoGameOver(fuente, "GAME OVER", 60);
	textoGameOver.setFillColor(sf::Color::Red);
	textoGameOver.setPosition(sf::Vector2f(260.0f, 100.0f));
	
	ventana.draw(textoGameOver);
	
	sf::Text textoJugador(fuente,"JUGADOR: " + nombreJugador,30);
	
	textoJugador.setPosition(sf::Vector2f(250.0f, 220.0f));
	
	ventana.draw(textoJugador);
	
	sf::Text textoPuntaje(fuente, "PUNTAJE: " + to_string(puntaje), 30);
	
	textoPuntaje.setPosition(sf::Vector2f(250.0f, 270.0f));
	
	ventana.draw(textoPuntaje);
	
	sf::RectangleShape botonQuickSort(sf::Vector2f(220.0f, 60.0f));
	
	botonQuickSort.setPosition(sf::Vector2f(160.0f, 360.0f));
	
	botonQuickSort.setFillColor(sf::Color(80, 80, 80));
	
	ventana.draw(botonQuickSort);
	
	sf::Text textoQuickSort(fuente,"QUICK SORT",24);
	
	textoQuickSort.setPosition(sf::Vector2f(205.0f, 378.0f));
	
	ventana.draw(textoQuickSort);
	
	sf::RectangleShape botonInsercion(sf::Vector2f(220.0f, 60.0f));
	
	botonInsercion.setPosition(sf::Vector2f(420.0f, 360.0f));
	
	botonInsercion.setFillColor(sf::Color(80, 80, 80));
	
	ventana.draw(botonInsercion);
	
	sf::Text textoInsercion(fuente,"INSERCION",24);
	
	textoInsercion.setPosition(sf::Vector2f(475.0f, 378.0f));
	
	ventana.draw(textoInsercion);
	
	sf::RectangleShape botonReiniciar(sf::Vector2f(220.0f, 60.0f));
	
	botonReiniciar.setPosition(sf::Vector2f(290.0f, 520.0f));
	
	botonReiniciar.setFillColor(sf::Color(80, 80, 80));
	
	ventana.draw(botonReiniciar);
	
	sf::Text textoReiniciar(fuente,"REINICIAR",24);
	
	textoReiniciar.setPosition(sf::Vector2f(350.0f,  538.0f));
	
	ventana.draw(textoReiniciar);
	
	sf::RectangleShape botonSalir(sf::Vector2f(220.0f, 60.0f));
	
	botonSalir.setPosition(sf::Vector2f(290.0f, 620.0f));
	
	botonSalir.setFillColor(sf::Color(80, 80, 80));
	
	ventana.draw(botonSalir);
	
	sf::Text textoSalir(fuente,"SALIR",24);
	
	textoSalir.setPosition(sf::Vector2f(365.0f, 638.0f));
	
	ventana.draw(textoSalir);
	
	sf::RectangleShape botonReplay(sf::Vector2f(220.0f, 60.0f));
	
	botonReplay.setPosition(sf::Vector2f(290.0f, 440.0f));
	
	botonReplay.setFillColor( sf::Color(80, 80, 80));
	
	ventana.draw(botonReplay);
	
	sf::Text textoReplay(fuente,"REPLAY", 24);
	
	textoReplay.setPosition(sf::Vector2f(360.0f, 458.0f));
	
	ventana.draw(textoReplay);
	
	if (Mostrar_Tabla){
		
		sf::RectangleShape fondo( sf::Vector2f(800.0f, 800.0f) );
		
		fondo.setPosition(sf::Vector2f(0.0f, 0.0f));
		fondo.setFillColor(sf::Color(0, 0, 0, 230));
		
		ventana.draw(fondo);
		
		sf::RectangleShape panel(sf::Vector2f(600.0f, 650.0f));
		
		panel.setPosition(sf::Vector2f(100.0f, 70.0f));
		
		panel.setFillColor(sf::Color(40, 40, 40));
		
		ventana.draw(panel);
		
		sf::Text titulo(fuente,"TOP 10",45);
		
		titulo.setPosition(sf::Vector2f(330.0f, 90.0f));
		
		ventana.draw(titulo);
		
		sf::Text algoritmo(fuente,"ORDENADO CON: " + Algoritmo_Usado,22);
		
		algoritmo.setPosition(sf::Vector2f(235.0f, 150.0f));
		
		ventana.draw(algoritmo);
		
		string tiempo = "TIEMPO: " + to_string(tiempo_Ordenamiento) + " segundos";
		
		sf::Text textoTiempo(fuente, tiempo, 20);
		
		textoTiempo.setPosition(sf::Vector2f(280.0f, 175.0f));
		
		ventana.draw(textoTiempo);
		
		sf::Text encabezadoPosicion(fuente,"POS",20);
		
		encabezadoPosicion.setPosition(sf::Vector2f(150.0f, 200.0f));
		
		ventana.draw(encabezadoPosicion);
		
		sf::Text encabezadoNombre(fuente,"JUGADOR",20);
		
		encabezadoNombre.setPosition(sf::Vector2f(250.0f, 200.0f));
		
		ventana.draw(encabezadoNombre);
		
		sf::Text encabezadoPuntaje(fuente,"PUNTAJE",20);
		
		encabezadoPuntaje.setPosition(sf::Vector2f(500.0f, 200.0f) );
		
		ventana.draw(encabezadoPuntaje);
		
		
		for (int i = 0; i < tablaPuntajes.getCantidad(); i++){
			sf::Text posicion(fuente,to_string(i + 1),20);
			
			posicion.setPosition(sf::Vector2f(160.0f, 240.0f + i * 35.0f));
			
			ventana.draw(posicion);
			
			sf::Text nombre(fuente,tablaPuntajes.getNombre(i),20);
			
			nombre.setPosition(sf::Vector2f(250.0f, 240.0f + i * 35.0f));
			
			ventana.draw(nombre);
			
			sf::Text puntos(fuente,to_string(tablaPuntajes.getPuntaje(i)),20);
			
			puntos.setPosition(sf::Vector2f(520.0f, 240.0f + i * 35.0f));
			
			ventana.draw(puntos);
		}
		
		sf::RectangleShape botonCerrar(sf::Vector2f(180.0f, 55.0f) );
		
		botonCerrar.setPosition(sf::Vector2f(310.0f, 620.0f));
		
		botonCerrar.setFillColor(sf::Color(80, 80, 80));
		
		ventana.draw(botonCerrar);
		
		sf::Text textoCerrar(fuente,"CERRAR",22);
		
		textoCerrar.setPosition(sf::Vector2f(360.0f, 636.0f));
		
		ventana.draw(textoCerrar);
	}
	
}



bool Visual_GameOver::Presionar_Reiniciar(const sf::Event& evento){
	if (const auto* mouse =	evento.getIf<sf::Event::MouseButtonPressed>()){
		if (mouse->button == sf::Mouse::Button::Left){
			sf::Vector2i posicion = sf::Mouse::getPosition(ventana);
			
			if (posicion.x >= 290 && posicion.x <= 510 && posicion.y >= 520 && posicion.y <= 580){
				return true;
			}
		}
	}
		
		return false;
}

bool Visual_GameOver::Presionar_Salir(const sf::Event& evento){
	if (const auto* mouse = evento.getIf<sf::Event::MouseButtonPressed>()){
		if (mouse->button == sf::Mouse::Button::Left){
			sf::Vector2i posicion = sf::Mouse::getPosition(ventana);
			
			if (posicion.x >= 290 && posicion.x <= 510 && posicion.y >= 620 && posicion.y <= 680){
				return true;
			}
		}
	}
	return false;
}




bool Visual_GameOver::Presionar_QuickSort(const sf::Event& evento){
	if (const auto* mouse = evento.getIf<sf::Event::MouseButtonPressed>()){
		if (mouse->button == sf::Mouse::Button::Left){
			sf::Vector2i posicion = sf::Mouse::getPosition(ventana);
			
			if (posicion.x >= 160 && posicion.x <= 380 && posicion.y >= 360 && posicion.y <= 420){
				return true;
			}
		}
	}
	
	return false;
}

bool Visual_GameOver::Presionar_Insercion(const sf::Event& evento){
	
	if (const auto* mouse = evento.getIf<sf::Event::MouseButtonPressed>()){
		if (mouse->button == sf::Mouse::Button::Left){
			sf::Vector2i posicion = sf::Mouse::getPosition(ventana);
			
			if (posicion.x >= 420 && posicion.x <= 640 && posicion.y >= 360 && posicion.y <= 420){
				return true;
			}
		}
	}
	
	return false;
}
void Visual_GameOver::Ventana_Top10(const string& algoritmo){
	Mostrar_Tabla = true;
	Algoritmo_Usado = algoritmo;
	
	if (algoritmo == "QUICK SORT"){
		tiempo_Ordenamiento = tablaPuntajes.getTiempoQuickSort();
	}
	else if (algoritmo == "INSERCION"){
		tiempo_Ordenamiento = tablaPuntajes.getTiempoInsercion();
	}
}

bool Visual_GameOver::Presionar_Cerrar(const sf::Event& evento){
	
	if (!Mostrar_Tabla)
		return false;
	
	if (const auto* mouse = evento.getIf<sf::Event::MouseButtonPressed>()){
		if (mouse->button == sf::Mouse::Button::Left){
			sf::Vector2i posicion = sf::Mouse::getPosition(ventana);
			
			if (posicion.x >= 310 && posicion.x <= 490 && posicion.y >= 620 && posicion.y <= 675){
				Mostrar_Tabla = false;
				Algoritmo_Usado = "";
				
				return true;
			}
		}
	}
	return false;
}

bool Visual_GameOver::Presionar_Replay( const sf::Event& evento){
	if (Mostrar_Tabla)
		return false;
	
	if (const auto* mouse = evento.getIf<sf::Event::MouseButtonPressed>()){
		if (mouse->button == sf::Mouse::Button::Left){
			sf::Vector2i posicion = sf::Mouse::getPosition(ventana);
			
			if (posicion.x >= 290 && posicion.x <= 510 && posicion.y >= 440 && posicion.y <= 500)
			{
				return true;
			}
		}
	}
		
		return false;
}
