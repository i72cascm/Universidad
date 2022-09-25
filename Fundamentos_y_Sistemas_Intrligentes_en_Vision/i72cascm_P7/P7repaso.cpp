//<>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <getopt.h>
#include <string>

void dilate(const cv::Mat &input, cv::Mat &output, const cv::Mat &kernel){

    int size = kernel.cols;

    for(int y=0;y<input.rows;y++){
        for(int x=0;x<input.cols;x++){
            float max = 0;
            for(int j=(size*-1)+(size/2)+1;j<size-(size/2);j++){
                for(int i=(size*-1)+(size/2)+1;i<size-(size/2);i++){
                    if((y+j>=0) && (x+i>=0) && (y+j<input.rows) && (x+i<input.cols)){
                        if(input.at<uchar>(y+j,x+i) > max){
                            max = input.at<uchar>(y+j,x+i);
                        }
                    }
                }
            }
            output.at<uchar>(y,x) = max;
        }
    }
}

void erode(const cv::Mat &input, cv::Mat &output, const cv::Mat &kernel){

    int size = kernel.cols;

    for(int y=0;y<input.rows;y++){
        for(int x=0;x<input.cols;x++){
            float min = 255;
            for(int j=(size*-1)+(size/2)+1;j<size-(size/2);j++){
                for(int i=(size*-1)+(size/2)+1;i<size-(size/2);i++){
                    if((y+j>=0) && (x+i>=0) && (y+j<input.rows) && (x+i<input.cols)){
                        if(input.at<uchar>(y+j,x+i) < min){
                            min = input.at<uchar>(y+j,x+i);
                        }
                    }
                }
            }
            output.at<uchar>(y,x) = min;
        }
    }
}

void applyThreshold(const cv::Mat &input, cv::Mat &output, const int threshold){

    for(int y=0;y<input.rows;y++){
        for(int x=0;x<input.cols;x++){
            if(input.at<uchar>(y,x) < threshold){
                output.at<uchar>(y,x) = 255;
            }else{
                output.at<uchar>(y,x) = 0;
            }
        }
    }

}

int main(int argc, char **argv){

    if(argc != 7){
        std::cerr<<"nº argumentos invalido."<<std::endl;
        return 0;
    }

    try{

        const struct option long_options[]={
            {"thres", required_argument, 0, 't'},
            {"op", required_argument, 0, 'o'},
            {0,0,0},
        };

        int longindex;
        int c = 0;

        std::string threshold_argument;
        std::string operation_argument;

        bool flag = false;

        cv::Mat input = cv::imread(argv[1],cv::IMREAD_GRAYSCALE);
        std::string save = argv[2];

        while((c=getopt_long(argc,argv,"t:o:", long_options, &longindex)) != -1){
            switch(c){
                case 't':
                    threshold_argument = optarg;
                break;

                case 'o':
                    operation_argument = optarg;
                break;
            }
        }

        int threshold = stoi(threshold_argument);

        int n;
        std::cout<<"Introduce valor de n (impar)"<<std::endl;
        std::cin>>n;

        if(n%2==0){
            std::cout<<"no es impar"<<std::endl;
            return 0;
        }                          

        cv::Mat kernel(n,n,CV_32FC1);
        kernel = cv::Mat::ones(n,n,CV_32FC1);

        cv::Mat thresholdedImage = input.clone();

        applyThreshold(input,thresholdedImage,threshold);
        cv::namedWindow("thresholded");
        cv::imshow("thresholded",thresholdedImage);

        cv::Mat result = input.clone();
        cv::Mat aux = input.clone();

        if(operation_argument == "erode"){
            erode(thresholdedImage,result,kernel);
            flag = true;
            cv::imshow("eroded",result);
        }

        if(operation_argument == "dilate"){
            dilate(thresholdedImage,result,kernel);
            flag = true;
            cv::imshow("dilate",result);
        }

        if(operation_argument == "open"){
            erode(thresholdedImage,aux,kernel);
            dilate(aux,result,kernel);
            flag = true;
            cv::imshow("open",result);
        }

        if(operation_argument == "close"){
            dilate(thresholdedImage,aux,kernel);
            erode(aux,result,kernel);
            flag = true;
            cv::imshow("close",result);
        }

        if(flag == false){
            std::cout<<"operacion mal escrita"<<std::endl;
            return 0;
        }

        cv::imwrite(save, result);

        cv::waitKey(0);

    }catch(std::exception &ex){
        std::cout<<ex.what()<<std::endl;
    }

}