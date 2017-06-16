#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <stdlib.h>

int n_boards = 0; //Will be set by input list
int board_w;
int board_h;
int board_n;//获取棋盘的大小
FILE *fptr;
CvSize board_sz;
char* viewImgPath;

int calibration() {

    char* filepath="/Users/jinfee/Documents/Github/game-technical-section/Calibration/chessboards.txt";
    fptr = fopen(filepath,"r");

    char names[2048];
//    根据目录统计目录下图像的数量
    while(fscanf(fptr,"%s ",names)==1){
        n_boards++;
    }
    printf("n_boards=%d\n",n_boards);
    rewind(fptr);

    cvNamedWindow( "Calibration" );
    //分配空间
    CvMat* image_points      = cvCreateMat(n_boards*board_n,2,CV_32FC1);
    CvMat* object_points     = cvCreateMat(n_boards*board_n,3,CV_32FC1);
    CvMat* point_counts      = cvCreateMat(n_boards,1,CV_32SC1);

///  CvMat * image_points	= cvCreateMat(1, n_boards*board_n, CV_32FC2);
///  CvMat * object_points = cvCreateMat(1, n_boards*board_n, CV_32FC3);
///  CvMat * point_counts  = cvCreateMat(1, n_boards, CV_32SC1);

    //初始化内参矩阵和畸变矩阵
    CvMat* intrinsic_matrix  = cvCreateMat(3,3,CV_32FC1);
    CvMat* distortion_coeffs = cvCreateMat(4,1,CV_32FC1);


    IplImage* image = 0;// = cvQueryFrame( capture );
    IplImage* gray_image = 0; //for subpixel
    CvPoint2D32f* corners = new CvPoint2D32f[ board_n ];
    int corner_count;
    int successes = 0;
    int step;
    //对每个图像进行循环
    for( int frame=0; frame<n_boards; frame++ ) {
        fscanf(fptr,"%s ",names);
        //读入图片，释放前一张图片的内存
        if(image){
            cvReleaseImage(&image);
            image = 0;
        }
        image = cvLoadImage( names);
        //用于亚像素精度计算的处理
        if(gray_image == 0  && image) //We'll need this for subpixel accurate stuff
            gray_image = cvCreateImage(cvGetSize(image),8,1);

        if(!image) printf("null image\n");

        //获取图像的角点
        int found = cvFindChessboardCorners(
                image,
                board_sz,
                corners,
                &corner_count,
                CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS
        );

        //获取亚像素精度的角点位置
        cvCvtColor(image, gray_image, CV_BGR2GRAY);
        cvFindCornerSubPix(gray_image, corners, corner_count,
                           cvSize(11,11),cvSize(-1,-1), cvTermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));

        //绘制棋盘格的角点
        cvDrawChessboardCorners(image, board_sz, corners, corner_count, found);
        cvShowImage( "Calibration", image );

        // 如果得到的角点数量是对的，加到我们的数据中
        //
        if( corner_count == board_n ) {
            step = successes*board_n;
            printf("Found = %d for %s\n",found,names);
            for( int i=step, j=0; j<board_n; ++i,++j ) {
                CV_MAT_ELEM(*image_points, float,i,0) = corners[j].x;
                CV_MAT_ELEM(*image_points, float,i,1) = corners[j].y;
                CV_MAT_ELEM(*object_points,float,i,0) = j/board_w;
                CV_MAT_ELEM(*object_points,float,i,1) = j%board_w;
                CV_MAT_ELEM(*object_points,float,i,2) = 0.0f;

            }
            CV_MAT_ELEM(*point_counts, int,successes,0) = board_n;
            successes++;
        }
        else printf("Couldn't aquire checkerboard on %s, only found %d of %d corners\n",
                    names,corner_count,board_n);

    }
    printf("successes = %d, n_boards=%d\n",successes,n_boards);
    //ALLOCATE MATRICES ACCORDING TO HOW MANY IMAGES WE FOUND CHESSBOARDS ON

    CvMat* object_points2     = cvCreateMat(successes*board_n,3,CV_32FC1);
    CvMat* image_points2      = cvCreateMat(successes*board_n,2,CV_32FC1);
    CvMat* point_counts2      = cvCreateMat(successes,1,CV_32SC1);

    //TRANSFER THE POINTS INTO THE CORRECT SIZE MATRICES
    for(int i = 0; i<successes*board_n; ++i){

        CV_MAT_ELEM(*image_points2, float,i,0) = CV_MAT_ELEM(*image_points, float,i,0);
        CV_MAT_ELEM(*image_points2, float,i,1) = CV_MAT_ELEM(*image_points, float,i,1);
        CV_MAT_ELEM(*object_points2,float,i,0) = CV_MAT_ELEM(*object_points,float,i,0) ;
        CV_MAT_ELEM(*object_points2,float,i,1) = CV_MAT_ELEM(*object_points,float,i,1) ;
        CV_MAT_ELEM(*object_points2,float,i,2) = CV_MAT_ELEM(*object_points,float,i,2) ;

    }
    for(int i=0; i<successes; ++i){
///		CV_MAT_ELEM(*point_counts2,int,0, i) = CV_MAT_ELEM(*point_counts, int,0,i);
        CV_MAT_ELEM(*point_counts2,int,i, 0) = CV_MAT_ELEM(*point_counts, int,i,0);
    }
    cvReleaseMat(&object_points);
    cvReleaseMat(&image_points);
    cvReleaseMat(&point_counts);

    // At this point we have all of the chessboard corners we need.
    //

    // Initialize the intrinsic matrix such that the two focal
    // lengths have a ratio of 1.0
    //
    CV_MAT_ELEM( *intrinsic_matrix, float, 0, 0 ) = 1.0f;
    CV_MAT_ELEM( *intrinsic_matrix, float, 1, 1 ) = 1.0f;
    printf("cvCalibrateCamera2\n");
    cvCalibrateCamera2(
            object_points2,
            image_points2,
            point_counts2,
            cvGetSize( image ),
            intrinsic_matrix,
            distortion_coeffs,
            NULL,
            NULL,
            0//CV_CALIB_FIX_ASPECT_RATIO
    );
    // 保存内参和畸变参数
    cvSave("Intrinsics.xml",intrinsic_matrix);
    cvSave("Distortion.xml",distortion_coeffs);

    return 0;
}

