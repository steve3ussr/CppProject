#include <stdio.h>

int(* func())[9] {
    static int a[9] = {1, 5432, 654, 6, 4324, 32, 97, 654, 321};
    printf("local var a's ADDR: %p\n\n", &a);
    int (*p)[9] = &a;
    return p;
}

int main() {
    int (*p)[9] = func();
    printf("local var a's ADDR: %d\n\n", *p);
    for(int i=0; i<9; i++) {
        printf("%d @ ADDR: %p\n", (*p)[i], &(*p)[i]);
    }
    
    return 0;
}