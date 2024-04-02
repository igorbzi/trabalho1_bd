#include <stdio.h>
#include "read_file.h"

int main(int argc, char *argv[]){

    if(argc>1){
        read_file(argv[1]);
        return 0;
    }
    printf("LOGICAL TABLE NAME MISSING\n");
    return 0;
}
