#include "datosFibonaci.hpp"
#include <iostream>
#include <unistd.h>

long double fibonacci(int n){

	if(n==1){
		return 1;
	}
	if(n==2){
		return 1;
	}
	return fibonacci(n-1)+fibonacci(n-2);
}
	




