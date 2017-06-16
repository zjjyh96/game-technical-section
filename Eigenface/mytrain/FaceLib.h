//
// Created by Jack Infinity on 2017/1/7.
//

#ifndef MYTRAIN_FACELIB_H
#define MYTRAIN_FACELIB_H

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
    void loadFace(string in);
    void getAveFace();
    void getEigen();
    void saveEigen(string in, int n);

private:
    vector<Face*> face;
    CvMat *image_points[1];
    Mat_<double>meanMat;
    Mat_<double>covMat;
    Mat_<double>sample[100];
    CvMat *covar_mat;
    CvMat *mean_mat;
    CvMat *eigen_value;
    CvMat *eigen_vector;
    CvMat *A;
    CvMat *eigen_image;
    int row;
    int col;
    int number;
    int eigen_number;
};


#endif //MYTRAIN_FACELIB_H
