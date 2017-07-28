FLAGS= -c -g -ansi -Wall -Wextra -std=c++11
EXE= programaFinal
CC=g++

all:$(EXE)

programaFinal: programaFinal.o funcionesAux.o funcionesFichero.o funcionesMatriz.o ClaseTiempo.o generarDatosInversa.o generarDatosFibonacci.o datosFibonaci.o minimosCuadradosMatriz.o minimosCuadradosFib.o datosEstimadosMatriz.o datosEstimadosFib.o
	$(CC) programaFinal.o generarDatosInversa.o funcionesAux.o funcionesFichero.o funcionesMatriz.o ClaseTiempo.o generarDatosFibonacci.o datosFibonaci.o minimosCuadradosMatriz.o minimosCuadradosFib.o datosEstimadosMatriz.o datosEstimadosFib.o -o programaFinal

funcionesAux.o: funcionesAux.cpp funcionesAux.hpp
	$(CC) funcionesAux.cpp $(FLAGS) -o funcionesAux.o
funcionesFichero.o:  funcionesFichero.cpp funcionesFichero.hpp
	$(CC) funcionesFichero.cpp $(FLAGS) -o funcionesFichero.o
funcionesMatriz.o: funcionesMatriz.cpp funcionesMatriz.hpp
	$(CC) funcionesMatriz.cpp $(FLAGS) -o funcionesMatriz.o
ClaseTiempo.o: ClaseTiempo.cpp ClaseTiempo.hpp
	$(CC) ClaseTiempo.cpp $(FLAGS) -o ClaseTiempo.o
datosFibonaci.o: datosFibonaci.cpp datosFibonaci.hpp
	$(CC) datosFibonaci.cpp $(FLAGS) -o datosFibonaci.o

generarDatosFibonacci.o: generarDatosFibonacci.cpp generarDatosFibonacci.hpp funcionesMatriz.hpp funcionesFichero.hpp funcionesAux.hpp ClaseTiempo.hpp
	$(CC) generarDatosFibonacci.cpp $(FLAGS) -o generarDatosFibonacci.o

generarDatosInversa.o: generarDatosInversa.cpp generarDatosInversa.hpp funcionesMatriz.hpp funcionesFichero.hpp funcionesAux.hpp ClaseTiempo.hpp
	$(CC) generarDatosInversa.cpp  $(FLAGS) -o generarDatosInversa.o

minimosCuadradosMatriz.o: minimosCuadradosMatriz.cpp  minimosCuadradosMatriz.hpp funcionesFichero.hpp funcionesMatriz.hpp
	$(CC) minimosCuadradosMatriz.cpp $(FLAGS) -o minimosCuadradosMatriz.o

minimosCuadradosFib.o: minimosCuadradosFib.cpp  minimosCuadradosFib.hpp funcionesFichero.hpp funcionesMatriz.hpp
	$(CC) minimosCuadradosFib.cpp $(FLAGS) -o minimosCuadradosFib.o
datosEstimadosMatriz.o: datosEstimadosMatriz.cpp datosEstimadosMatriz.hpp funcionesFichero.hpp funcionesAux.hpp
	$(CC) datosEstimadosMatriz.cpp $(FLAGS) -o datosEstimadosMatriz.o
datosEstimadosFib.o: datosEstimadosFib.cpp datosEstimadosFib.hpp funcionesFichero.hpp funcionesAux.hpp
	$(CC) datosEstimadosFib.cpp $(FLAGS) -o datosEstimadosFib.o

programaFinal.o: programaFinal.cpp generarDatosInversa.hpp
	$(CC) programaFinal.cpp $(FLAGS) -o programaFinal.o

clean:
	rm -f *.o programaFinal *.txt