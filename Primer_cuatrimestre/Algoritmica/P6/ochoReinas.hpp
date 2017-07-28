#ifndef OCHOREINAS_HPP
#define OCHOREINAS_HPP

#include <vector>


bool lugar(int k, std::vector <int> x);
void ochoReinasBacktracking(int n, std::vector<std::vector<int>> &soluciones);
bool ochoReinasVegas(int n, std::vector<int> &solucion);
void mostrarSoluciones(std::vector<std::vector<int>> &soluciones);
int num_aleatorio(const uint &lim_inf, const uint &lim_sup);
bool insertSolucionUnica(std::vector<std::vector<int>> &soluciones,std::vector<int> &solucion);


#endif