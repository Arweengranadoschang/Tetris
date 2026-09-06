#include<iostream>
#include "Registro_Movimientos.h"

using namespace std;

int main (int argc, char *argv[]) {
	
	RegistroMovimientos registro;
	
	registro.registrarMovimiento('T', 'D');
	registro.registrarMovimiento('T', 'D');
	registro.registrarMovimiento('T', 'R');
	
	cout << "Deshaciendo:" << endl;
	
	cout << registro.deshacer() << endl;
	cout << registro.deshacer() << endl;
	cout << registro.deshacer() << endl;
	
	cout << endl;
	
	cout << "Rehaciendo:" << endl;
	
	cout << registro.rehacer() << endl;
	cout << registro.rehacer() << endl;
	cout << registro.rehacer() << endl;
	
	return 0;
	

}

