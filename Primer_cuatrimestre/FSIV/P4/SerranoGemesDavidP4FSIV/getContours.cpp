#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include <string>
#include <cmath>
#include <list>
#include <fstream>

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <cv.h>

using namespace cv;

void puntosFichero(std::string baseFichero,int indice,vector<Point>& puntos);
bool isNotIn(std::vector<int> &max,int ind);
int min(int min1, int min2);


int main(int argc,char ** argv){

	bool nflag=false;
	int nValue=1;


	int optvalue;

	while((optvalue = getopt(argc,argv,"n:"))!=-1 ){
		switch(optvalue){
			case 'n':
				nflag=true;
				nValue=atoi(optarg);
				break;
			
			case '?':
			
			if(optopt=='n'){
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

	std::string nombreImgEntrada;
	std::string nombreContourBaseName;
	switch(argc){
		case 3:
			nombreImgEntrada=argv[1];
			nombreContourBaseName=argv[2];
			break;
		case 4:
			nombreImgEntrada=argv[2];
			nombreContourBaseName=argv[3];
			break;

		default:
			std::cout<<"Error de sintaxis, utilice ./getContours [-n(int)] img-entrada baseNombresFichero"<<std::endl;
			exit(-1);
	}

	Mat contourIMG;

	contourIMG=imread(nombreImgEntrada.c_str(),-1);

	if(contourIMG.empty()){
		std::cout<<"La imagen "<<nombreImgEntrada<<" no existe."<<std::endl;
		exit(-1);
	}

	int numeroContornos=nValue;
   	
    //cvtColor(contourIMGInit, contourIMG, CV_BGR2GRAY);

  	vector<vector<Point> > contours;
  	vector<Vec4i> hierarchy;

	findContours( contourIMG, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);//, Point(0, 0) );
  	 std::cout<<"Contornos: "<<contours.size()<<std::endl;


  	vector<int> max;
  	max.resize(nValue,-1);
  	
  	
  	for(int i=0;i<contours.size();i++){
  		int maxLoc=0;
  		for(int j=0;j<contours.size();j++){
  			if(maxLoc<contours[j].size()){
  				if(isNotIn(max,j)){
  					maxLoc=j;
  					max[i]=j;
  				}	
  			}
  		}
  	}
   	
  for(int i=0; i<min(nValue,contours.size());i++){
  	puntosFichero(nombreContourBaseName,i,contours[max[i]]);
}

}

void puntosFichero(std::string baseFichero,int indice,vector<Point>& puntos){
	std::ofstream ficheroSalida;

	std::string nombreFichero=baseFichero+"-"+std::to_string(indice)+".txt";

	ficheroSalida.open(nombreFichero);
	std::cout<<"Escribiendo contorno "<<indice<<std::endl;
	std::cout<<"No da exactamente los puntos que al profesor, para que los de activar la corrección."<<std::endl<<"Provoca resultados erroneos en el rec minimo y los descriptores de Fourier."<<std::endl;
	for(int i=0;i<puntos.size();i++){
		//ficheroSalida<<puntos[i].x<<" "<<256-puntos[i].y<<std::endl; //Esta linea hace que los resultados salgan como a el
		ficheroSalida<<puntos[i].x<<" "<<puntos[i].y<<std::endl;

	}
	ficheroSalida.close();

}


bool isNotIn(std::vector<int> &max,int ind){
	bool exist=true;

	for(int i=0;i<max.size();i++){
		if(max[i]==ind){
			exist=false;
			
		}
	}
	return exist;


}

int min(int min1, int min2){
	if(min1>min2)
		return min2;
	else
		return min1;
}