#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

void applyKernel(const cv::Mat &in, cv::Mat &out, cv::Mat &kernel){

    int radius = kernel.rows /2;
    int size = kernel.cols;

    for(int y = 0;y<in.rows;y++){
        for(int x = 0;x<in.cols;x++){
            float value = 0.0;
            for(int j=(size*-1)+(size/2)+1;j<size-(size/2);j++){
                for(int i=(size*-1)+(size/2)+1;i<size-(size/2);i++){
                    if((y+j>=0) && (x+i>=0) && (y+j<in.rows) && (x+i<in.cols)){
                        value += in.at<uchar>(y+j,x+i)*kernel.at<float>(j+(size/2),i+(size/2));
                    }
                }
            }
            out.at<uchar>(y,x) = value;
        }
    }

}


int main(int argc, char **argv){
    
    if(argc!=2){
        std::cerr<<"nº args invalido."<<std::endl;
        return 0;
    }

    try{

        int size = 0;
        std::cout<<"Enter a odd numbre."<<std::endl;
        std::cin>>size;

        cv::Mat in;
        cv::Mat out;

        in = cv::imread(argv[1],cv::IMREAD_GRAYSCALE);
        out = cv::imread(argv[1],cv::IMREAD_GRAYSCALE);

        if(size%2==0){
            std::cout<<"the number is even."<<std::endl;
            return 0;
        }

        cv::Mat kernel(size,size,CV_32FC1);
        kernel = cv::Mat::ones(size,size,CV_32FC1)/(float)(size*size);

        applyKernel(in, out, kernel);

        cv::imshow("first",in);
        cv::imshow("secons",out);

        cv::waitKey(0);

    }catch(std::exception &ex){
        std::cout<<ex.what()<<std::endl;
    }

}