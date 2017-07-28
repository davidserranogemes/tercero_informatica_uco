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

#include "funcionesOpencv.hpp"

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

	list<int> coordinates;
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
				//std::cout<<"BUFFER: "<<buffer<<std::endl;
				init=end;
				coordinates.push_back(atoi(buffer));
			}
		}
		leng= wValue.copy(buffer,end-init,init);
		end++;
		buffer[leng]='\0';
		//std::cout<<"BUFFER: "<<buffer<<std::endl;
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
//		std::cout<<"COORD x:" <<coordX<<std::endl;
//		std::cout<<"COORD y:" <<coordY<<std::endl;
//		std::cout<<"COORD we:" <<coordWeight<<std::endl;
		std::cout<<"COORD he:" <<coordHeight<<std::endl;
	/*	
		while(!coordinates.empty()){
			std::cout<<"BUFFER: "<<coordinates.front()<<std::endl;
			coordinates.pop_front();
		}
		*/

	}

//programa
	string foto, masc;
	
	cv::Mat img;
	cv::Mat imgOrigen;
	cv::Mat aux;
	cv::Mat mascara;
	
	vector<cv::Mat> canales;
	
	vector<int> moda;
	
	int maxModa=0;
	int defModa;
	int row, cols;
	int min=9999999;
	int max=0;
	int numCanal;
	int check;
	int auxval=0;

	double desTipica=0;

	long double media=0,suma=0, sumaCuadrados=0, varianza=0;

	long int posArea=0, negArea=0, numZeros=0, pixelused=0;
	
	double pearson;

	bool colorImage;
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
	//std::cin>>foto;

	//nales.resize(3);
	imgOrigen=cv::imread(foto.c_str(),-1 );	//el entero final indica el tipo de imagen que genera
										//0= imagen en blanco y negro
										//1= imagen a color


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

	moda.resize(256);
/*	if(colorImage){
		numCanal=3;
	}else{
		numCanal=1;
	}*/
	numCanal=canales.size();
		
	//fin check color
	std::cout<<"Canales: "<<numCanal<<std::endl;
	std::cout<<"Filas: "<<row<<std::endl;
	std::cout<<"Cols: "<<cols<<std::endl;

	for(int i=0;i<numCanal;i++){
		//Tabajamos en cada canal
		std::cout<<std::endl;
		std::cout<<std::endl;
		std::cout<<"Canal: "<<i<<std::endl;

		//inicializa el vector de la moda
		for(int j=0;j<256;j++){
			moda[i]=0;
		}
		//Se asegura de que o bien se apriete enter o esc
		do{
			cv::imshow("Canal",canales[i]);
			check=(char) cv::waitKey(0);
			
		//	std::cout<<"CHEKC:"<<check<<std::endl; 
		}while(check!=ENTER and check!=ESC);


		if(check==ESC){
			std::cout<<"Se ha decidido no extraer estadisticos de este canal."<<std::endl;	
		}else{
			if(mflag){
	//			std::cout<<"usamos mascara"<<std::endl;
			for(int j=0;j<row;j++){
				for(int k=0;k<cols;k++){
					//Contabiliza la moda
					if(mascara.at<uchar>(k,j)==255){ //Control de mascara, si es !=0 se cuenta
						pixelused++;
						auxval=canales[i].at<uchar>(k,j);
						if(pow(auxval,2)<0){
							moda[pow(auxval,2)+128]=moda[128+pow(auxval,2)]+1;
						}else{
							moda[pow(auxval,2)]=moda[pow(auxval,2)]+1;
						}
						//suma acumulativa simple y cuadratica, sirve para la varianza por ejemplo
						suma+=auxval;
						sumaCuadrados+=pow(auxval,2);
						//std::cout<<val<<std::endl;
					
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
							if((int)auxval==0){
								numZeros++;
								std::cout<<"Un cero:"<<auxval<<std::endl;
							}else{
								negArea++;
							}
						}	
					}
				}
			}
		}else{
			//std::cout<<"No usamos mascara"<<std::endl;
			for(int j=0;j<row;j++){
				for(int k=0;k<cols;k++){
					//Contabiliza la moda
						pixelused++;

						auxval=canales[i].at<uchar>(k,j);

						if(pow(auxval,2)<0){
							moda[pow(auxval,2)+128]=moda[128+pow(auxval,2)]+1;
						}else{
							moda[pow(auxval,2)]=moda[pow(auxval,2)]+1;
						}
						//suma acumulativa simple y cuadratica, sirve para la varianza por ejemplo
						suma+=auxval;
						sumaCuadrados+=pow(auxval,2);
						//std::cout<<val<<std::endl;
					
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
							if(auxval==0){
								numZeros++;
							}else{
								negArea++;
							}
						}	
				}
			}
		}
			//Seleccion de la moda
			for(int m=0;m<256;m++){
				if(moda[m]>maxModa){
					defModa=m;
				}
			}

			media=suma/(pixelused);
			varianza=sumaCuadrados/(pixelused)-pow(media,2);


			//Calculo del coeficiente de asimetria de pearson

			desTipica=0;
			long double sumaCubos=0;
			//check mascara
			if(mflag){
				for(int j=0;j<row;j++){
					for(int k=0;k<cols;k++){
						if(mascara.at<uchar>(k,j)==255){
					//	desTipica=desTipica+pow(canales[i].at<uchar>(k,j)-media,2);
						auxval=canales[i].at<uchar>(k,j);
						sumaCubos=sumaCubos+pow(auxval-media,3);
						}
					}
				}
			}else{
				for(int j=0;j<row;j++){
					for(int k=0;k<cols;k++){
					//	desTipica=desTipica+pow(auxval-media,2);
						auxval=canales[i].at<uchar>(k,j);

						sumaCubos=sumaCubos+pow(auxval-media,3);
					}
				}

			}

			desTipica=desTipica/((pixelused)-1);
			sumaCubos=sumaCubos/((pixelused));

			desTipica=sqrt(varianza);
			//desTipica=sqrt(desTipica);
			desTipica=pow(desTipica,3);
			
		//	pearson=(media-defModa)/desTipica;

			pearson=sumaCubos/desTipica;



			//Muestra de las estadisticas
			std::cout<<"width: "<<canales[i].cols<<std::endl;
			std::cout<<"Height: "<<canales[i].rows<<std::endl;

			std::cout<<"Minimo valor: "<<min<<std::endl;
			std::cout<<"Maximo valor: "<<max<<std::endl;
			std::cout<<"Media: "<<media<<std::endl;
			std::cout<<"Varianza: "<<varianza<<std::endl;
			std::cout<<"Suma: "<<suma<<std::endl;
			std::cout<<"Suma Cuadrados: "<<sumaCuadrados<<std::endl;
			std::cout<<"Area positiva: "<<posArea<<std::endl;
			std::cout<<"Area negativa: "<<negArea<<std::endl;
			std::cout<<"Numero de zeros: "<<numZeros<<std::endl;
			std::cout<<"Moda: "<<defModa<<std::endl;
			std::cout<<"Asimetria de Pearson / Skewness:" <<pearson<<std::endl;
		//	std::cout<<"Desviacion tipica: "<<desTipica<<std::endl;
			//Reset de acumuladores.
			maxModa=0;
			media=0;
			suma=0;
			sumaCuadrados=0;
			varianza=0;
			min=9999999;
			max=0;
			posArea=0;
			negArea=0;
			numZeros=0;
			sumaCubos=0;
			pixelused=0;

		}
	}
}