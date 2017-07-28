#include <iostream>
#include <vector>

#include "recursivoSimple.hpp"

using std::vector;
long double combinatorioRecursivoSimple(int n, int k){
	if(k>n){
		return 0;
	}
	if(k==0 or k==n){
		return 1;
	}else{
		return combinatorioRecursivoSimple(n-1, k-1) + combinatorioRecursivoSimple(n-1,k);
	}
}


long double combinatorioRecursivoTabla(int n, int k, vector<vector<long double>> & resultados){
	if(k>n){
		return 0;
	}

	if(k==0 or k==n){
		return 1;
	}else{
		if(resultados[n][k]==-1){
			resultados[n][k]=combinatorioRecursivoTabla(n-1, k-1,resultados) + combinatorioRecursivoTabla(n-1,k,resultados);
		}
		return resultados[n][k];
	}
}

long double factorial(int n){
	long double factorRes=1;

	for(int i=1;i<=n;i++){
		factorRes=factorRes*i;
	}
	//std::cout<<factorRes<<std::endl;
	return factorRes;
}

long double combinatorioNoRecursivo(int n, int k){
	if(k>n){
		return 0;
	}
	
	return (factorial(n)/(factorial(k)*factorial(n-k)));
}