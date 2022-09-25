//code for invert an image

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;

int main(int argc, char **argv){

    try{

        cv::Mat image = imread(argv[1],cv::IMREAD_GRAYSCALE);

        for(int y = 0; y<image.rows;y++){
            uchar *ptr = image.ptr<uchar>(y);
            for(int x = 0; x<image.cols;x++){
                ptr[x] = 255 - ptr[x];
            }
        }

        imwrite("inverted.jpg", image);

    }catch (exception &ex){
        cout<<ex.what()<<endl;
    }
    



}