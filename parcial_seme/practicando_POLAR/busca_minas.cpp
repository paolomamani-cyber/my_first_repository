// Practica 3 - Buscaminas 3D con punteros (version compacta)
// Un solo main(), un solo array dinamico, acceso solo con punteros.
#include <iostream>
using namespace std;

int main() {
	// ---------- a) Matriz 3D dinamica en UN solo array ----------
	// Orden en memoria: cara 1 (fila 1, fila 2...), cara 2, cara 3...
	int caras = 3, filas = 14, columnas = 8;     // cada cara es un bloque de 14x8
	int tamCara = filas * columnas;              // celdas por cara
	int total   = caras * tamCara;               // celdas totales
	
	int datos[] = {                              // Fig. 1 de la practica
		// Cara 1
		0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,1,0,
			0,1,0,1,0,0,0,1,
			0,1,0,1,0,0,0,0,
			0,1,1,0,0,0,0,0,
			0,0,1,0,0,0,0,0,
			0,0,0,1,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,1,
			0,0,0,0,0,0,1,0,
			0,0,0,0,0,0,1,0,
			0,0,0,0,1,1,1,0,
			0,0,0,0,0,0,0,0,
			// Cara 2
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,1,0,1,0,0,0,0,
			0,1,0,1,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,1,1,1,0,
			0,0,0,0,0,0,0,0,
			// Cara 3
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,1,0,
			0,0,0,0,0,0,0,1,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			1,0,0,0,0,0,0,1,
			1,0,0,0,0,0,1,0,
			1,0,0,0,0,0,1,0,
			1,0,0,0,1,1,1,0,
			0,0,0,0,0,0,0,0
	};
	
	int* mat = new int[total];
	int* fin = mat + total;                      // una posicion despues del final
	int* origen = datos;
	for (int* p = mat; p < fin; p++, origen++) *p = *origen;
	
	const char* sep;                             // para poner comas entre numeros
	
	// ---------- b) Imprimir toda la matriz ----------
	cout << "b) Matriz 3D:\n";
	for (int* cara = mat; cara < fin; cara += tamCara) {
		for (int* fila = cara; fila < cara + tamCara; fila += columnas) {
			for (int* p = fila; p < fila + columnas; p++) cout << *p << " ";
			cout << endl;
		}
		cout << endl;                            // linea en blanco entre caras
	}
	
	// ---------- c) Unos de la primera cara ----------
	int unos = 0;
	for (int* p = mat; p < mat + tamCara; p++) unos += *p;   // 0 o 1, se suma directo
	cout << "c) Unos en la cara 1: " << unos << endl;
	
	// ---------- d) Unos de cada cara ----------
	cout << "d) Unos por cara: ";
	sep = "";
	for (int* cara = mat; cara < fin; cara += tamCara) {
		unos = 0;
		for (int* p = cara; p < cara + tamCara; p++) unos += *p;
		cout << sep << unos;
		sep = ",";
	}
	cout << endl;
	
	// ---------- e) Minas por fila (primera cara) ----------
	// Una mina en una fila empieza donde hay un 1 y antes hay un 0 (o inicio de fila).
	// Las filas sin minas no se imprimen (como en el ejemplo de la practica).
	cout << "e) Minas por fila de la cara 1: ";
	sep = "";
	for (int* fila = mat; fila < mat + tamCara; fila += columnas) {
		int minas = 0;
		for (int* p = fila; p < fila + columnas; p++)
			if (*p == 1 && (p == fila || *(p - 1) == 0)) minas++;
		if (minas > 0) { cout << sep << minas; sep = ","; }
	}
	cout << endl;
	
	// ---------- f) Minas por fila de cada cara ----------
	cout << "f) Minas por fila de cada cara:\n";
	for (int* cara = mat; cara < fin; cara += tamCara) {
		sep = "";
		for (int* fila = cara; fila < cara + tamCara; fila += columnas) {
			int minas = 0;
			for (int* p = fila; p < fila + columnas; p++)
				if (*p == 1 && (p == fila || *(p - 1) == 0)) minas++;
			if (minas > 0) { cout << sep << minas; sep = ","; }
		}
		cout << endl;                            // una cara por renglon
	}
	
	// ---------- g), h), i) Contar grupos de unos contiguos ----------
	// Trabajamos en una copia con un BORDE de ceros alrededor, asi al mirar
	// un vecino nunca nos salimos de la matriz (el borde siempre vale 0).
	int c2     = columnas + 2;                   // ancho con borde
	int tam2   = (filas + 2) * c2;               // celdas por cara con borde
	int total2 = (caras + 2) * tam2;
	int* copia = new int[total2]();              // () la llena de ceros
	
	int** pila = new int*[total2];               // pila de punteros pendientes de revisar
	int*  minasCara = new int[caras + 2]();      // minas por cara (se usa de la 1 a la ultima)
	int   minas3D = 0;                           // minas de toda la matriz
	
	// Pasada 0: vecinos solo dentro de la cara (2D)  -> minas de cada cara
	// Pasada 1: vecinos tambien en caras contiguas   -> minas de toda la matriz
	// En ambos casos los vecinos incluyen las diagonales (como en la Fig. 1).
	for (int pasada = 0; pasada < 2; pasada++) {
		int dzMax = (pasada == 0) ? 0 : 1;       // 0: no cambia de cara, 1: cara anterior/siguiente
		
		// Copiar la matriz dentro de 'copia' (se rehace porque vamos borrando unos)
		origen = mat;
		for (int* cara = copia + tam2; cara < copia + tam2 * (caras + 1); cara += tam2)
			for (int* fila = cara + c2; fila < cara + c2 * (filas + 1); fila += c2)
				for (int* p = fila + 1; p < fila + 1 + columnas; p++, origen++)
					*p = *origen;
		
		// Recorrer toda la copia buscando un 1 (= mina nueva)
		for (int* celda = copia; celda < copia + total2; celda++) {
			if (*celda == 1) {
				if (pasada == 0) (*(minasCara + (celda - copia) / tam2))++;  // cara a la que pertenece
				else             minas3D++;
				
				// Borrar toda la mina "pintando" sus vecinos con una pila
				int** tope = pila;               // pila vacia
				*celda = 0;
				*tope = celda; tope++;           // apilar
				while (tope > pila) {
					tope--;                      // desapilar
					int* actual = *tope;
					for (int dz = -dzMax; dz <= dzMax; dz++)        // cara
						for (int dy = -1; dy <= 1; dy++)            // fila
							for (int dx = -1; dx <= 1; dx++) {      // columna
								int* vecino = actual + dz * tam2 + dy * c2 + dx;
								if (*vecino == 1) {  // vecino con mineral: misma mina
									*vecino = 0;
									*tope = vecino; tope++;
								}
					}
				}
			}
		}
	}
	
	cout << "g) Minas de la cara 1: " << *(minasCara + 1) << endl;
	
	cout << "h) Minas por cara: ";
	sep = "";
	for (int* p = minasCara + 1; p <= minasCara + caras; p++) {
		cout << sep << *p;
		sep = ",";
	}
	cout << endl;
	
	cout << "i) Minas en toda la matriz: " << minas3D << endl;
	
	// ---------- Liberar memoria ----------
	delete[] mat;
	delete[] copia;
	delete[] pila;
	delete[] minasCara;
	return 0;
}