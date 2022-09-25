/***********************************
 * Autor: Manuel Casas Castro (i72cascm@uco.es)
 * Universidad de Córdoba (Spain)
 * 
 * P8
 * 
 * ******************************************/

#include <iostream>
#include <exception>
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
using namespace std;
using namespace cv;

int main(int argc,char **argv){

    //var inicializations
    int rows = stoi(argv[1]);
    int cols = stoi(argv[2]);
    float size = stof(argv[3]);
    String intrinsics = argv[4];
    String input_video = argv[5];

    //Video control and inicialization
    VideoCapture video;
    video.open(input_video);
    if (! video.isOpened()){
        cout<<"Error opening the video."<<endl;
        return 0;
    }
        

    Mat image; //frames

    FileStorage intr(intrinsics, FileStorage::READ);
    if(!intr.isOpened()){
        cout<<"Error opening the intrinsics file."<<endl;
        return 0;
    }

    Mat camera;
    Mat dist_coefs;
    intr["camera_matrix"] >> camera;
    intr["distorsion_coefficients"] >> dist_coefs;

    vector<Point3f> obj_pts;
    for(int i=0;i<rows-1;i++){
        for(int j=0;j<cols-1;j++){
            obj_pts.push_back(Point3f(j*size,i*size,0));
        }
    }


    while(video.grab()){

        Mat grayscale;
        vector<Point2f> corners;

        video.retrieve(image);

        if(findChessboardCorners(image, Size(cols-1,rows-1), corners, CALIB_CB_FAST_CHECK)){
            
            //frame to gray scale
            cvtColor(image, grayscale, COLOR_BGR2GRAY);

            //refine corners
            cornerSubPix(grayscale, corners, Size(11,11), Size(-1,-1), TermCriteria(TermCriteria(TermCriteria::COUNT | TermCriteria::EPS, 20, 0.03)));
            
            //Estimate camera pose
            Mat rotation;
            Mat traslation;
            solvePnP(obj_pts, corners, camera, dist_coefs, rotation, traslation);
            
            //Proyect
            vector<Point3f> points3d;
            vector<Point2f> puntosRespuesta;

            
            points3d.push_back(Point3f(0,0,0));
            points3d.push_back(Point3f(size,0,0));
            points3d.push_back(Point3f(0,size,0));
            points3d.push_back(Point3f(0,0,-size));

            projectPoints(points3d, rotation, traslation, camera, dist_coefs, puntosRespuesta);

            line(image, puntosRespuesta[0], puntosRespuesta[1], Scalar(0,0,255), 6); //Blue
            line(image, puntosRespuesta[0], puntosRespuesta[2], Scalar(0,255,0), 6); //Green
            line(image, puntosRespuesta[0], puntosRespuesta[3], Scalar(255,0,0), 6); //Red

        }

        imshow("image",image);
        waitKey(10);
    }

}
