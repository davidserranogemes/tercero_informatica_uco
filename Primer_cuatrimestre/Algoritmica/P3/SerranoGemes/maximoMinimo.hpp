#ifndef MAXIMOMINIMO_HPP
#define MAXIMOMINIMO_HPP

#include "Conjunto.hpp"


template <class T>
void maxMinIter(Conjunto<T> &c,T &max, T &min, uint &numComp){
	T curr=0;
	max=c.at(0);
	min=c.at(0);
	
	for(int i=1;i<c.size();i++){
		curr=c.at(i);

		numComp++;
		if(curr>max){
			max=curr;
		}
		numComp++;
		if(curr<min){
			min=curr;
		}
	}
}

template <class T>
void maxMinDivVen(Conjunto<T> &c,int i, int j, T &max, T &min,uint &numComp){		//void Conjunto<T>::maxMinDivVen(int i, int j, T &max, T &min){
	int mitad;
	T min1,min2;
	T max1, max2;

	numComp++;
	if( i==j){
		max=c.at(i);
		min=c.at(j);

	}else{
		numComp++;
		if(i == (j-1)){
			numComp++;
			if(c.at(i)>c.at(j)){
				max=c.at(i);
				min=c.at(j);
			}else{
				max=c.at(j);
				min=c.at(i);
			}
		}else{
			mitad=(i+j)/2;
			maxMinDivVen(c,i,mitad,max1, min1,numComp);
			maxMinDivVen(c,mitad+1,j,max2,min2,numComp);
			numComp++;
			if(max1>max2){
				max=max1;
			}else{
				max=max2;
			}
			numComp++;
			if(min1<min2){
				min=min1;
			}else{
				min=min2;
			}
					//std::cout<<"MAX: "<<max<<" MIN: "<<min<<std::endl;
		}	
	}
}

#endif