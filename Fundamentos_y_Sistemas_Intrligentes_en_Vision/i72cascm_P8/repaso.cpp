//<>

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

    /*Parametros
    input image = image
    camera matrix = camera
    distorsion = dist_coefs
    point to be projected = obj_pts;
    size() = ??
    */  

    vector<Point3f> obj_pts;
    for(int y=0;y<rows-1;y++){
        for(int x=0;x<cols-1;x++){
            obj_pts.push_back(Point3f(x,y,0));
        }
    }

    while(video.grab()){

        Mat grayscale;
        vector<Point2f> corners;

        video.retrieve(image);

        if(findChessboardCorners(image,Size(cols-1,rows-1),corners)){

            cvtColor(image,grayscale,COLOR_BGR2GRAY);

            cornerSubPix(grayscale,corners,Size(11,11),Size(-1,-1),TermCriteria(TermCriteria(TermCriteria::COUNT | TermCriteria::EPS,20,0.03)));

            Mat rotation;
            Mat traslation;

            solvePnP(obj_pts, corners, camera, dist_coefs, rotation, traslation);

            vector<Point3f> points3d;
            vector<Point2f> puntosRespuesta;

            points3d.push_back(Point3f(0,0,0));
            points3d.push_back(Point3f(size,0,0));
            points3d.push_back(Point3f(0,size,0));
            points3d.push_back(Point3f(0,0,-size));

            projectPoints(points3d,rotation,traslation,camera,dist_coefs,puntosRespuesta);

            line(image,puntosRespuesta[0],puntosRespuesta[1],Scalar(255,0,0),6);
            line(image,puntosRespuesta[0],puntosRespuesta[2],Scalar(0,255,0),6);
            line(image,puntosRespuesta[0],puntosRespuesta[3],Scalar(0,0,255),6);

        }

        imshow("image",image);
        waitKey(10);

    }

}