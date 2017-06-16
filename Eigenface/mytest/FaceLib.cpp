//
// Created by Jack Infinity on 2017/1/7.
//

#include "FaceLib.h"

FaceLib::FaceLib() {
}

FaceLib::~FaceLib() {
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



void FaceLib::testFace(int recn) {

    CvMat* At = cvCreateMat(eigen_number, row * col, CV_64FC1);
    cvTranspose(A, At);
    int total=rec_face.size();
    int correct=0;

    for(int t = 0; t < rec_face.size(); t ++) {
        //cvNamedWindow(rec_face[t]->name);
        CvMat* rec = cvCreateMat(row * col, 1, CV_64FC1);
        for(int i = 0; i < row; i ++)
            for(int j = 0; j < col; j++)
                CV_MAT_ELEM(*rec, double, i*col+j, 0) = CV_MAT_ELEM(*rec_face[t]->data, double, i, j);
        rec_face[t]->eigen = cvCreateMat(eigen_number, 1, CV_64FC1);
        cvMatMul(At, rec, rec_face[t]->eigen);

        double min[100];
        int min_index[100];

//        求识别图像权重矢量与各个人脸权重矢量的距离
        for(int i = 0; i < recn; i ++) {
            min[i] = cvNorm(face[i]->eigen, rec_face[t]->eigen, CV_L2);
            min_index[i] = i;
        }
//        寻找距离最小的人脸图像
        for(int i = recn; i < face.size(); i ++) {
            double dis = cvNorm(face[i]->eigen, rec_face[t]->eigen, CV_L2);
            if(dis < min[recn - 1]) {
                for(int j = 0; j <recn; j ++){
                    if(dis < min[j]){
                        for(int k = recn - 1; k > j; k --) { min[k] = min[k - 1]; min_index[k] = min_index[k - 1];}
                        min[j] = dis;
                        min_index[j] = i;
                        j = recn;
                    }
                }
            }
        }

        cout<<"Test people: "<<rec_face[t]->name<<endl;
        string test=rec_face[t]->name;
        string reco=face[min_index[0]]->name;
        if ((test[0]==reco[0]) && (test[1]==reco[1]) && (test[2]==reco[2])) correct++;
        for(int i = 0; i < recn; i ++)
            cout<<"Result =  "<<face[min_index[i]]->name<<"; dis = "<<min[i]<<endl;
    }
    cout<<"The Ratio is "<<correct*1.0/total<<endl;
}




