//<>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>



void applyMagnitud(cv::Mat &result, const cv::Mat &imgX, const cv::Mat &imgY){


    for(int y=0;y<result.rows;y++){
        for(int x=0;x<result.cols;x++){
            int GrX = imgX.at<float>(y,x);
            int GrY = imgY.at<float>(y,x);
            result.at<float>(y,x) = sqrt(pow(GrX,2)+pow(GrY,2));
        }
    }

}


void applyKernel(const cv::Mat &input, cv::Mat &output,const cv::Mat &kernel){
    int radius = kernel.cols/2;
    int size = kernel.rows;

    for(int y=0;y<input.rows;y++){
        for(int x=0;x<input.cols;x++){
            float value = 0.0;
            for(int j=0;j<kernel.rows;j++){
                for(int i=0;i<kernel.cols;i++){
                    if((x+i>=radius) && (y+j>=radius) && (x-i+radius<input.cols) && (y-j+radius<input.rows)){
                        value += input.at<uchar>(y+j-radius,x+i-radius)*kernel.at<float>(j,i);
                        //std::cout<<value<<std::endl;
                    }
                }
            }
            output.at<float>(y,x) = value;
        }
    }
}


int main(int argc, char **argv){

    if(argc!=2){
        std::cerr<<"nº argumentos invalido"<<std::endl;
        return 0;
    }

    try{

        cv::Mat input = cv::imread(argv[1],cv::IMREAD_GRAYSCALE);
        cv::Mat original;
        
        input.convertTo(original,CV_32FC1);

        cv::Mat resultX = original.clone();
        cv::Mat resultY = original.clone();
        cv::Mat magnitud = original.clone();

        float sobelX[] = {-1, 0, 1,
                          -2, 0, 2,
                          -1, 0, 1}; 

        float sobelY[] = {1, 2, 1,
                          0, 0, 0,
                          -1, -2, -1}; 

        cv::Mat kernelX(3,3,CV_32FC1,sobelX);
        cv::Mat kernelY(3,3,CV_32FC1,sobelY);
        //std::cout<<"1"<<std::endl;



        applyKernel(input, resultX, kernelX);
        applyKernel(input, resultY, kernelY);
        applyMagnitud(magnitud, resultX, resultY);

        //std::cout<<"2"<<std::endl;

        cv::Mat normalized = magnitud.clone();
        //std::cout<<"3"<<std::endl;
        cv::normalize(magnitud, normalized, 255, cv::NORM_MINMAX);
        //std::cout<<"4"<<std::endl;
        
       

        cv::imshow("first",input);
        cv::imshow("second",normalized);

        cv::waitKey(0);

    }catch(std::exception &ex){
        std::cout<<ex.what()<<std::endl;
    }

}