#include <iostream>

using namespace std;

int main() {
	const int N = 3;
	const int n = 3;
	
	
	// Inicializacion del arreglo 3D (Cubo)
	int cubo[3][N][N] = {
		{
			{0, 1, 2},
		    {1, 2, 0},
			{2, 0, 1}
	},
	{
		{1, 2, 0},
	    {2, 0, 1},
		{0, 1, 2}
	},
		{
			{2, 0, 1},
		    {0, 1, 2},
			{1, 2, 0}
		}
	};
	
	// --- IMPRESION DEL CUBO COMPLETO ---
	cout << "--- Contenido del Array 3D (Cara por Cara) ---" << endl;
	
	for (int *p = **cubo, *fin = **cubo + (N * N * N); p < fin; ) {
		cout << *p << " ";
		p++;
		if ((p - **cubo) % N == 0) {
			cout << endl;
		}
		if ((p - **cubo) % (N * N) == 0) {
			cout << "--------------------" << endl;
		}
	}
	
	// --- IMPRESION DE BLOQUES EN PROFUNDIDAD ---
	cout << "\n--- BLOQUES EN PROFUNDIDAD ---" << endl;
	
	// Completar:
	for(int (*fila)[n] = cubo[0]; fila < cubo[0] + n; fila++){
		
		for(int *columna = *fila; columna < *fila + n; columna++){
			
			for(int *profundidad = columna; profundidad < **cubo + (N*N*N); profundidad += N*N){
				cout << *profundidad << " ";
			}
			cout << endl; // un bloque (una línea) por cada par fila-columna
		}
	}
	
	
	return 0;
}
