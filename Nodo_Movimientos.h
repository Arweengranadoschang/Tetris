#ifndef NODO_MOVIMIENTOS_H
#define NODO_MOVIMIENTOS_H

class NodoMovimiento{
private:
	char pieza;
	char movimiento;
	
	NodoMovimiento* anterior;
	NodoMovimiento* siguiente;
	char tablero[20][10];
	int filaPieza;
	int columnaPieza;
	int orientacionPieza;
	char piezaEnEspera;
	bool bombaActiva;
	int filaBomba;
	int columnaBomba;
	int puntaje;
	
public:
	NodoMovimiento();
	NodoMovimiento(char pieza, char movimiento);
	char getPieza();
	void setPieza(char pieza);
	char getMovimiento();
	void setMovimiento(char movimiento);
	NodoMovimiento* getAnterior();
	void setAnterior(NodoMovimiento* anterior);
	NodoMovimiento* getSiguiente();
	void setSiguiente(NodoMovimiento* siguiente);
	void guardarEstado(char tablero[20][10],int filaPieza,int columnaPieza,int orientacionPieza,char piezaEnEspera,bool bombaActiva,int filaBomba,int columnaBomba,int puntaje);
	char getCeldaTablero(int fila, int columna);
	int getFilaPieza();
	int getColumnaPieza();
	int getOrientacionPieza();
	char getPiezaEnEspera();
	bool getBombaActiva();
	int getFilaBomba();
	int getColumnaBomba();
	int getPuntaje();
};
#endif
