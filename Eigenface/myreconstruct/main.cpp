#include "FaceLib.h"

int main(int argc, char* argv[]) {


//    if(argc != 3){
//        printf("Parameter Invalid\n");
//        return -1;
//    }

    FaceLib library;

    char* folder = new char[100]; sprintf(folder, "/Users/jinfee/Documents/Github/game-technical-section/Eigenface/Src");
//    char* t_src = argv[1];
    char* m_src = new char[100]; sprintf(m_src, "%s/model", folder);
//    char* m_src = argv[2];
    char* t_src = new char[100]; sprintf(t_src, "%s/recface", folder);


    library.loadLibrary(m_src);
    printf("finish loadLibrary\n");

    library.loadRecFace(t_src);
    printf("finish loadRecFace\n");

    library.calcEigen();
    printf("finish calcEigen\n");

//    library.recFace(10, t_src);
//    library.recFace(25, t_src);
    library.recFace(100, t_src);


    printf("finish recFace\n");
}
