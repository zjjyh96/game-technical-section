//
// Created by Jack Infinity on 2017/1/17.
//

#ifndef MYRECONSTRUCT_FACELIB_H
#define MYRECONSTRUCT_FACELIB_H


#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

using namespace std;
using namespace cv;

struct Face{
    char* name;
    CvMat* data;
    CvMat* eigen;
};

class FaceLib{
public:
    FaceLib();
    ~FaceLib();
    void loadLibrary(string in);
    void loadRecFace(string in);
    void recFace(int k,string in);
    void calcEigen();

private:
    vector<Face*> face;
    vector<Face*> rec_face;
    CvMat *image_points[1];
    Mat_<double>meanMat;
    Mat_<double>covMat;
    Mat_<double>sample[100];
    CvMat *A;
    CvMat *eigen_image;
    CvMat *new_face;
    int row;
    int col;
    int number;
    int eigen_number;
};


#endif //MYRECONSTRUCT_FACELIB_H
