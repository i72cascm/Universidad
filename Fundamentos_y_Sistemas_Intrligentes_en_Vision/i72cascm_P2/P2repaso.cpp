//repaso p2

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

std::vector<double> histograma(255,0);
std::vector<double> histogramaAcumulado(255,0);
std::vector<double> result(255,0);

cv::Mat image;
cv::Mat image2;

void makeHistogram(){

    //histograma
    for(int y=0;y<image.rows;y++){
        for(int x=0;x<image.cols;x++){
            int val = image.at<uchar>(y,x);
            histograma[val]++;
        }
    }

    //histograma acumulado
    histogramaAcumulado[0] = histograma[0];
    for(int i = 1;i<histograma.size();i++){
        histogramaAcumulado[i] = histograma[i] + histogramaAcumulado[i-1];
    }


}

void equalization(){

    //equalizar
    for(int i = 0;i<256;i++){
        result[i] = (histogramaAcumulado[i]/(image.cols*image.rows))*255;
    }

    //rellenar img2
    for(int y=0; y<image2.rows;y++){
        for(int x=0; x<image2.cols;x++){
            image2.at<uchar>(y,x) = result[image2.at<uchar>(y,x)];
        }
    }

}


int main(int argc, char **argv){

    if(argc!=2){
        std::cerr<<"nº de argumentos mal"<<std::endl;
    }

    image = cv::imread(argv[1],cv::IMREAD_GRAYSCALE);
    image2 = cv::imread(argv[1],cv::IMREAD_GRAYSCALE);
    //cv::imshow("saaa",image2);
    makeHistogram();
    equalization();


    cv::imshow("first",image);
    cv::imshow("second",image2);

    cv::waitKey(0);

}