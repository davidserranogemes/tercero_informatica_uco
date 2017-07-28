#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <list>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp> 
#include <cv.h>

#include "Region.hpp"

/**@brief Calcula el código LBP correspondiente a un entorno de un pixel
Calcula el LBP correspondiente a un entorno
a b c
h i d
g f e


Si uniform es true, devuelve el código uniforme.
*/
int computeLBP(const char a, const char b, const char c, const char d, const char e, const char f, const char g, const char h, const char i , bool uniform);


/**@brief Calcula la imagen de LBP dada una imagen de entrada.*/
cv::Mat computeLBPImage(const cv::Mat& img, bool uniform);


/**@brief Calcula un histograma LBP. 
Si hay máscara sólo se tendrán en cuenta los pixeles de activos en la máscara.
Hoja hay que recortar la roi por si cae fuera de los límites de de la imagen.
El histograma resultante estará normalizado o no según el parámetro.
*/
cv::Mat computeLBPHist(const cv::Mat& lbpImg, const cv::Rect& roi, const cv::Mat mask, bool normalize=true,bool LBPU=false);


/**@brief dados dos histogramas calcula la pseudo-distancia entre los mismos.
El valor devuelto será >= 0.0, siendo 0.0 para histogramas idénticos.
se utilizará cv::compareHist con chi-sqr.
*/
float computeHistogramDistance(const cv::Mat& h1, const cv::Mat& h2);


/**@brief dada una región, devolver un vector con cuatro regiones resultantes al dividirla.*/
std::vector<Region> splitRegion(const Region& r);


/**@brief Calcula el coeficiente de split para cuatro regiones resultantes de la división de una region.
el coeficiente es el ratio r_max/r_min, donde r_max es la mayor distancia entre dos regiones y r_min la menor distancia.
*/
float computeSplitCoeff(const std::vector<Region>& rs);


/**@brief Calcula el coeficiente de importancia del merge (MI) entre dos regiones.
Este coeficiente se calcula como p*distancia(r1,r2), donde p es el tamaño en pixeles de la menor de las dos regiones y distancia(r1,r2) es la distancia de sus histogramas.
*/
float computeMICoeff(const Region& r1, const Region& r2);


/**@brief busca en regiones, la pareja de regiones adyacentes r1, r2 cuyo coeficiente MI sea el menor de todos.
El correspondiente valor MI es devuelto.
*/
float findNextRegionsToMerge (const std::vector<Region>& regions, int& r1, int& r2);

/**@brief Pinta una región con una etiqueta.
Rellena cada rectángulo de un región con un valor etiqueta, marcando así cada pixel a la región que pertenece.
*/
void fillRegion(const Region& r, cv::Mat &img, int valueEtiqueta);


/**@brief Genera una imagen de etiquetas según el número de regiones detectadas.
La imagen tendrá como tipo de pixel CV_16I, dejando la etiqueta 0 para uso reservado.
*/
cv::Mat generatelSegmentedImage(const cv::Size& imageSize, const std::vector<Region>& regs);


/**@brief Genera una imagen máscara con todos los pixels frontera a partir de una imagen segmentada.
Un pixel es frontera cuando tiene al menos un 8-vecino con una etiqueta distinta a la suya.
*/
cv::Mat getBorders (const cv::Mat segImg);


/**@brief dada una imagen de característica la dividide en regiones homogéneas.
El algoritmo puede implementarse con una pila donde en cada iteración mientras la pila no esté vacía, desapliar la cima y analizar si hay dividirla. En caso de ser necesario, apliar las cuatro regiones resultantes. En otro caso añadir la región homogénea detectada al vector de regiones homogéneas.
Para dividir una región debe cumplirse que su tamaño WXH sea mayor que minSize y que splitCoeff  > sTh, donde splitCoeff es el coeficiente de split @see computeSplitCoeff.
*/
void split(const cv::Mat& lbpImg, float sTh, float minSize, std::vector<Region>& regions,bool LBPU=false);


/**@brief Dada una lista de regiones homogéneas fusionar las regiones adyacentes que sean a su vez homogéneas.
El algoritmo es iterativo. En cada iteración se busca la pareja de regiones con el factor MI menor posible (es decir que el cambio que se producirá al fusionar será mínimo). Fusionar las regiones, quitar las regiones originales de la lista de regiones y repetir. La condición de salida del bucle será que el ratio MI_cur/MI_max > miTh, donde MI_cur es el factor MI de la pareja que acaba de fusionarse, el factor MI_max es el mayor valor de los valores MI_cur calculados hasta el momento. Para forzar el comienzo, la regla sólo es aplicada a  partir de un número determinado de las fusiones minIters.
*/
void merge(std::vector<Region>& regions, float miTh, unsigned minIters,float sTh);

bool esHomogenea(const Region& r1, const Region& r2, float sTh);

/**@brief refina las fronteras de las regiones detectadas.
El algoritmo es iterativo. En cada iteración cada pixel marcado para estudio (inicialmente los pixeles frontera, es decir al menos un 8-vecino con otra etiqueta de región) es analizado. Para ello se obtiene el histograma de un región de radio r a su alrededor y se compara el histograma de dicha región con los histogramas de las regiones detectadas, asignando la etiqueta del pixel a la de la región con histograma más cercano. Si la etiqueta del pixel cambia, se marcan su 8-vecinos para analizar en la próxima iteración y se actualizan los histogramas de las regiones correspondientes.
La condición de salida del bucle es no tener pixeles que estudiar o alcanzar un número de iteraciones máximo permitido.
La imagen segImage indicará para cada pixel a qué región detectada pertenece. Inicialmente tendrá el resultado de las regiones detectadas el mecanismo de división/fusión.
*/
//void refine(const cv::Mat& lbpImg, cv::Mat& segImage, float radius, unsigned maxIters);



#endif