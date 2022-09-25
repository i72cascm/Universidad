/***********************************
 * Autor: Manuel Casas Castro (i72cascm@uco.es)
 * Universidad de Córdoba (Spain)
 * 
 * P4
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


//this function take the radius of the kernel image and go across the matrix of the original image applying the Sovel filter.
//PROBLEM: This function can not calculate the value for the pixel at the edges

void applySovelKernel(Mat &in, Mat &out, Mat &KernelA, Mat &KernelB){

    float GradientA;
    float GradientB;
    float Magnitude;


    int radius=(KernelA.cols/2);
    //cout<<radius;

    //We go across the matrix (no edges included)
    for(int i=radius; i<in.rows-radius;i++){
        for(int j=radius;j<in.cols-radius;j++){

            GradientA=0;
            GradientB=0;

            //We make the sum like the last assignement, but we do it twice, one for each Sovel Kernel (X,Y)
            for(int x=0; x<KernelA.rows;x++){
                for(int y=0; y<KernelA.cols;y++){
                    GradientA += in.at<uchar> (i+x-radius,j+y-radius)*KernelA.at<float>(x,y);
                }
            }
            

            for(int x=0; x<KernelB.rows;x++){
                for(int y=0; y<KernelB.cols;y++){
                    GradientB += in.at<uchar> (i+x-radius,j+y-radius)*KernelB.at<float>(x,y);
                }
            }

            //Once calculated the gradients, we take the magnitude and set the result as the new value of the pixel
            Magnitude= sqrt(pow(GradientA,2)+pow(GradientB,2));
            
            
            //cout<<result<<endl;
            out.at<uchar>(i,j)=Magnitude;          
        }
    }
}

int main(int argc, char **argv){


    //Arguments control
    if(argc!=2){cerr<<"Usage:image"<<endl;return 0;}

    try{


        //image inicialization
        Mat image = imread(argv[1]);
        Mat in;
        cvtColor( image, in, COLOR_BGR2GRAY );


        Mat out;

        if(in.rows==0){
            cout<<"This is not a valid image."<<endl;
            return 0;
        }

        //result inicialization
        Mat dst = in.clone();
        normalize(dst, out, 255, 230, NORM_MINMAX,-1, noArray());

        //Vector that contain the Sovel filter values
        float SovelArrayA[3][3] = {
        { -1, 0, 1},
        { -2, 0, 2},
        { -1, 0 ,1},
        };

        Mat KernelA = cv::Mat(3, 3, CV_32FC1, &SovelArrayA);
        

        float SovelArrayB[3][3] = {
        { -1, -2, -1},
        { 0, 0, 0},
        { 1, 2 ,1},
        };

        Mat KernelB = cv::Mat(3, 3, CV_32FC1, &SovelArrayB);
        

        //function to apply the Sovel filter
        applySovelKernel(in, out, KernelA,KernelB);
        
        //show result images
        imshow("Original", in);
        imshow("After Sovel filter",out);
   

        char c;
        while(c!=27)  //waits until ESC pressed
	    c=cv::waitKey(0);

    }catch(std::exception &ex){
    cout<<ex.what()<<endl;
    }

}