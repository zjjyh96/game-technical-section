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


//加载人脸库
void FaceLib::loadFace(string in){
    printf("start loadFace\n");
    DIR* dir = NULL;
//    打开路径内的文件
    dir = opendir(in.data());

    dirent* ent = NULL;

    if(dir == NULL) return;

//    读取图片文件
    while((ent = readdir(dir))!=NULL) {
        char* suffix = new char[100];
        char* name = new char[100];
        sscanf(ent->d_name,"%*[^.].%s", suffix);
        sscanf(ent->d_name,"%[^.]%*s", name);
//        若后缀为pgm格式
        if(strcmp(suffix, "pgm")==0) {
            Face* f= new Face();
//            保存图片的名称
            f->name = name;
            char* img_src = new char[100];
            sprintf(img_src,"%s/%s",in.data(),ent->d_name);
//            保存图片内容
            IplImage* d = cvLoadImage(img_src, CV_LOAD_IMAGE_GRAYSCALE);
            CvMat* mat = cvCreateMat(d->height, d->width, CV_64FC1);
//            将图片转化为Mat格式的矩阵，方便后续运算
            cvConvert(d, mat);
//            将图片矩阵存入f
            f->data = mat;
            face.push_back(f);
        }
    }

//    保存这个库里面图片的长宽以及人脸数量
    row = face[0]->data->rows;
    col = face[0]->data->cols;
    number = face.size();

    printf("load end\n");
}

//得到平均人脸
void FaceLib::getAveFace() {
    printf("start getAveFace\n");
    int k = number;
    int m = row;
    int n = col;

    printf("%d %d %d\n", k, m, n);

//将人脸图像展开成m*n的向量，并将k张人脸向量叠加成矩阵
    image_points[0] = cvCreateMat(k, m*n, CV_64FC1);
    for(int num = 0; num < k; num ++) {
        for(int i = 0; i < m; i ++)
            for(int j = 0; j < n; j ++){
                CV_MAT_ELEM(*image_points[0], double, num, i*n+j) = CV_MAT_ELEM(*face[num]->data, double, i, j);
            }
    }

    covar_mat = cvCreateMat(m*n, m*n, CV_64FC1);
    mean_mat = cvCreateMat(1, m*n, CV_64FC1);

//得到协方差矩阵和均值矩阵
    cvCalcCovarMatrix((const CvArr**)image_points, k, covar_mat, mean_mat, CV_COVAR_NORMAL|CV_COVAR_ROWS);
    printf("end calcCov\n");

//将得到的均值矩阵转为均值人脸
    CvMat* Media = cvCreateMat(m, n, CV_64FC1);
    for(int i = 0; i < m; i ++)
        for(int j = 0; j < n; j++){
            CV_MAT_ELEM(*Media, double, i, j) = CV_MAT_ELEM(*mean_mat, double,0, i*n+j);
        }
//展示平均人脸
    cvNamedWindow("meanFace");

    IplImage* mm = cvCreateImage(cvSize(Media->cols, Media->rows), 8, 1);
    cvConvert(Media, mm);
    cvSaveImage("/Users/jinfee/Documents/Github/game-technical-section/Eigenface/Src/meanface.pgm",mm);

//    cvShowImage("meanFace", mm);
//
//    cvWaitKey(0);
//    cvDestroyWindow("meanFace");
    printf("end getAve\n");
}

//用cvEigenVV()计算得到特征向量
void FaceLib::getEigen() {

    eigen_value = cvCreateMat(row * col, 1, CV_64FC1);
    eigen_vector = cvCreateMat(row * col, row * col, CV_64FC1);
    printf("ready to compute eigen\n");
    cvEigenVV(covar_mat, eigen_vector, eigen_value);
    printf("finish computing eigen\n");

}

//保存计算得到的特征人脸
void FaceLib::saveEigen(string in, int k) {
    printf("start saveEigen\n");
    eigen_number = k;
    A = cvCreateMat(row * col, k, CV_64FC1);
//    将k个特征向量还原成图像排列
    for(int t = 0; t < k; t ++) {
        CvMat *eigen_face = cvCreateMat(row, col, CV_64FC1);
        for(int i = 0; i < row; i ++)
            for(int j = 0; j < col; j ++) {
                CV_MAT_ELEM(*eigen_face, double,i,j) = CV_MAT_ELEM(*eigen_vector, double, t, i*col+j);
            }


        for(int i = 0; i < row; i++)
            for(int j = 0; j < col; j++) {
                CV_MAT_ELEM(*A, double, i * col + j, t) = CV_MAT_ELEM(*eigen_face, double, i, j);
            }

        //        对特征人脸矩阵均衡化为0-255
        cvNormalize(eigen_face, eigen_face, 255.0, 0.0, CV_MINMAX);

//        将特征人脸转化为图像格式后储存
        IplImage* eigen_img = cvCreateImage(cvSize(col, row), 8, 1);
        cvConvert(eigen_face, eigen_img);
        char* img_src = new char[100];
        sprintf(img_src, "%s/eigen%d.pgm", in.data(), t);
        cvSaveImage(img_src, eigen_img);
    }

//    将特征向量保存为xml文件
    CvMat* At = cvCreateMat(k, row * col, CV_64FC1);
    cvTranspose(A, At);
    char* src = new char[100];
    sprintf(src, "%s/A.xml", in.data());
    cvSave(src, A);
    cout<<"finish saving eigen"<<endl;


    CvMat* X = cvCreateMat(row*col, number, CV_64FC1);
    cvTranspose(image_points[0], X);

    eigen_image = cvCreateMat(k, number, CV_64FC1);
    cvMatMul(At, X, eigen_image);
    sprintf(src, "%s/EigenImage.xml", in.data());
    cvSave(src, eigen_image);

//    将训练之后得到的各个权重向量进行保存
    for(int n = 0; n < number; n ++) {
        CvMat* yi = cvCreateMat(k, 1, CV_64FC1);
        for(int i = 0; i < k; i ++)
            CV_MAT_ELEM(*yi, double, i, 0) = CV_MAT_ELEM(*eigen_image, double, i, n);
        char* img_src = new char[100];
        sprintf(img_src, "%s/face/%s.xml", in.data(), face[n]->name);
        cvSave(img_src, yi);
        face[n]->eigen = yi;
    }
    cout<<"finish eigen face"<<endl;

}

