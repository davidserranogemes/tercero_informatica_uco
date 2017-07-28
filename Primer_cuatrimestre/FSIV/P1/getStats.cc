/*
Nota se usa como control de mascara que el elemento valga 255 para contarse
Esto hace que todos los valores coincidan con datos.txt salvo el caso de 
cell.png mascara ROI, que requiere que se compruebe que el pixel de la mascara !=0

Debido a que con ==255 obtenemos una mayor cantidad de datos exactos,
decidimos dejarlo con ese valor aunque se ha añadido comentada la linea que haria falta
para !=0

*/


#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include <string>
#include <cmath>
#include <list>
//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp> 
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/calib3d/calib3d.hpp>



using std::vector;
using std::string;
using std::list;
		
#define ESC  27
#define ENTER 10

int main(int argc, char **argv){
	//Control de parametros
	bool wflag=false;
	string wValue;
	int optvalue;
	int coordX, coordY, coordHeight, coordWeight;
	list<int> coordinates;


	while((optvalue = getopt(argc,argv,"w:"))!=-1 ){
		switch(optvalue){
			case 'w':
				wflag=true;
				wValue=optarg;
				break;
			//case 'i':
			case '?':
				if(optopt=='i'){
					std::cerr<<"La opcion "<<optopt<<" requiere un argumento"<<std::endl;
					abort();
				//}else{}para el -i
				}else{
					if(isprint (optopt)){
	              		std::cerr<<"Opción desconocida '-"<<optopt<<"'"<<std::endl;
	              		exit(-1);
	            	}else{
	            		std::cerr<<"Error desconocido."<<std::endl;
	            	}
				}


		}
	} //añadir -i para meter la ultima opcion

	

	if(wflag){
		uint init=0, end=0;
		char buffer [10];
		int leng;
		std::cout<<"-w "<<wValue<<std::endl;
		while(end<wValue.size()){
			if(isdigit(wValue[end])){
				end++;
			}else{
				leng= wValue.copy(buffer,end-init,init);
				end++;
				buffer[leng]='\0';
				init=end;
				coordinates.push_back(atoi(buffer));
			}
		}

		leng= wValue.copy(buffer,end-init,init);
		end++;
		buffer[leng]='\0';
		init=end;
		coordinates.push_back(atoi(buffer));

		if(coordinates.size()!=4){
			std::cout<<"La opcion -w requiere 4 numeros enteros positivos, separados por una coma."<<std::endl;
			exit(-1);
		}
		coordX=coordinates.front();
		coordinates.pop_front();


		coordY=coordinates.front();
		coordinates.pop_front();

		coordWeight=coordinates.front();
		coordinates.pop_front();

		coordHeight=coordinates.front();
		coordinates.pop_front();

	}

//programa
	string foto, masc;
	
	cv::Mat img;
	cv::Mat imgOrigen;
	cv::Mat aux;
	cv::Mat mascara;
	
	vector<cv::Mat> canales;
	
	int row, cols;
	int min=9999999;
	int max=0;
	int numCanal;
	int check;
	int auxval=0;
	int numPos=0, numNeg=0;
	double desTipica=0;

	long double media=0,suma=0, sumaCuadrados=0, varianza=0;

	long int posArea=0, negArea=0, numZeros=0, pixelused=0;
	
	double pearson;

	//bool colorImage;
	bool mflag=false;


	switch(argc){
		case 2:
			if(wflag){//-w activado sin fotos
				std::cout<<"Error de sintaxis. Se esperaba: ./nombre-programa [-w x,y,h,w] img1 [mascara]"<<std::endl;
				exit(-1);
			}else{//solo la foto
				foto=argv[1];
			}
			break;

		case 3:
				if(wflag){
					foto=argv[2];
				}else{//consideramos que el otro parametro es la mascara
					foto=argv[1];
					masc=argv[2];
					mflag=true;
				}
			break;

		case 4:
			if(wflag){
				foto=argv[2];
				masc=argv[3];
				mflag=true;
			}else{
				std::cout<<"Error de sintaxis. Se esperaba: ./nombre-programa [-w x,y,h,w] img1 [mascara]"<<std::endl;
				exit(-1);				
			}
			break;
		default:
				std::cout<<"Error de sintaxis. Se esperaba: ./nombre-programa [-w x,y,h,w] img1 [mascara]"<<std::endl;
				exit(-1);	
			break;
	}

	std::cout<<"Se trata la foto: "<<foto<<std::endl;
	
	if(mflag){
		std::cout<<"Se usa la mascara: "<<masc<<std::endl;
		mascara=cv::imread(masc.c_str(),0);
		if(mascara.empty()){
			std::cout<<"La mascara indicada no existe."<<std::endl;
			exit(-1);
		}
	}
	imgOrigen=cv::imread(foto.c_str(),-1 );	//el entero final indica el tipo de imagen que genera
										//0= imagen en blanco y negro
										//1= imagen a color
										//-1=segun el tipo de image,, si es BN carga en 0, si es RGB  carga 1


	if(imgOrigen.empty()){
		std::cout<<"La foto indicada no existe."<<std::endl;
		exit(-1);
	}


//IMAGEN ROI
	if(wflag){
		if(imgOrigen.rows<coordX+coordHeight or imgOrigen.cols<coordY+coordWeight){
			std::cout<<"La dimensiones de la ROI se salen de rango."<<std::endl;
			exit(-1);
		}
		if(coordX<0 or coordY<0 or coordWeight<0 or coordHeight<0){
			std::cout<<"Las coordenadas introducidas deben ser positivas."<<std::endl;
		}
		cv::Rect ROI(coordX,coordY,coordWeight,coordHeight);
		aux=imgOrigen(ROI);	
		aux.copyTo(img);
		if(mflag){
			cv::Rect ROImask(coordX,coordY,coordWeight,coordHeight);
			aux=mascara(ROImask);
			aux.copyTo(mascara);
		}
	}else{
		imgOrigen.copyTo(img);
	}

	if(img.empty()){
		std::cout<<"Fallo en la copia."<<std::endl;
		exit(-1);
	}


	row=img.rows;//son variables publicas, no funciones
	cols=img.cols;


	cv::split(img, canales);//No requiere que el vector este inicializado! GGWP

	//colorImage=imagenColor(canales);

	numCanal=canales.size();
		
	//fin check color
	std::cout<<"Canales: "<<numCanal<<std::endl;
	std::cout<<"Ancho: "<<cols<<std::endl;
	std::cout<<"Alto: "<<row<<std::endl;


	for(int i=numCanal-1;i>=0;i--){

		//Tabajamos en cada canal
		std::cout<<std::endl;
		std::cout<<std::endl;
		std::cout<<"Canal: "<<i<<std::endl;

		//Se asegura de que o bien se apriete enter o esc
		do{
			cv::imshow("Canal",canales[i]);
			check=(char) cv::waitKey(0);
			
		}while(check!=ENTER and check!=ESC);


		if(check==ESC){
			std::cout<<"Se ha decidido no extraer estadisticos de este canal."<<std::endl;	
		}else{
			if(mflag){
			for(int j=0;j<cols;j++){
				for(int k=0;k<row;k++){
					//Contabiliza la moda
					if(mascara.at<uchar>(k,j)==255){ 
					//if(mascara.at<uchar>(k,j)!=0){ cell.png mascara ROI

						pixelused++;
						auxval=canales[i].at<uchar>(k,j);

						//suma acumulativa simple y cuadratica, sirve para la varianza por ejemplo
						suma+=auxval;
						sumaCuadrados+=pow(auxval,2);
					
						//Calculo del minimo y del maximo
						if(min>auxval){
							min=auxval;
						}else{
							if(max<auxval){
								max=auxval;
							}
						}
						//Calculo del numero de elementos positivos, negativos y 0
						if(auxval>0){
							posArea=posArea+auxval;;
							numPos++;
						}else{
							if(auxval<0){
								negArea=negArea+auxval;;
								numNeg++;

							}else{
								numZeros++;

							}
						}	
					}
				}
			}
		}else{
			//Sin mascara
			for(int j=0;j<cols;j++){
				for(int k=0;k<row;k++){
						pixelused++;
						auxval=canales[i].at<uchar>(k,j);

						//suma acumulativa simple y cuadratica, sirve para la varianza por ejemplo
						suma+=auxval;
						sumaCuadrados+=pow(auxval,2);
					
						//Calculo del minimo y del maximo
						if(min>auxval){
							min=auxval;

						}else{
							if(max<auxval){
								max=auxval;
							}
						}
						//Calculo del numero de elementos positivos, negativos y 0
						if(auxval>0){
							posArea++;
						}else{
							if(auxval<0){
								negArea++;
							}else{
								numZeros++;
							}
						}	
				}
			}
		}
	

			media=suma/(pixelused);
			varianza=sumaCuadrados/(pixelused)-pow(media,2);


			//Calculo del coeficiente de asimetria de pearson

			desTipica=0;
			long double sumaCubos=0;

			//check mascara
			if(mflag){
				for(int j=0;j<cols;j++){
					for(int k=0;k<row;k++){
						if(mascara.at<uchar>(k,j)==255){ 
//						if(mascara.at<uchar>(k,j)!=0){ cell.png mascara ROI
	
						auxval=canales[i].at<uchar>(k,j);
						sumaCubos=sumaCubos+pow(auxval-media,3);
						}
					}
				}
			}else{
				for(int j=0;j<cols;j++){
					for(int k=0;k<row;k++){
						auxval=canales[i].at<uchar>(k,j);

						sumaCubos=sumaCubos+pow(auxval-media,3);
					}
				}

			}

			sumaCubos=sumaCubos/((pixelused));

			desTipica=sqrt(varianza);
			desTipica=pow(desTipica,3);
			

			pearson=sumaCubos/desTipica;


			//Muestra de las estadisticas
			std::cout<<"Width: "<<canales[i].cols<<std::endl;
			std::cout<<"Height: "<<canales[i].rows<<std::endl;

			std::cout<<"Minimo valor: "<<min<<std::endl;
			std::cout<<"Maximo valor: "<<max<<std::endl;
			std::cout<<"Media: "<<media<<std::endl;
			std::cout<<"Varianza: "<<varianza<<std::endl;
			std::cout<<"Suma: "<<suma<<std::endl;
			std::cout<<"Suma Cuadrados: "<<sumaCuadrados<<std::endl;
			std::cout<<"Area positiva: "<<posArea<<std::endl;
			std::cout<<"Area negativa: "<<negArea<<std::endl;
			std::cout<<"Numero de positivos: "<<numPos<<std::endl;
			std::cout<<"Numero de negativos: "<<numNeg<<std::endl;
			std::cout<<"Numero de zeros: "<<numZeros<<std::endl;
			std::cout<<"Asimetria de Pearson / Skewness:" <<pearson<<std::endl;
		//	std::cout<<"Desviacion tipica: "<<desTipica<<std::endl;
			//Reset de acumuladores.
			media=0;
			suma=0;
			sumaCuadrados=0;
			varianza=0;
			min=9999999;
			max=0;
			posArea=0;
			negArea=0;
			numZeros=0;
			numNeg=0;
			numPos=0;
			sumaCubos=0;
			pixelused=0;

		}
	}
}