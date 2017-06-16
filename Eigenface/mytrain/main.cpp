#include "facelib.h"

int main(int argc, char* argv[]) {

//    if(argc!=4){
//        printf("Parameters Invalid");
//        return -1;
//    }



    int energy = 200;
    char* folder = new char[100];sprintf(folder, "/Users/jinfee/Documents/Github/game-technical-section/Eigenface/Src");

//    Att att;
    FaceLib library;

    char* l_src = new char[100]; sprintf(l_src, "%s/trainface", folder);
    char* m_src = new char[100]; sprintf(m_src, "%s/model", folder);

//    int energy = atoi(argv[1]);//能量百分比
//    char* l_src = argv[3];
//    char* m_src = argv[2];

    library.loadFace(l_src);//加载人脸库
    library.getAveFace();//得到平均人脸
    library.getEigen();//得到特征人脸
    library.saveEigen(m_src, energy);//保存特征人脸

    return 0;
}
