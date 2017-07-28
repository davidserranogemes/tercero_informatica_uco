#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cmath>

#include "funcionesMatriz.hpp"
#include <vector>
using std::vector;
//Recibe un doble puntero y le genera una matriz aleatoria de n elementos
void genMatriz(int n, vector< vector <double> > &matriz){

	srand(time(NULL));

	//Rellena la matriz con valores aleatorios
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
				matriz[i][j]=(rand()%100000+1)/10000;
				if(rand()%2){
					matriz[i][j]=matriz[i][j]*-1;
				}
		}
	}
 }


long double determinante(const vector< vector<long double> > &matriz) {
   std::vector< std::vector<long double> > m = matriz;
    long double deter = 1.0;
    unsigned int orden = m.size();

    for (unsigned int k = 0; k < orden-1; k++) {
        for (unsigned int i = k+1; i < orden; i++) {
            for (unsigned int j = k+1; j < orden; j++) {
                m[i][j] -= m[i][k]*m[k][j] / m[k][k];
            }
        }
    }
    for (unsigned int i = 0; i < orden; i++) {
        deter *= m[i][i];
    }
    return deter;
} // determinante




