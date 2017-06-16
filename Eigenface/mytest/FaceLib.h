//
// Created by Jack Infinity on 2017/1/7.
//

#ifndef MYTEST_FACELIB_H
#define MYTEST_FACELIB_H

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
    void testFace(int recn);

private:
    vector<Face*> face;
    vector<Face*> rec_face;
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


#endif //MYTEST_FACELIB_H
