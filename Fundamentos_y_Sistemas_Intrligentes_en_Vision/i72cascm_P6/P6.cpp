/***********************************
 * Autor: Manuel Casas Castro (i72cascm@uco.es)
 * Universidad de Córdoba (Spain)
 * 
 * P6
 * 
 * ******************************************/

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <bits/stdc++.h> //sorting
using namespace std;
using namespace cv;

//this function take all the values of the kernel and sort them in an array.
//finally we set the pixel value as the median of this array

void medianFilter(const Mat &in,Mat &out,int size){

    Mat kernel(size,size, CV_32FC1);
    kernel=Mat::ones(size,size,CV_32FC1);

    int median = size*size/2;    

    int radius=(kernel.cols/2);

    //int pixelcount =0;

    for(int i=radius; i<in.rows-radius;i++){
        for(int j=radius;j<in.cols-radius;j++){
            //pixelcount++;
            int array[size*size] = {0};
            int n = sizeof(array) / sizeof(array[0]);
            int count = 0;

            for(int x=0; x<kernel.rows;x++){
                for(int y=0; y<kernel.cols;y++){
                    array[count] = in.at<uchar> (i+x-radius,j+y-radius);
                    count++;
                }
            }

            sort(array, array + n);

            //for (int p = 0; p < n; ++p)
            //cout <<"Pixel "<<pixelcount<<":"<<" PositionArray: "<<p<<" "<< array[p] << " "<<endl;

            out.at<uchar>(i,j)=array[median]; 


        }
    }

}

void boxFilter(const Mat &in, Mat &out, int size){

    Mat kernel(size,size, CV_32FC1);
    kernel=Mat::ones(size,size,CV_32FC1)/(float)(size*size);

    float value;


    int radius=(kernel.cols/2);
    //cout<<radius;


    for(int i=radius; i<in.rows-radius;i++){
        for(int j=radius;j<in.cols-radius;j++){

            value=0;


            for(int x=0; x<kernel.rows;x++){
                for(int y=0; y<kernel.cols;y++){
                    value += in.at<uchar> (i+x-radius,j+y-radius)*kernel.at<float>(x,y);
                }
            }
            out.at<uchar>(i,j)=value;        
        }
    }
}

int main(int argc, char **argv){


    //Arguments control
    if(argc!=2){cerr<<"Usage:image"<<endl;return 0;}

    try{

        //in image inicialization
        Mat in = imread(argv[1], IMREAD_GRAYSCALE);
        if(in.rows==0){
            cout<<"This is not a valid image."<<endl;
            return 0;
        }
    
        //Mat in;
        //first.convertTo(in,CV_32FC1);

        //out image inicialization
        Mat outMedian = in.clone();
        Mat outBox = in.clone();

        //input of the size
        int size;
        cout<<"Enter a size for median filter:"<<endl;
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

        //functions
        medianFilter(in, outMedian, size);
        boxFilter(in, outBox, size);

        //Mat normalized = out.clone();
        //normalize(out,normalized,100,NORM_MINMAX);

        //show result images
        imshow("Original", in);
        imshow("After Median filter",outMedian);
        imshow("After Box filter",outBox);

        
        char c;
        while(c!=27)  //waits until ESC pressed
	    c=cv::waitKey(0);

    }catch(std::exception &ex){
        cout<<ex.what()<<endl;
    }


}