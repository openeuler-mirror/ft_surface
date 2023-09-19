#include "native_window_wrapper.h"
#include <stdio.h>

int main(int argc, const char** argv) {
    if(LoadFtSurface() == SUCCESS) {
        if (FAILED == OpenLibraryTest()) {
            printf("open so failed\n");
            return -1;
        }
    }
    return 0;
}