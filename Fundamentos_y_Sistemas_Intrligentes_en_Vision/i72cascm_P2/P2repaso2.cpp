//<>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

std::vector<double> histograma(256,0);
std::vector<double> histogramaAcumulado(256,0);
std::vector<double> resultado(256,0);

void makeHistograms(const cv::Mat &input){


    //histogram
    int val=0;
    for(int y=0;y<input.rows;y++){
        for(int x=0;x<input.cols;x++){
            val = input.at<uchar>(y,x);
            histograma[val] = histograma[val]+1;
        }
    }

    //acumulated hist
    histogramaAcumulado[0] = histograma[0];
    for(int i=1;i<histograma.size();i++){
        histogramaAcumulado[i] = histograma[i]+histogramaAcumulado[i-1];
    }
}

void equalization(cv::Mat &output){

    //equalization
    for(int i = 0;i<resultado.size();i++){
        resultado[i] = (histogramaAcumulado[i]/(output.rows*output.cols))*255;
    }

    //rellenar output

    for(int y=0;y<output.rows;y++){
        for(int x=0;x<output.cols;x++){
            output.at<uchar>(y,x) = resultado[output.at<uchar>(y,x)];
        }
    }

}


int main(int argc, char **argv){
    
    if(argc!=2){
        std::cerr<<"nº args invalido"<<std::endl;
        return 0;
    }

    try{

        cv::Mat input = cv::imread(argv[1],cv::IMREAD_GRAYSCALE);
        cv::Mat output = input.clone();

        makeHistograms(input);
        equalization(output);

        cv::imshow("first",input);
        cv::imshow("second",output);
        cv::waitKey(0);

    }catch(std::exception &ex){
        std::cout<<ex.what()<<std::endl;
        return 0;
    }

}