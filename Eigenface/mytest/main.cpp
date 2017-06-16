#include "FaceLib.h"

int main(int argc, char* argv[]) {


//    if(argc != 4){
//        printf("Parameter Invalid\n");
//        return -1;
//    }



    int facenum = 1;
    FaceLib library;

    char* folder = new char[100]; sprintf(folder, "/Users/jinfee/Documents/Github/game-technical-section/Eigenface/Src");
    char* m_src = new char[100]; sprintf(m_src, "%s/model", folder);
    char* t_src = new char[100]; sprintf(t_src, "%s/testface", folder);

//    char* m_src = argv[2];
//    char* t_src = argv[1];

    library.loadLibrary(m_src);
    library.loadRecFace(t_src);
    library.testFace(facenum);
}
