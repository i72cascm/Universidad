//<>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

void applyGradient(const cv::Mat resultX, const cv::Mat resultY, cv::Mat output){

    for(int y=0;y<output.rows;y++){
        for(int x=0;x<output.cols;x++){
            float Grx = resultX.at<float>(y,x);
            float Gry = resultY.at<float>(y,x);
            output.at<float>(y,x) = sqrt(pow(Grx,2)+pow(Gry,2));
        }
    }

}

void applyKernel(const cv::Mat &input, cv::Mat &output, const cv::Mat kernel){

    int size = kernel.cols;

    for(int y=0;y<input.rows;y++){
        for(int x=0;x<input.cols;x++){
            float value = 0.0;
            for(int j=((size*-1)+(size/2)+1);j<(size-(size/2));j++){
                for(int i=((size*-1)+(size/2)+1);i<(size-(size/2));i++){
                    if((y+j>=0) && (x+i>=0) && (y+j<input.rows) && (x+i<input.cols)){
                        value += input.at<float>(y+j,x+i)*kernel.at<float>(j+(size/2),i+(size/2));
                    }
                }
            }
            output.at<float>(y,x) = value;
        }
    }

}

int main(int argc, char **argv){

    if(argc != 2){
        std::cerr<<"nº args invalido"<<std::endl;
        return 0;
    }

    try{

        cv::Mat original = cv::imread(argv[1],cv::IMREAD_GRAYSCALE);
        cv::Mat input;
        original.convertTo(input,CV_32FC1);
        cv::Mat resultX;
        resultX = input.clone();
        cv::Mat resultY;
        resultY = input.clone();

        float sobelX[] = {-1, 0 ,1,
                          -2, 0 ,2,
                          -1, 0 ,1};

        float sobelY[] = {1, 2, 1,
                          0, 0, 0,
                         -1, -2, -1};

        cv::Mat kernelX(3,3,CV_32FC1,sobelX);
        cv::Mat kernelY(3,3,CV_32FC1,sobelY);
        
        cv::Mat output = input.clone();

        applyKernel(input,resultX,kernelX);
        applyKernel(input,resultY,kernelY);
        applyGradient(resultX,resultY,output);

        cv::Mat normalized = input.clone();
        cv::normalize(output,normalized,100,cv::NORM_MINMAX);

        cv::imshow("result",normalized);
        //cv::imshow("original",original);

        cv::waitKey(0);

    }catch(std::exception &ex){
        std::cout<<ex.what()<<std::endl;
    }

}