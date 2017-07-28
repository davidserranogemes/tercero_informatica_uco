#ifndef FICHERO_HPP
#define FICHERO_HPP

#include <iostream>
#include <fstream>

#include "material.hpp"
#include "mochila.hpp"
#include "moneda.hpp"
#include "cambio.hpp"

bool leerFichero(std::string nombreFich, std::vector<material> &v);

bool leerFichero(std::string nombreFich, std::vector<moneda> &v);




#endif