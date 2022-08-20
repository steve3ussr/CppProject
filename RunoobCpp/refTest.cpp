#include <stdio.h>

int main() {
    int a = 114514;
    int& b = a;
    int c = b;
    c -= 100;
    b -= 131345;
    printf("a=%d, b=%d, c=%d\n", a, b, c);
    return 0;
}