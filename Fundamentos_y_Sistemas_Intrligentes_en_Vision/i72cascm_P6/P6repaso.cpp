//<>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

void medianFilter(const cv::Mat &input, cv::Mat &output, int n){

    int size = n*n;

    std::vector<uchar> array;

    for(int y=0;y<input.rows;y++){
        for(int x=0;x<input.cols;x++){
            for (int j=((size*-1)+(size/2)+1);j<(size-(size/2));j++){
                for(int i=((size*-1)+(size/2)+1);i<(size-(size/2));i++){
                    if((y+j>=0) && (x+i>=0) && (y+j<input.rows) && (x+i<input.cols)){
                        array.push_back(input.at<uchar>(y+j,x+i));
                    }else{
                        array.push_back(0);
                    }
                }
            }

            sort(array.begin(),array.end()),
            output.at<uchar>(y,x) = array[array.size()/2];
            array.clear();

        }
    } 

}

int main(int argc, char** argv){

    if(argc != 2){
        std::cerr<<"nº args invalido."<<std::endl;
        return 0;
    }

    
    try{

        int size = 0;
        std::cout<<"insert size"<<std::endl;
        std::cin>>size;

        if(size%2==0){
            std::cout<<"debe ser impar"<<std::endl;
            return 0;
        }

        cv::Mat input = cv::imread(argv[1],cv::IMREAD_GRAYSCALE);
        cv::Mat output = input.clone();

        medianFilter(input, output, size);

        cv::namedWindow("original");
        cv::imshow("original",input);

        cv::namedWindow("median filter");
        cv::imshow("median filter",output);

        cv::waitKey(0);

    }catch(std::exception &ex){

        std::cout<<ex.what()<<std::endl;

    }

}