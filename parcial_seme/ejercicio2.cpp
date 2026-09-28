#include <iostream>
using namespace std;

int main() {
	const int fila = 4;
	const int colum = 4;
	
	int datos[fila][colum] =
	{
		{3,1,5,9},
	    {2,1,6,10},
		{2,4,7,11},
	    {3,4,8,11}
	};
	
	int **A = new int*[fila];
	int *d = &datos[0][0];
	
	for(int **p = A; p < A + fila; p++){ ///////////////////////////LLENADO DE INFORMACION
		*p = new int[colum];
		for(int *q = *p; q < *p + colum; q++){
			*q = *d;
			d++;
		}
	}
	
	for(int **p = A; p < A + fila; p++){///////////////////////////IMPRESION DE INFROMACION
		for(int *q = *p; q < *p + colum; q++){
			cout<<*q<<" ";
		}
		cout<<endl;
	}
	
	cout<<endl;
	
	for(int **p = A; p < A + fila; p++){///////////////////////////IMPRESION DE SEGUNDA COLUMNA
		for(int *q = *p + 1; q < *p + colum; q+=4){
			cout<<*q<<" ";
		}
		/*cout<<endl;*/
	}
	
	
	
	
	for(int **p = A; p < A + fila; p++){
		delete[]*p;
	}
	delete []A;
	
	return 0;
}
