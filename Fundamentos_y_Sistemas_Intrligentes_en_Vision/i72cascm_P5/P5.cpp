/***********************************
 * Autor: Manuel Casas Castro (i72cascm@uco.es)
 * Universidad de Córdoba (Spain)
 * 
 * P5
 * 
 * ******************************************/

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;
using namespace cv;


//this function take the radius of the kernel image and go across the matrix of the original image applying the high boost filter.
//PROBLEM: This function can not calculate the value for the pixel at the edges

void applyKernel(Mat &in, Mat &out, Mat &Kernel){

    float value;


    int radius=(Kernel.cols/2);
    //cout<<radius;


    for(int i=radius; i<in.rows-radius;i++){
        for(int j=radius;j<in.cols-radius;j++){

            value=0;


            for(int x=0; x<Kernel.rows;x++){
                for(int y=0; y<Kernel.cols;y++){
                    value += in.at<float> (i+x-radius,j+y-radius)*Kernel.at<float>(x,y);
                }
            }
            out.at<float>(i,j)=value;        
        }
    }

}



int main(int argc, char **argv){


    //Arguments control
    if(argc!=3){cerr<<"Usage:image && high boost filter value"<<endl;return 0;}

    try{

        //high boost filter value inicialization
        float c = stof(argv[2]);
        cout<<"c"<<c<<endl;

        //image inicialization
        Mat first = imread(argv[1], IMREAD_GRAYSCALE);
        

        if(first.rows==0){
            cout<<"This is not a valid image."<<endl;
            return 0;
        }
        
        Mat in;
        first.convertTo(in,CV_32FC1);

        //result inicialization
        Mat out = in.clone();


        //Matrix with the values of the high boost filter
        float highBoostArray[3][3] = {
            {-c,-c,-c},
            {-c,(8*c+1),-c},
            {-c,-c,-c},
        };

        //Blur img (low frequency)
        Mat lowF = in.clone();

        //Kernel img inicialization (1/3*3 in each pixel)
        Mat Kernel(3,3, CV_32FC1);
        Kernel=Mat::ones(3,3,CV_32FC1)/(float)(3*3);

        Mat kernelHighBoost = cv::Mat(3 ,3 ,CV_32FC1 , highBoostArray);
        //kernelHighBoost=Mat::ones(3,3,CV_32FC1)/(float)(9);

        //function to apply the high boost filter
        applyKernel(in, lowF, Kernel);

        Mat highF = in.clone();
        highF = in - lowF;
        Mat highFout = in.clone();

        applyKernel(highF, highFout ,kernelHighBoost );

        Mat result = in.clone();
        result = in + highFout;
        Mat normalized = result.clone();
        normalize(result,normalized,100,NORM_MINMAX);

        //show result images
        imshow("Original", first);
        imshow("After High Boost filter",normalized);
        
        

        char a;
        while(a!=27)  //waits until ESC pressed
	    a=cv::waitKey(0);

    }catch(std::exception &ex){
    cout<<ex.what()<<endl;
    }

}