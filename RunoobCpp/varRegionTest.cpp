#include <stdio.h>

int a = 10;

void aux() {
    a = 1;
    printf("a = %d\n", a);
}

int main() {
    aux();
    printf("a main = %d\n", a);
}
