#include <iostream>
#include <list>

#include "hanoi.hpp"

using std::vector;
using std::list;


void hanoi(int m,int i, int j, long double &result ){
	if(m>0){
		hanoi(m-1,i,6-i-j,result);
	//	std::cout<<"Mueve el disco "<< m <<" desde "<<i<<" a "<<j<<std::endl;
		result=result+1;
		hanoi(m-1,6-i-j,j,result);
		
	}

}
void verEstadoHanoi(vector<vector<int>> &anillo){
	int c0=0,c1=0,c2=0;
	int max=0;

	if(anillo[max].size()<anillo[1].size()){
		max=1;
	}
	if(anillo[max].size()<anillo[2].size()){
		max=2;
	}

	for(uint k=0;k<anillo[max].size();k++){
		//	std::cout<<"HOLA INIT"<<std::endl;
		//std::cout<<"  anillo 0: "<<anillo[0].size()<<"  anillo 1: "<<anillo[1].size()<<"  anillo 2: "<<anillo[2].size()<<" nesc: "<<anillo[max].size()-k<<" k: "<<k<<" max: "<<max<<std::endl;
		if(anillo[0].size()>=anillo[max].size()-k){
			
			std::cout<<"\t"<<anillo[0][c0]<<"\t";
			c0++;
		}else{
			std::cout<<"\t  \t";
		}

		if(anillo[1].size()>=anillo[max].size()-k){
			//muestra
			std::cout<<"\t"<<anillo[1][c1]<<"\t";
			c1++;
		}else{
			std::cout<<"\t  \t";
		}
		if(anillo[2].size()>=anillo[max].size()-k){
			//muestra
			std::cout<<"\t"<<anillo[2][c2]<<"\t";
			c2++;
		}else{
			std::cout<<"\t  \t";
		}
		std::cout<<std::endl;

	}
		std::cout<<"___________________________________________________________________"<<std::endl;
}

void hanoiVisual(int m,int i, int j, long double &result, vector<vector<int>> &anillo ){
	int change;
	vector<int>::iterator it;

	if(m>0){
		hanoiVisual(m-1,i,6-i-j,result,anillo);
		std::cout<<"Estado: "<<result<<std::endl<<std::endl;
		verEstadoHanoi(anillo);

		change=anillo[i-1].front();
		it=anillo[i-1].begin();
		anillo[i-1].erase(it);

		it=anillo[j-1].begin();

		anillo[j-1].insert(it, change);
		std::cout<<std::endl<<std::endl;



	//	std::cout<<"Mueve el disco "<< m <<" desde "<<i<<" a "<<j<<std::endl;
		result=result+1;

		hanoiVisual(m-1,6-i-j,j,result,anillo);
		
	}

}

/*
int main(){

	vector<vector<int>> anillo;
	anillo.resize(3);
	int m=5;
	int max=0;
	long double result=0;
	for(int i=1;i<=m;i++){
		anillo[0].push_back(i);
	}
	
	hanoiVisual(m,1,2,result,anillo);
	std::cout<<"Estado: "<<result<<std::endl;
	verEstadoHanoi(anillo);

	std::cout<<"Numero de movimientos necesarios: "<<result<<std::endl;
}
*/
