/***********************************
 * Autor: Manuel Casas Castro (i72cascm@uco.es)
 * Universidad de Córdoba (Spain)
 * 
 * P3
 * 
 * ******************************************/

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h>
#include <iostream>
using namespace std;
using namespace cv;


//this function take the radius of the kernel image and go across the matrix of the original image making the sum of the final result for each pixel.


//PROBLEM: This function can not calculate the value for the pixel at the edges

void applyKernel(Mat &in, Mat &out, Mat &Kernel){

    float value;


    int radius=Kernel.cols/2;
    //cout<<radius;


    for(int y=0; y<in.rows;y++){ //i
        for(int x=0;x<in.cols;x++){ //j
            value=0;
            for(int j=0; j<Kernel.rows;j++){ //x
                for(int i=0; i<Kernel.cols;i++){ //y
                    if((x+i>=radius) && (y+j>=radius) && (x+radius-i<in.cols) && (y+radius-j<in.rows) ){
                        value += in.at<uchar> (y+j-radius,x+i-radius)*Kernel.at<float>(j,i);
                    }
                }
            }
            out.at<uchar>(y,x)=value;        
        }
    }
}

int main(int argc, char **argv){


    //Arguments control
    if(argc!=2){cerr<<"Usage:image"<<endl;return 0;}

    try{

        //image inicialization
        Mat in = imread(argv[1], IMREAD_GRAYSCALE);

        if(in.rows==0){
            cout<<"This is not a valid image."<<endl;
            return 0;
        }

        //result inicialization
        Mat out = in.clone();
        

        //the variable size is the dimension (NxN) of the box filter
        int size;

        //size must be a number
        cout<<"Enter a number. The box filter will be NxN where N is that number."<<endl;
        while(!(cin>>size)){
            cout<<"Error: a number must be entered:"<<endl;
            cin.clear();
            cin.ignore(123,'\n');
        }

        //size must be odd
        if(size%2 == 0){
            cout<<"Error: the box filter is not odd."<<endl;
            return 0;
        }

        //Kernel img inicialization (1/size*size in each pixel)
        Mat Kernel(size,size, CV_32FC1);
        Kernel=Mat::ones(size,size,CV_32FC1)/(float)(size*size);
        
        /*for(int i=0; i<Kernel.rows;i++){
            for(int j=0;j<Kernel.cols;j++){
                Kernel.at<uchar>(i,j)=1/(size*size);
                    
            }
        }*/

        //function to blur the image
        applyKernel(in, out, Kernel);

        //show result images
        imshow("Original", in);
        imshow("After box filter",out);

        char c;
        while(c!=27)  //waits until ESC pressed
	    c=cv::waitKey(0);

    }catch(std::exception &ex){
    cout<<ex.what()<<endl;
    }
    

}