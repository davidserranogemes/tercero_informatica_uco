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
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/calib3d/calib3d.hpp>

using std::vector;
using std::string;
using std::list;
using namespace cv;

#define ESC  27
#define ENTER 10

const int alpha_slider_max = 255;
int alpha_slider;
int alpha;

void on_trackbar( int, void* );



int main(int argc, char **argv){

	bool tflag=false;
	int tValue;
	int optvalue;

	while((optvalue = getopt(argc,argv,"t:"))!=-1 ){
		switch(optvalue){
			case 't':
				tflag=true;
				tValue=atoi(optarg);
				break;
			//case 'i':
			case '?':
				if(optopt=='t'){
					std::cerr<<"La opcion "<<(char)optopt<<" requiere un argumento entero entre 0-255"<<std::endl;
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
	}


std::string nombreVideo;
std::string rutaVideoSalida;
if(tflag){
	if(argc!=4){
		std::cout<<"Fallo de syntasis../<nombre-programa> -t<range> <ruta-Video-entrada> <ruta-video-Salida>"<<std::endl;
		exit(-1);
	}else{
		nombreVideo=argv[2];
		rutaVideoSalida=argv[3];
	}
}else{
	if(argc!=3){
		std::cout<<"Fallo de syntasis../<nombre-programa> -t<range> <ruta-Video-entrada> <ruta-video-Salida>"<<std::endl;
		exit(-1);
	}else{
		nombreVideo=argv[1];
		rutaVideoSalida=argv[2];
	}
}


	bool first=true;

	int umbralT=0;
	int check;
	uint nframe=0;
	alpha_slider=0;
	alpha=0;
	VideoCapture video(nombreVideo);

	string saveImage;
	Mat filo;
	Mat frame;
	Mat prevFrame;
	Mat withMask;

	Mat difference;
	int fps;
	vector<Mat> canalesClean;

	VideoWriter videoSalida;
	int ex = static_cast<int>(video.get(CV_CAP_PROP_FOURCC));     // Get Codec Type- Int form
	Size S=Size((int) video.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
                  (int) video.get(CV_CAP_PROP_FRAME_HEIGHT));

	if(tflag){
		umbralT=tValue;
		alpha=tValue;
		alpha_slider=tValue;
	}

	if(!video.isOpened()){
		std::cout<<"No se ha podido abrir el video. Compruebe que la ruta es correcta."<<std::endl;
		exit(-1);
	}else{
			namedWindow(nombreVideo,1);
			
			//fps=video.get(CV_CAP_PROP_FPS); //No funciona
			fps=30;
			std::cout<<"fps: "<<fps; 
			createTrackbar( "Umbral", nombreVideo, &alpha_slider, alpha_slider_max, on_trackbar );
	 
      		 videoSalida.open(rutaVideoSalida, ex, fps, S, true);

      		 if(!videoSalida.isOpened()){
      		 	std::cout<<"No se ha podido crear el video de salida."<<std::endl;
      		 	exit(-1);
      		 }





		while(1){
			umbralT=alpha;
			//std::cout<<"1:"<<std::endl;
			if(video.read(frame)){
			//std::cout<<"2:"<<std::endl;
			cvtColor( frame, filo, CV_BGR2GRAY );

			if(first){
				std::cout<<"Primer frame"<<std::endl;
				first=false;
				filo.copyTo(prevFrame);
			}

			absdiff(prevFrame,filo,difference);

			for(int j=0;j<difference.cols;j++){
					for(int k=0;k<difference.rows;k++){
						if(difference.at<uchar>(k,j)>umbralT){
							difference.at<uchar>(k,j)=255;
						}else{
							difference.at<uchar>(k,j)=0;
						}
					}
			}

			frame.copyTo(withMask,difference);

			imshow(nombreVideo,filo);
			imshow("Masked img",withMask);
			imshow("Binary",difference);

			filo.copyTo(prevFrame);


			check= (char) waitKey(50);
			videoSalida<< withMask;


			if(check==32){
				std::cout<<"guarda frame"<<std::endl;
				saveImage="sal_"+std::to_string(nframe)+".png";
				split(withMask,canalesClean);

				for(int k=0;k<withMask.rows;k++){
					for(int j=0;j<withMask.cols;j++){
						for(int i=0;i<withMask.channels();i++){			
							if(difference.at<uchar>(k,j)==0){
								canalesClean[i].at<uchar>(k,j)=255;
							}
						}
					}
				}
				merge(canalesClean,withMask);

				imwrite(saveImage,withMask);
			}
			if(check==ESC){
				destroyAllWindows();
				exit(1);
			}
			videoSalida<< withMask;
			//std::cout<<withMask.channels();
			split(withMask,canalesClean);
		for(int k=0;k<withMask.rows;k++){
			for(int j=0;j<withMask.cols;j++){
				for(int i=0;i<withMask.channels();i++){			
					if(difference.at<uchar>(k,j)==0){
						canalesClean[i].at<uchar>(k,j)=0;
					}
				}
			}
		}
			merge(canalesClean,withMask);
			std::cout<<"Frame: "<<nframe<<"  T value: "<<umbralT<<std::endl;
			nframe++;
			}else{
				std::cout<<"Se acaba el video."<<std::endl;
				destroyAllWindows();
				exit(1);
			}
		}	
	}
	

}

void on_trackbar( int, void* ){
	alpha=alpha_slider;
}