int birdeye() {


    CvMat *intrinsic = (CvMat*)cvLoad("Intrinsics.xml");
    CvMat *distortion = (CvMat*)cvLoad("Distortion.xml");

    IplImage *image = 0, *gray_image = 0;
    image = cvLoadImage(viewImgPath);
    //用于亚像素精度计算
    gray_image = cvCreateImage(cvGetSize(image),8,1);
    cvCvtColor(image, gray_image, CV_BGR2GRAY);

    //还原图像畸变
    IplImage* mapx = cvCreateImage( cvGetSize(image), IPL_DEPTH_32F, 1 );
    IplImage* mapy = cvCreateImage( cvGetSize(image), IPL_DEPTH_32F, 1 );
    cvInitUndistortMap(
            intrinsic,
            distortion,
            mapx,
            mapy
    );
    IplImage *t = cvCloneImage(image);
    cvRemap( t, image, mapx, mapy );

    //GET THE CHECKERBOARD ON THE PLANE
    cvNamedWindow("Checkers");
    CvPoint2D32f* corners = new CvPoint2D32f[ board_n ];
    int corner_count = 0;
    int found = cvFindChessboardCorners(
            image,
            board_sz,
            corners,
            &corner_count,
            CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS
    );
    if(!found){
        printf("Couldn't aquire checkerboard, only found %d of %d corners\n",
               corner_count,board_n);
        return -1;
    }
    //Get Subpixel accuracy on those corners
    cvFindCornerSubPix(gray_image, corners, corner_count,
                       cvSize(11,11),cvSize(-1,-1),
                       cvTermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));

    //GET THE IMAGE AND OBJECT POINTS:
    //Object points are at (r,c): (0,0), (board_w-1,0), (0,board_h-1), (board_w-1,board_h-1)
    //That means corners are at: corners[r*board_w + c]
    CvPoint2D32f objPts[4], imgPts[4];
    objPts[0].x = 0;         objPts[0].y = 0;
    objPts[1].x = board_w-1; objPts[1].y = 0;
    objPts[2].x = 0;         objPts[2].y = board_h-1;
    objPts[3].x = board_w-1; objPts[3].y = board_h-1;
    imgPts[0] = corners[0];
    imgPts[1] = corners[board_w-1];
    imgPts[2] = corners[(board_h-1)*board_w];
    imgPts[3] = corners[(board_h-1)*board_w + board_w-1];

    //DRAW THE POINTS in order: B,G,R,YELLOW
    cvCircle(image,cvPointFrom32f(imgPts[0]),9,CV_RGB(0,0,255),3);
    cvCircle(image,cvPointFrom32f(imgPts[1]),9,CV_RGB(0,255,0),3);
    cvCircle(image,cvPointFrom32f(imgPts[2]),9,CV_RGB(255,0,0),3);
    cvCircle(image,cvPointFrom32f(imgPts[3]),9,CV_RGB(255,255,0),3);

    //DRAW THE FOUND CHECKERBOARD
    cvDrawChessboardCorners(image, board_sz, corners, corner_count, found);
    cvShowImage( "Checkers", image );
    cvSaveImage("Checkers.jpg",image);

    //FIND THE HOMOGRAPHY
    CvMat *H = cvCreateMat( 3, 3, CV_32F);
    CvMat *H_invt = cvCreateMat(3,3,CV_32F);
    cvGetPerspectiveTransform(objPts,imgPts,H);

    //LET THE USER ADJUST THE Z HEIGHT OF THE VIEW
    float Z = 25;
    int key = 0;
    IplImage *birds_image = cvCloneImage(image);
    cvNamedWindow("Birds_Eye");
    while(key != 27) {//escape key stops
        CV_MAT_ELEM(*H,float,2,2) = Z;
//	   cvInvert(H,H_invt); //If you want to invert the homography directly
//	   cvWarpPerspective(image,birds_image,H_invt,CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS );
        //USE HOMOGRAPHY TO REMAP THE VIEW
        cvWarpPerspective(image,birds_image,H,
                          CV_INTER_LINEAR+CV_WARP_INVERSE_MAP+CV_WARP_FILL_OUTLIERS );
        cvShowImage("Birds_Eye", birds_image);
        key = cvWaitKey();
        if(key == 'u') Z += 0.5;
        if(key == 'd') Z -= 0.5;
    }

    //SHOW ROTATION AND TRANSLATION VECTORS
    CvMat* image_points  = cvCreateMat(4,1,CV_32FC2);
    CvMat* object_points = cvCreateMat(4,1,CV_32FC3);
    for(int i=0;i<4;++i){
        CV_MAT_ELEM(*image_points,CvPoint2D32f,i,0) = imgPts[i];
        CV_MAT_ELEM(*object_points,CvPoint3D32f,i,0) = cvPoint3D32f(objPts[i].x,objPts[i].y,0);
    }

    CvMat *RotRodrigues   = cvCreateMat(3,1,CV_32F);
    CvMat *Rot   = cvCreateMat(3,3,CV_32F);
    CvMat *Trans = cvCreateMat(3,1,CV_32F);
    cvFindExtrinsicCameraParams2(object_points,image_points,
                                 intrinsic,distortion,
                                 RotRodrigues,Trans);
    cvRodrigues2(RotRodrigues,Rot);

    //SAVE AND EXIT
    cvSaveImage("birdeye-view.jpg",birds_image);
    cvSave("Rot.xml",Rot);
    cvSave("Trans.xml",Trans);
    cvSave("H.xml",H);
    cvInvert(H,H_invt);
    cvSave("H_invt.xml",H_invt); //Bottom row of H invert is horizon line
    return 0;
}


int main() {
    board_w = 9;//输入棋盘的宽度
    board_h = 6;//输入棋盘的高度
    viewImgPath="view.jpg";
    board_n  = board_w * board_h;//获取棋盘的大小
    board_sz = cvSize( board_w, board_h );

    calibration();
    birdeye();

    return 0;
}
