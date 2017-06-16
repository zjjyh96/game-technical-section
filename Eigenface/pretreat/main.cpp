#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {

    char* in = new char[100];
    sprintf(in, "/Users/jinfee/Documents/Github/game-technical-section/Eigenface/Src/orl_faces");
    double fScale = 0.5;      //缩放倍数
    CvSize cvSize;              //目标图像尺寸
    IplImage* di;

    for (int i=1;i<=40;i++){
        char* src = new char[100];
        sprintf(src, "%s/s%d", in,i);

        for(int j=1;j<=5;j++){

            char* img_src = new char[100];
            sprintf(img_src,"%s/%d.pgm",src,j);

            printf("%s\n",img_src);
//            保存图片内容
            IplImage* d = cvLoadImage(img_src, CV_LOAD_IMAGE_GRAYSCALE);

            cvSize.width = 30;
            cvSize.height = 40;

            //创建图像并缩放
            di= cvCreateImage(cvSize, d->depth, d->nChannels);
            cvResize(d, di, CV_INTER_AREA);
            cvEqualizeHist(di,di);


//            cvNamedWindow("meanFace");
//            cvShowImage("meanFace", d);
//            cvWaitKey(0);
//            cvDestroyWindow("meanFace");

            char* nsrc = new char[100];
            sprintf(nsrc, "/Users/jinfee/Documents/Github/game-technical-section/Eigenface/Src/trainface/s%d_%d.pgm",i,j);
            cvSaveImage(nsrc,di);
            delete[] nsrc;

        }
        delete[] src;
    }

    char* src2 = new char[100];
    sprintf(src2, "/Users/jinfee/Documents/Github/game-technical-section/Eigenface/Src/Jinfee.jpg");
    IplImage* d = cvLoadImage(src2, CV_LOAD_IMAGE_GRAYSCALE);

    di= cvCreateImage(cvSize, 8,1);
    cvResize(d, di, CV_INTER_AREA);
    cvEqualizeHist(di,di);
    char* nsrc = new char[100];
    sprintf(nsrc, "/Users/jinfee/Documents/Github/game-technical-section/Eigenface/Src/trainface/Jinfee.pgm");
    cvSaveImage(nsrc,di);



    return 0;
}