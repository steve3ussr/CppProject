#include <stdio.h>

void argRef(int &&x) {
    printf("%d\n", x+114514);
}

int main() {
    argRef(10);
}