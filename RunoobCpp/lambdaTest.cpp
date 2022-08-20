#include <iostream>
#include <stdio.h>
#define mian main

int mian() {
    int c = 1819;
    auto normL = [&](int a, int b){printf("lambda a=%d, b=%d, extern=%d\n", a, b, c);};
    
    normL(114, 514);

    return 0;
}