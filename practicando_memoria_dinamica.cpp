#include <iostream>

using namespace std;

int main() {
	const int N = 3;
	const int n = 3;
	
	
	// Inicializacion del arreglo 3D (Cubo)
	int cubo[3][N][N] = {
		{
			{1, 2, 3},
		    {4, 5, 6},
			{7, 8, 9}
	},
	{
		{10, 11, 12},
		{13, 14, 15},
		{16, 17, 18}
	},
		{
			{19, 20, 21},
	    	{22, 23, 24},
			{25, 26, 27}
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
	for(int (*fila)[n] = cubo[0]; fila < cubo[2] ; fila++){
		
		for(int *columna = *fila; columna < *fila + n ; columna++){
			
			for(int (*cara)[n][n] = cubo; *cara < cubo[3]; cara++){
				
				cout<< *columna + n*n<<" ";
			}
		}
		cout<<endl;
	};
	
	
	return 0;
}
