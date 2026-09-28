#include <iostream>
using namespace std;

int main() {
	const int fila = 8;
	const int colum = 8;
	
	int datos[fila][colum] = {
		{0, 0, 0, 0, 2, 0, 0, 0},
	    {0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
	    {1, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
	    {0, 1, 0, 0, 1, 0, 0, 1}
	};
	
	int **A = new int*[fila];
	int *d = &datos[0][0];
	
	// Reservar y copiar
	for (int **p = A; p < A + fila; p++) {
		*p = new int[colum];
		for (int *q = *p; q < *p + colum; q++) {
			*q = *d;
			d++;
		}
	}
	
	// Mostrar tablero
	for (int **p = A; p < A + fila; p++) {
		for (int *q = *p; q < *p + colum; q++) {
			cout << *q << " ";
		}
		cout << endl;
	}
	
	// <A Completar>
	bool torre = false;
	bool enemigo_fila = false;
	bool enemigo_colum = false; 
	
	int *Torrefila = NULL;
	int desp = 0;
	
	for (int **p = A; p < A + fila; p++) {
		for (int *q = *p; q < *p + colum; q++) {
			if(*q == 2){
				torre = true;
				Torrefila = *p;
				desp = q - *p;
				
			}
		}
	}
	
	if(torre){
		for(int *q = Torrefila; q < Torrefila + colum; q++){
			if(*q == 1)enemigo_fila = true;
		}
		
		for(int **p = A; p < A + fila; p++){
			if(*(*p + desp) == 1) enemigo_colum = true;
		}
	}
	
	
	if(enemigo_fila ||  enemigo_colum) cout<<"ATAQUE";
	else {cout<<"Sin Ataque";}
	
	
	
	// Liberar memoria
	for (int **p = A; p < A + fila; p++) {
		delete[] *p;
	}
	delete[] A;
	
	return 0;
}