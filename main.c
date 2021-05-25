//
// Created by liuchang01_dxm on 2021/5/25.
//

#include "dict.h"

int main(int argc, char **argv){
    if (argc < 2){
        fprintf(stderr, "input params is too few! \n");
        return 1;
    }
    Process(argc,argv);
    return 0;
}