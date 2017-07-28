#ifndef FUNCIONES_MATRIZ_HPP
#define FUNCIONES_MATRIZ_HPP
#include <vector>
using std::vector;

void genMatriz(int n, vector< vector <double> > &matriz);
double determinante(int n, vector< vector < double > > &matriz);
void invermat(int n, vector< vector < double > > &a, vector< vector < double > > &ainv);
long double determinante(const vector< vector<long double> > &matriz);

#endif

