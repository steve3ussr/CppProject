#include <stdio.h>


int main() {
    int lst[3][2] = {0, 111, 222, 333, 444, 555};
    //int *p = lst;
    printf("%d\n", *(lst+1)[1]);
    return 0;
}