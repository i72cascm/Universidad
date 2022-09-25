#include <iostream>
#include <exception>
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
using namespace std;
using namespace cv;
    /*Parametros
    input image = image
    camera matrix = camera
    distorsion = dist_coefs
    point to be projected = obj_pts;
    size() = ??
    */  

vector<Point2f> NombreFuncion(&parametros,&parametros){

    vector<Point3f> obj_pts;
    for(int y=0;y<rows-1;y++){
        for(int x=0;x<cols-1;x++){
            obj_pts.push_back(Point3f(x,y,0));
        }
    }

    Mat grayscale;
    vector<Point2f> corners;

    if(findChessboardCorners(imageinput, Size(cols-1,rows-1), corners,CALIB_CB_FAST_CHECK)){

        //Se pasa a gris
        cvtColor(image,grayscale,COLOR_BGR2GRAY);

        //Cuando se tiene en gris se refinan las corners
        cornerSubPix(grayscale,corners ,Size(11,11), Size(-1,-1), TermCriteria(TermCriteria(TermCriteria::COUNT | TermCriteria::EPS, 20, 0.03) )
    
        //Cuando se tienen las corners se estiman la pose
        Mat distorsion;
        Mat traslacion;
        solvePnP(obj_pts, corners, camera, dist_coefs, distorsion, traslacion);

        //Projectas los puntos en el tablero
        vector<Point3f> points3d;
        vector<Points2f> puntosRespuesta;

        points3d.push_back(Point3f(0,0,0));
        points3d.push_back(Point3f(size,0,0));
        points3d.push_back(Point3f(0,size,0));
        points3d.push_back(Point3f(0,0,-size));

        projectPoints(points3d, rotation, traslation, camera, dist_coefs, puntosRespuesta);

        //dibujo
        line(image, puntosRespuesta[0], puntosRespuesta[1], Scalar(0,0,255), 6); //Blue
        line(image, puntosRespuesta[0], puntosRespuesta[2], Scalar(0,255,0), 6); //Green
        line(image, puntosRespuesta[0], puntosRespuesta[3], Scalar(255,0,0), 6); //Red

        //imshow
        //waitKey
        return puntosRespuesta;    
    }
}