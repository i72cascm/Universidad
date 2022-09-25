#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <getopt.h>
using namespace std;
using namespace cv;

//apply threshold
void applyThreshold(const Mat &in, Mat &out,int thresvalue){
    
    cout<<thresvalue<<endl;
    for(int i=0; i<in.rows;i++){
    for(int j=0;j<in.cols;j++){
        
            if((in.at<uchar> (i,j))<thresvalue){
                out.at<uchar>(i,j)=255;
            }else{
                out.at<uchar>(i,j)=0;
            }
        }
    }
}

//apply erode filter
void erode(const Mat &in, Mat &out, Mat &kernel){
float value;
int radius=(kernel.cols/2);

//Edges not included
    for(int i=radius; i<in.rows-radius;i++){
        for(int j=radius;j<in.cols-radius;j++){
            value=255;
            for(int x=0; x<kernel.rows;x++){
                for(int y=0; y<kernel.cols;y++){
                    if(in.at<uchar> (i+x-radius,j+y-radius)<value){
                        value=in.at<uchar> (i+x-radius,j+y-radius);
                    }
                }
            }
            out.at<uchar>(i,j)=value;        
        }
    }
}

//apply dilate filter
void dilate(const Mat &in, Mat &out, Mat &kernel){
float value;
int radius=(kernel.cols/2);

//Edges not included
    for(int i=radius; i<in.rows-radius;i++){
        for(int j=radius;j<in.cols-radius;j++){
            value=0;
            for(int x=0; x<kernel.rows;x++){
                for(int y=0; y<kernel.cols;y++){
                    if(in.at<uchar> (i+x-radius,j+y-radius)>value){
                        value=in.at<uchar> (i+x-radius,j+y-radius);
                    }
                }
            }
            out.at<uchar>(i,j)=value;        
        }
    }
}


int main(int argc, char **argv){

    if(argc!=7){
        cerr<<"Usage:URL image -thres value -op opcion"<<endl;
        return 0;
    }

    // Process arguments of the command line
    const struct option longopts[] =
{
    {"file",   required_argument,        0, 'f'},  
    {"thres",   required_argument,        0, 't'},
    {"op",      required_argument,        0, 'o'},
    {0,0,0,0},
};

int index;
int iarg=0;


//turn off getopt error message
char *tvalue = NULL, *ovalue = NULL, *fvalue=NULL;
opterr=1; 

while(iarg != -1)
{
    iarg = getopt_long(argc, argv, "f:t:o:", longopts, &index);

    switch (iarg)
    {
    case 'f':
        fvalue = optarg;
        break;
        
    case 't':
        tvalue = optarg;
        break;

    case 'o':
        ovalue = optarg;
        break;

    }
}

    try{

        cout<<argv[2]<<endl;
        //image inicialization
        Mat in = imread(argv[2], IMREAD_GRAYSCALE);
        
        if(in.rows==0){
            cout<<"This is not a valid image."<<endl;
            return 0;
        }

        //result inicialization
        Mat inThreshold = in.clone();

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

        Mat kernel(size,size, CV_32FC1);
        kernel=Mat::ones(size,size,CV_32FC1);

        int thresvalue = stoi(tvalue);
        applyThreshold(in, inThreshold,thresvalue);
        
        Mat out= inThreshold.clone();
        Mat outThreshold = inThreshold.clone();

        //if -op = open lanzar primero el que toque y luego el otro
        //if -op = closing al contrario
        //if -op uno solo pues solo ese
    
        String select = string(ovalue);

        if(select=="erode"){
            erode(inThreshold,out,kernel);
            imshow("Original", in);
            imshow("Filtered", out);
            imwrite("erode.jpg",out);
        }      
        if(select=="dilate"){
            dilate(inThreshold,out,kernel);
            imshow("Original", in);
            imshow("Filtered", out);
            imwrite("dilate.jpg",out);
        }
        if(select=="open"){
            erode(inThreshold,outThreshold,kernel);
            out = outThreshold.clone();
            dilate(outThreshold,out,kernel);
            imshow("Original", in);
            imshow("Filtered", out);
            imwrite("open.jpg",out);
        }
        if(select=="close"){
            dilate(inThreshold,outThreshold,kernel);
            out = outThreshold.clone();
            erode(outThreshold,out,kernel);
            imshow("Original", in);
            imshow("Filtered", out);
            imwrite("close.jpg",out);
        }

        
        
        
        char a;
        while(a!=27)  //waits until ESC pressed
        a=cv::waitKey(0);

    }catch(std::exception &ex){
        cout<<ex.what()<<endl;
    }

}
