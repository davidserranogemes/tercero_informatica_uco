#include <iostream>

#include "Conjunto.hpp"
/*
template <class T>
void Conjunto<T>::maxMinDivVen(int i, int j, T &max, T &min){
	int mitad;
	T min1,min2;
	T max1, max2;

	if( i==j){
		max=at(i);
		min=at(j);
	}else{
		if(i == (j-1)){
			if(at(i)>at(j)){
				max=at(i);
				min=at(j);
			}else{
				max=at(j);
				min=at(i);
			}
		}else{
			mitad=(i+j)/2;
			maxMinDivVen(i,mitad,max1, min1);
			maxMinDivVen(mitad+1,j,max2,min2);

			if(max1>max2){
				max=max1;
			}else{
				max=max2;
			}
			if(min1<min2){
				min=min1;
			}else{
				min=min2;
			}
		}	
	}

}
*/
//template class Conjunto<int>;