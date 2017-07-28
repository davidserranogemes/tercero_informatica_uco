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
#include <cv.h>

#include "funciones.hpp"
#include "Region.hpp"

int main(int argc, char ** argv){


	bool aflag=false;
	float avalue=1.2;

	bool bflag=false;
	float bvalue=2.0;

	bool cflag=false;
	int cvalue=16;

		bool eflag=false;
	int evalue=100;

	bool fflag=false;
	int fvalue=1000;

	bool hflag=false;
	bool uflag=false;

	int optvalue;

	while((optvalue = getopt(argc,argv,"a:b:c:e:hu"))!=-1 ){
		switch(optvalue){
			case 'a':
				aflag=true;
				avalue=atof(optarg);
				break;
			case 'b':
				bflag=true;
				bvalue=atof(optarg);
				break;
			//case 'i':
			case 'c':
				cflag=true;
				cvalue=atoi(optarg);
				break;
			case 'e':
				eflag=true;
				evalue=atoi(optarg);
				break;
			
			case 'h':
				hflag=true;
				break;
			case 'u':
				uflag=true;
			case '?':
			
			if(optopt=='a'){
					std::cerr<<"La opcion "<<optopt<<" requiere un argumento"<<std::endl;
					abort();
				//}else{}para el -i
				}else{
					if(optopt=='b'){
						std::cerr<<"La opcion "<<optopt<<" requiere un argumento"<<std::endl;
						abort();
					}else{
						if(optopt=='c'){
							std::cerr<<"La opcion "<<optopt<<" requiere un argumento"<<std::endl;
							abort();
						}else{
							if(optopt=='e'){
								std::cerr<<"La opcion "<<optopt<<" requiere un argumento"<<std::endl;
								abort();
							}else{
								if(optopt=='f'){
									std::cerr<<"La opcion "<<optopt<<" requiere un argumento"<<std::endl;
									abort();
								}else{
									if(isprint (optopt)){
	              						std::cerr<<"Opción desconocida '-"<<optopt<<"'"<<std::endl;
					              		exit(-1);
	        				    	}else{
	            						//std::cerr<<"Error desconocido."<<std::endl;
	            					}
								}
							}
						}
					}
				}
		}
	}
	

if(hflag){
	std::cout<<"-a valor limite de homogeneo"<<std::endl;
	std::cout<<"-b valor limite de fusion"<<std::endl;
	std::cout<<"-c tamaño minimo de zona"<<std::endl;
	std::cout<<"-e minimo numero de iteraciones antes de salir de dejar intentar de fusionar"<<std::endl;
	std::cout<<"-h ayuda"<<std::endl;

	std::cout<<"Se debe poner la ruta de una imagen de entrada y la ruta de la imagen de salida"<<std::endl;
	exit(-1);
}
std::string nombreImgEntrada;
std::string nombreImgSalida;
switch(argc){
	case 3:
		nombreImgEntrada=argv[1];
		nombreImgSalida=argv[2];
		break;
	case 4:
		nombreImgEntrada=argv[2];
		nombreImgSalida=argv[3];
		break;
	case 5:
		nombreImgEntrada=argv[3];
		nombreImgSalida=argv[4];
		break;
	case 6:
		nombreImgEntrada=argv[4];
		nombreImgSalida=argv[5];
		break;
	case 7:
		nombreImgEntrada=argv[5];
		nombreImgSalida=argv[6];
		break;
	case 8:
		nombreImgEntrada=argv[6];
		nombreImgSalida=argv[7];
		break;
	default:
		std::cout<<"Error de sintaxis, utilice ./lbpImg -h"<<std::endl;
		exit(-1);
}


cv::Mat lbpImg;
lbpImg=cv::imread(nombreImgEntrada.c_str(),0);

if(lbpImg.empty()){
	std::cout<<"La imagen "<<nombreImgEntrada<<" no existe."<<std::endl;
	exit(-1);
}

float sTh=avalue;
float miTh=bvalue;
float minSize=cvalue;
uint minIters=evalue;

std::vector<Region> regions;



split(lbpImg,sTh,minSize,regions,uflag);

std::cout<<"Numero de regiones: "<<regions.size()<<std::endl;

std::cout<<"Mostrando segmentacion."<<std::endl;
cv::Mat border=generatelSegmentedImage(lbpImg.size(),regions);
border=getBorders(border);
cv::imshow("Segmentada",border);
cv::waitKey(0);

std::cout<<"Mostrando imagen falso color antes del merge."<<std::endl;
cv::Mat imgFalsoColor=generatelSegmentedImage(lbpImg.size(),regions);
cv::imshow("Falso color",imgFalsoColor);
cv::waitKey(0);

merge(regions,miTh,minIters,sTh);

std::cout<<"Numero de regiones: "<<regions.size()<<std::endl;
border=generatelSegmentedImage(lbpImg.size(),regions);
border=getBorders(border);
cv::imshow("Segmentada",border);
cv::waitKey(0);

cv::Mat lbpImgSalida(lbpImg);

for(int j=0;j<lbpImg.cols;j++){
	for(int k=0;k<lbpImg.rows;k++){
		if(border.at<uchar>(k,j)==255)
			lbpImgSalida.at<uchar>(k,j)=255;
	}
}

std::cout<<"Mostrando imagen en falso color: "<<std::endl;


cv::imwrite(nombreImgSalida,lbpImgSalida);


imgFalsoColor=generatelSegmentedImage(lbpImg.size(),regions);
cv::imshow("Falso color",imgFalsoColor);
cv::waitKey(0);

cv::imwrite("false-color"+nombreImgSalida,imgFalsoColor);

std::cout<<"Se acaba el programa."<<std::endl;

}