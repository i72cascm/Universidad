//<>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

void applyKernel(const cv::Mat &input, cv::Mat &output, const cv::Mat &kernel){

    int size = kernel.cols;
    int radius = kernel.cols/2;
    //std::cout<<"size: "<<size<<" radius: "<<radius<<std::endl;

    for(int y=0;y<input.rows;y++){
        for(int x=0;x<input.cols;x++){
            float value = 0.0;
            for(int j=(size*-1)+(size/2)+1;j<size-(size/2);j++){
                for(int i=(size*-1)+(size/2)+1;i<size-(size/2);i++){
                    if(((y+j>=0) && (x+i>=0) && (y+j<input.rows) && (x+i<input.cols))){    
                        value += input.at<float>(y+j, x+i)*kernel.at<float>(j+radius,i+radius);
                    }
                }
            }
            output.at<float>(y,x) = value;
        }
    }

}

int main(int argc, char** argv){

    if(argc != 2){
        std::cerr<<"nº de args invalido."<<std::endl;
        return 0;
    }

    try{

        //introducri c y comprobante

        float c = 0.0;
        std::cout<<"Introduzca valor de c: "<<std::endl;
        std::cin>>c;
        if(c<0){
            std::cout<<"c no puede ser menor que 0."<<std::endl;
            return 0;
        }

        //creacion de imagenes

        cv::Mat input = cv::imread(argv[1],cv::IMREAD_GRAYSCALE);
        cv::Mat original;

        input.convertTo(original,CV_32FC1);

        cv::Mat lowFrequency = original.clone();
        cv::Mat highFrequency = original.clone();
        cv::Mat result = original.clone();

        //kernel lowFrequency and aply

        cv::Mat kernelLow(3,3,CV_32FC1);
        kernelLow = cv::Mat::ones(3,3,CV_32FC1)/(float)(3*3);

        applyKernel(original, lowFrequency, kernelLow);

        //highFrequency = image - lowFrequency

        highFrequency = original - lowFrequency;

        //highboost  kernel and apply

        float higharray[] = {-c, -c, -c, -c, 8*c+1, -c, -c, -c, -c};
        cv::Mat kernelHigh(3,3,CV_32FC1,higharray);

        applyKernel(highFrequency, result, kernelHigh);

        //normalize

        cv::Mat result_normalize;
        cv::normalize(result, result_normalize, 255, cv::NORM_MINMAX);

        cv::Mat highFrequency_normalize;
        cv::normalize(highFrequency, highFrequency_normalize, 255, cv::NORM_MINMAX);

        //show results

        cv::namedWindow("original");
        cv::imshow("original", input);
        
        cv::namedWindow("highFrequency");
        cv::imshow("highFrequency", highFrequency_normalize);

        cv::namedWindow("result");
        cv::imshow("result", result_normalize);

        cv::waitKey(0);


    }catch(std::exception &ex){
        std::cout<<ex.what()<<std::endl;
    }

}