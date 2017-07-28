#ifndef REGION_HPP
#define REGION_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp> 
#include <cv.h>

#include <vector>
#include <iostream>
/**
@brief Describre una region como una lista de áreas rectangulares que son adyacentes mas el histograma de valores de característica en los pixeles dentro de estas áreas.
El histograma estará normalizado.
*/

class Region {
public:
       /**@brief crea una region*/
    Region(const cv::Rect& r, cv::Mat& hist){
    		_rs.push_back(r);
    		_hist=hist;
    }
    
       /**@brief calcula el tamaño en pixeles de una region*/
    float size() const;
    
       /**@brief devuelve el histograma de la region*/
    const cv::Mat& hist() const;

       /**@brief devuelve la lista de rectángulos
        @post los rectángulos definen una componente conexa.
       */
    const std::vector<cv::Rect>& rects() const;

       /**@brief comprueba si la region other y this son adyacentes.
          Dos regiones son adyacentes si al menos dos rectángulos, uno de cada una, son adyacentes.
       */
    bool areAdjacents(const Region& other) const;
    
       /**@brief fusiona la region other con this.
       @post other y this son adyacentes.
       */
    void merge(const Region& other);

    void setRect(cv::Rect &r){_rs.clear();_rs.push_back(r);};
    void setHist(cv::Mat hist){_hist=hist;};
    
private:
    std::vector<cv::Rect> _rs;
    cv::Mat _hist;
};

#endif