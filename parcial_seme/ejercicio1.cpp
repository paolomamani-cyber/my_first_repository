#include <iostream>
using namespace std;

int main() {
	int fila = 3;
	int colum = 4;
	const int n = 3;
	int **A = new int*[fila];
	
	int contador = 1;
	for(int **p = A; p < A + fila; p++){
		*p = new int[colum];
		for(int *q = *p; q < *p + colum; q++){
			*q = contador++;
		}
	}
	
	for(int **p = A; p < A + fila; p++){
		for(int *q = *p; q < *p + colum; q++){
			cout<<*q<<" ";
		}
		cout<<endl;
	}
	
	cout<< endl; //////////////////////////////////////////CON WHILE
	
	
	for(int **p = A; p < A + fila; p++){
		
		for(int *q = *p; q < *p + colum; q++){
			int a = 0;
			while(a < n){
				cout<<*q;
				a++;
			}
			
		}
	}
	
	cout<< endl; ////////////////////////////////////////////CON FOR
	cout<< endl;
	
	
	for(int **p = A; p < A + fila; p++){
		
		for(int *q = *p; q < *p + colum; q++){
			
			for (int i = 0; i < n; i++){
				cout<<*q;
			}
			
		}
	}
	
	
	for(int **p = A; p < A + fila; p++){
		
			delete[]*p;

	}
	delete A;
	
	return 0;
}
