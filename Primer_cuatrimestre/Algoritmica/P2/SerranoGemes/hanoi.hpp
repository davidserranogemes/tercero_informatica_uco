#ifndef HANOI_HPP
#define HANOI_HPP value
#include <vector>
using std::vector;
void hanoi(int m,int i, int j,long double &result );
void hanoiVisual(int m,int i, int j, long double &result, vector<vector<int>> &anillo );
void verEstadoHanoi(vector<vector<int>> &anillo);


#endif