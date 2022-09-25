/***********************************
 * Autor: Manuel Casas Castro (i72cascm@uco.es)
 * Universidad de Córdoba (Spain)
 * 
 * P2
 * 
 * ******************************************/

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;

cv::Mat image;
cv::Mat image2;
vector<double> histograma(256,0);
vector<double> histograma_acumulado(256,0);
vector<double> resultado(256,0);

void makeHistograma(){
    //Histogram
    //We take the value of each pixel and we classify them on the histogram
    for(int i=0; i<image.rows;i++){
        for(int j=0;j<image.cols;j++){
            int value = image.at<uchar>(i,j);
            histograma[value]=histograma[value]+1;
                
        }
    }

    //Acumulated histogram
    //We make this histogram by adding the histogram with the previous colum
    histograma_acumulado[0]=histograma[0];
    
    for(int i = 1; i<histograma_acumulado.size();i++){
        histograma_acumulado[i] = histograma[i]+histograma_acumulado[i-1];
    }
}

void equalization(){


    //Using the histogram for doing the final result 
    for(int i=0; i<256;i++){
        resultado[i]=(histograma_acumulado[i]/histograma_acumulado[255])*255;
        
    }

    //Updating the second img with the result array to refactor the img
    for(int i=0; i<image2.rows;i++){
        for(int j=0;j<image2.cols;j++){
            image2.at<uchar>(i,j)=resultado[image2.at<uchar>(i,j)];
            
        }
    }
}

int main(int argc, char **argv){

    //Arguments control
    if(argc!=2){cerr<<"Usage:image"<<endl;return 0;}

    //Load img
    image=imread(argv[1], cv::IMREAD_GRAYSCALE);

    //Clone img for final result
    image2=image.clone();

    try{
        
        //Functions
        makeHistograma();
        equalization();

        //Show img on screen
        cv::imshow("First",image);
        cv::imshow("Second",image2);

        char c;
        while(c!=27)  //waits until ESC pressed
	    c=cv::waitKey(0);


    }catch(std::exception &ex){
    cout<<ex.what()<<endl;
    }

}

    