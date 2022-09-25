/***********************************
 * Autor: Manuel Casas Castro (i72cascm@uco.es)
 * Universidad de Córdoba (Spain)
 * 
 * P1
 * 
 * ******************************************/

#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow namedWindow,waitKey
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;


cv::Mat image;
cv::Mat swapPictures;
cv::Mat final;


void create(int v[]){
    
    cv::Mat newWindow = cv::Mat::zeros(image.size(), image.type());
    cv::Mat v2;

    image.copyTo(v2);
    for (int i = 0; i < v2.rows; ++i){
		for (int j = 0; j < v2.cols; ++j){
			cv::Vec3b color = v2.at<cv::Vec3b>(cv::Point(j, i));
			float val= color[0] + color[1] + color[2];
			val = val/3;
			color[0] = val;
			color[1] = val;
			color[2] = val;
			v2.at<cv::Vec3b>(cv::Point(j, i))= color;
		}
	}
    std::vector<std::vector<cv::Point>> vertices;
	vertices.push_back(std::vector<cv::Point>());

    //Setting the vertex of the picture

	vertices[0].push_back(cv::Point(v[0], v[1]));
	vertices[0].push_back(cv::Point(v[2], v[1]));
	vertices[0].push_back(cv::Point(v[2], v[3]));
	vertices[0].push_back(cv::Point(v[0], v[3]));

    //Generate the new modified window

	cv::fillPoly(newWindow, vertices, cv::Scalar(255, 255, 255));
	cv::bitwise_and(image, newWindow, swapPictures);
	cv::bitwise_not(newWindow, newWindow);
	cv::Mat monocroma;
	cv::bitwise_and(v2, newWindow, monocroma);
	cv::Mat solucion;
	cv::bitwise_or(swapPictures, monocroma, solucion);
	cv::namedWindow("Changed Picture");
	cv::imshow( "Changed Picture" , solucion);
}

void black_white( int event, int x, int y, int flags, void* puntos){
    
//In this function, I put a few logical elementes (if), where I take the positions of x and y element when the left part of the mouse is clicked and the positions when the click is released.

    int* punt = (int*)puntos;
    if(event==cv::EVENT_LBUTTONDOWN){

        punt[0]=x;
        punt[1]=y;

    }
    else if(event==cv::EVENT_LBUTTONUP){

        punt[2]=x;
        punt[3]=y;

        //Once we have all the points, we call the function create which is the responsable for create a newWindow windows with the modified picture.
        create(punt);
    }
}

int main(int argc, char **argv){

    int puntos[4];

    try{


        //Arguments control
        if(argc!=2){cerr<<"Usage:image"<<endl;return 0;}

        //Load img
        image=cv::imread(argv[1]);
        if(image.rows==0){cerr<<"Error reading the image."<<endl;return 0;}

        //creates a window
        cv::namedWindow("myimage");

        //indicates that the on_mouse function should be called in case of mouse moved or pressed over window
        cv::setMouseCallback( "myimage", black_white, &puntos );

        //shows image
        cv::imshow("myimage",image);

        char c=0;
        while(c!=27)  //waits until ESC pressed
	    c=cv::waitKey(0);

    }catch(std::exception &ex){
        cout<<ex.what()<<endl;
    }
}