#ifndef FUNCIONESFICHERO_HPP
#define FUNCIONESFICHERO_HPP
#include <string>
#include <list>

struct tiempoUsado{
	int valor; ///El valor n no el resultado
	long double tiempo;
	long double tiempoEstimado; //Si no se usa este parametro ponerlo a -1

};

std::list<struct tiempoUsado> leerFichero(std::string nombreFichero);
void escribirFichero(std::list<struct tiempoUsado> listaTiempos,std::string nombreFichero);

#endif