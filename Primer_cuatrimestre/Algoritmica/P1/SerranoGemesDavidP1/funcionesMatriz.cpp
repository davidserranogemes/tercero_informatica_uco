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

double determinante(int n, vector< vector < double > > &a){

int i, j, k;
double determ;

  double factor;

  vector <vector < double > > L;
  
  L.resize(n);
  for(int i=0;i<n;i++){
  for(int j=0; j<n;j++){
    std::cout<<"["<<a[i][j]<<"]";
  }
  std::cout<<std::endl;
}
  
  for (j = 0; j < n; j++) 

    L[j].resize(n);

  for (k = 0; k < n - 1; k++) {
    
    for (i = k+1; i < n;  i++) {

      factor = a[i][k]/a[k][k]; 
      std::cout<<"Factor: "<<factor<<std::endl;

      for (j = k+1; j < n; j++) {

        a[i][j] = a[i][j] - factor * a[k][j];

      }
    }
  }

// Cálculo del determinante

        determ = 1.;

  for (i = 0; i < n; i++) {
    std::cout<<determ<<" *  "<<a[i][i]<<std::endl;
    determ = determ * a[i][i];
    std::cout<<"determ: "<<determ<<"   i:  "<<i<<std::endl;
}
 return determ;
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








/*
long double determinante(int n,vector< vector < long double > > &a){

int i, j, k;
long double determ;

 long double factor;

  vector< vector < long double > > L;
  

  L.resize(n);
for(int i=0;i<n;i++){
  for(int j=0; j<n;j++){
    std::cout<<"["<<a[i][j]<<"]";
  }
  std::cout<<std::endl;
}

  
  for (j = 0; j < n; j++) 

    L[j].resize(n);

  for (k = 0; k < n - 1; k++) {
    
    for (i = k+1; i < n;  i++) {

      factor = a[i][k]/a[k][k]; 
      std::cout<<"Factor: "<<factor<<" K: "<<k<<" I: "<<i<<" J: "<<j<<std::endl;

      for (j = k+1; j < n ; j++) {

        a[i][j] = a[i][j] - factor * a[k][j];

      }
    


    }

  }

  for(int i=0;i<n;i++){
  for(int j=0; j<n;j++){
    std::cout<<"["<<a[i][j]<<"]";
  }
  std::cout<<std::endl;
}

// Cálculo del determinante

        determ = 1.;

  for (i = 0; i < n; i++) {
 std::cout<<determ<<" *  "<<a[i][i]<<std::endl;
    determ = determ * a[i][i];
    std::cout<<"determ: "<<determ<<"   i:  "<<i<<std::endl;

  }

 return determ;
}


*/

void invermat(int n, vector< vector < double > > &a, vector< vector < double > > &ainv){

int i, j, k;

  double factor;

  vector< vector <double> > L;
  vector <double> D, X;
  double determ;

  X.resize(n);
  D.resize(n);

  L.resize(n);
  
  for (j = 0; j < n; j++) 

    L[j].resize(n);

  for (k = 0; k < n - 1; k++) {
    
    for (i = k+1; i < n;  i++) {

      factor = a[i][k]/a[k][k]; 

      for (j = k+1; j < n ; j++) {
        a[i][j] = a[i][j] - factor * a[k][j];

      }
    


    }

  }

// Cálculo del determinante

        determ = 1.0;

	for (i = 0; i < n; i++) {

		determ = determ * a[i][i];

	}

if (determ != 0) {

// Rutina para determinar las matrices L (inferior) y U (superior) de la 
// descomposición LU


        for (i = 0; i < n; i++) {

               for (j = 0; j < n; j++) {

                  if (i > j) {
     
                      L[i][j] = a[i][j]/a[j][j];

                      a[i][j] = 0;

                   }


               }

        }


       for (i = 0; i < n; i++) {

            for (j = 0; j < n; j++) {

                  L[j][j] = 1;

            }

        }

//std::cout<<"Determinante hecho ."<<std::endl;
// Implementación de la rutina para el cálculo de la inversa


 for (k = 0; k < n; k++) {


// Esta rutina inicializa los L[i][n] para ser utilizados con la matriz L


          for (i = 0; i < n; i++) {

               if (i == k){
               	 L[i][n-1] = 1;
               }else{
               		 L[i][n-1] = 0;
               	}

           }

// Esta función implementa la sustitución hacia adelante con la matriz L y los L[i][n]
// que produce la rutina anterior

  double sum;

  D[0] = L[0][n-1];

  for (i = 1; i < n; i++) {

       sum = 0;

       for (j = 0; j < i; j++) {

            sum = sum + L[i][j]*D[j];

       }

        D[i] = L[i][n-1] - sum;

   }



// Esta rutina asigna los D[i] que produce forward para ser utilizados con la matriz U

  for (i = 0; i < n; i++) {

          a[i][n-1] = D[i];

  }

// Rutina que aplica la sustitución hacia atras


 X[n-1] = a[n-2][n-1]/a[n-1][n-1];

 // Determinación de las raíces restantes


  for (i = n - 2; i > -1; i--) {

        sum = 0;

        for (j = i+1; j < n; j++) {

              sum = sum + a[i][j]*X[j];

         }

         X[i] = (a[i][n-1] - sum)/a[i][i];

   }


// Esta rutina asigna los X[i] que produce Sustituir como los elementos de la matriz inversa

  for (i = 0; i < n; i++) {

         ainv[i][k] = X[i];

  }

 }   // llave de cierre del for para k
  //std::cout<<"Acabo."<<std::endl;

} else{
	std::cout<<"No tiene inversa, menudo atino tienes, ve ha jugar a la loteria o algo."<<std::endl;
  } // cierre del if
}


