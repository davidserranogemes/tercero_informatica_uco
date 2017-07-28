CC= g++
EXE= pPrincipal
FLAGS= -c -g -ansi -Wall -Wextra -std=c++11

pPrincipal: pPrincipal.o ClaseTiempo.o funcionesFichero.o funcionesMatriz.o minimosCuadradosPolinomico.o minimosCuadrados2n.o recursivoSimple.o datosEstimadosPolinomio.o datosEstimados2n.o hanoi.o
	$(CC) pPrincipal.o ClaseTiempo.o funcionesFichero.o funcionesMatriz.o minimosCuadradosPolinomico.o minimosCuadrados2n.o recursivoSimple.o datosEstimadosPolinomio.o datosEstimados2n.o hanoi.o -o pPrincipal
ClaseTiempo.o: ClaseTiempo.cpp ClaseTiempo.hpp
	$(CC) ClaseTiempo.cpp $(FLAGS) -o ClaseTiempo.o
funcionesFichero.o: funcionesFichero.cpp funcionesFichero.hpp
	$(CC) funcionesFichero.cpp $(FLAGS) -o funcionesFichero.o
funcionesMatriz.o: funcionesMatriz.cpp  funcionesMatriz.hpp
	$(CC) funcionesMatriz.cpp $(FLAGS) -o funcionesMatriz.o
minimosCuadradosPolinomico.o: minimosCuadradosPolinomico.cpp minimosCuadradosPolinomico.hpp funcionesMatriz.hpp funcionesFichero.hpp
	$(CC) minimosCuadradosPolinomico.cpp $(FLAGS) -o minimosCuadradosPolinomico.o
minimosCuadrados2n.o: minimosCuadrados2n.cpp minimosCuadrados2n.hpp funcionesMatriz.hpp funcionesFichero.hpp
	$(CC) minimosCuadrados2n.cpp $(FLAGS) -o minimosCuadrados2n.o
recursivoSimple.o: recursivoSimple.cpp recursivoSimple.hpp
	$(CC) recursivoSimple.cpp $(FLAGS) -o recursivoSimple.o
datosEstimadosPolinomio.o: datosEstimadosPolinomio.cpp datosEstimadosPolinomio.hpp funcionesFichero.hpp
	$(CC) datosEstimadosPolinomio.cpp $(FLAGS) -o datosEstimadosPolinomio.o
datosEstimados2n.o: datosEstimados2n.cpp datosEstimados2n.hpp funcionesFichero.hpp
	$(CC) datosEstimados2n.cpp $(FLAGS) -o datosEstimados2n.o
hanoi.o: hanoi.cpp hanoi.hpp
	$(CC) hanoi.cpp $(FLAGS) -o hanoi.o

pPrincipal.o: pPrincipal.cpp ClaseTiempo.hpp funcionesFichero.hpp funcionesMatriz.hpp minimosCuadradosPolinomico.hpp minimosCuadrados2n.hpp recursivoSimple.hpp datosEstimados2n.hpp datosEstimadosPolinomio.hpp
		$(CC) pPrincipal.cpp $(FLAGS) -o pPrincipal.o



clean:
	rm -f *.o $(EXE) *.txt
