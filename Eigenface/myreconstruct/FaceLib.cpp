//
// Created by Jack Infinity on 2017/1/7.
//

#include "FaceLib.h"

FaceLib::FaceLib() {
}

FaceLib::~FaceLib() {
}

double* img2double(IplImage* img){
    CvMat* im = cvCreateMat(img->height, img->width, CV_64FC1);
    cvConvert(img, im);
    double* d = im->data.db;
    return d;
}

void FaceLib::loadLibrary(string in){
//    加载矩阵A
    char* A_src = new char[100];
    sprintf(A_src, "%s/A.xml", in.data());
    A = (CvMat*)cvLoad(A_src);

//    加载每个脸的数据
    DIR* dir = NULL;
    char* face_src = new char[100];
    sprintf(face_src, "%s/face", in.data());

    dir = opendir(face_src);

    dirent* ent = NULL;
    if(dir == NULL) return;

    while((ent = readdir(dir))!=NULL) {
        char* suffix = new char[100];
        char* name = new char[100];
        sscanf(ent->d_name,"%*[^.].%s", suffix);
        sscanf(ent->d_name,"%[^.]%*s", name);
        if(strcmp(suffix, "xml")==0) {
            Face* f= new Face();
            f->name = name;
            char* img_src = new char[100];
            sprintf(img_src,"%s/face/%s",in.data(),ent->d_name);
            CvMat* img =(CvMat*)cvLoad(img_src);
            f->eigen = img;
            face.push_back(f);
        }
    }

//    获取其他基础数据
    number = face.size();
    eigen_number = face[0]->eigen->rows;

}

//加载需要识别的图片文件
void FaceLib::loadRecFace(string in){
    DIR* dir = NULL;
    dir = opendir(in.data());

    dirent* ent = NULL;

    if(dir == NULL) return;

    while((ent = readdir(dir))!=NULL) {
        char* suffix = new char[100];
        char* name = new char[100];
        sscanf(ent->d_name,"%*[^.].%s", suffix);
        sscanf(ent->d_name,"%[^.]%*s", name);
        if(strcmp(suffix, "pgm")==0) {
            Face* f= new Face();
            f->name = name;
            char* img_src = new char[100];
            sprintf(img_src,"%s/%s",in.data(),ent->d_name);
            IplImage* d = cvLoadImage(img_src, CV_LOAD_IMAGE_GRAYSCALE);
            CvMat* mat = cvCreateMat(d->height, d->width, CV_64FC1);
            cvConvert(d, mat);
            f->data = mat;
            rec_face.push_back(f);
        }
    }
    row = rec_face[0]->data->rows;
    col = rec_face[0]->data->cols;
}


//计算待重构人脸的特征空间权重值
void FaceLib::calcEigen(){

    CvMat* At = cvCreateMat(eigen_number, row * col, CV_64FC1);
    cvTranspose(A, At);

    //cvNamedWindow(rec_face[t]->name);
    CvMat* rec = cvCreateMat(row * col, 1, CV_64FC1);
    for(int i = 0; i < row; i ++)
        for(int j = 0; j < col; j++)
            CV_MAT_ELEM(*rec, double, i*col+j, 0) = CV_MAT_ELEM(*rec_face[0]->data, double, i, j);
    rec_face[0]->eigen = cvCreateMat(eigen_number, 1, CV_64FC1);
    cvMatMul(At, rec, rec_face[0]->eigen);
    for (int i=0;i<100;i++){
        double j=CV_MAT_ELEM(*rec_face[0]->eigen, double, i,0);
        printf("%f ",j);
    }
    printf("\n");

}

//进行人脸重构
void FaceLib::recFace(int k, string in) {

    new_face = cvCreateMat(row, col, CV_64FC1);
    CvMat *face2 = cvCreateMat(row, col, CV_64FC1);
    for(int i = 0; i < row; i ++)
        for(int j = 0; j < col; j ++) {
            CV_MAT_ELEM(*new_face, double,i,j) =0;
        }


    for(int t = 0; t < k; t ++) {

        for(int i = 0; i < row; i ++)
            for(int j = 0; j < col; j ++) {
                CV_MAT_ELEM(*new_face, double,i,j) +=
                        CV_MAT_ELEM(*rec_face[0]->eigen, double, t, 0)*CV_MAT_ELEM(*A, double, i * col + j, t);
            }

        if(t==9||t==24||t==49||t==99)
        {
            //  对特征人脸矩阵均衡化为0-255
            cvNormalize(new_face, face2, 255.0, 0.0, CV_MINMAX);
            printf("finish normalize\n");

            //  将特征人脸转化为图像格式后储存
            IplImage* new_img = cvCreateImage(cvSize(col, row), 8, 1);
            cvConvert(face2, new_img);
            printf("finish convert\n");

            char* img_src = new char[100];
            sprintf(img_src, "%s/recimage%d.pgm", in.data(), t+1);
            cvSaveImage(img_src, new_img);
        }


    }

}




