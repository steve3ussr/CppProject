# include <stdio.h>

void swapVal(int a, int b) {
    int tmp = a;
    a = b;
    b = a;
    return;
}

void swapPnt(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

void swapRef(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
    return;
}

int main() {
    int x = 114; 
    int y = 514;

    swapVal(x, y);
    printf("x = %d, y = %d\n", x, y);

    swapPnt(&x, &y);
    printf("x = %d, y = %d\n", x, y);

    swapRef(x, y);
    printf("x = %d, y = %d\n", x, y);
    return 0;
}


