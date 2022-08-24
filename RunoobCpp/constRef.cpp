#include <stdio.h>

int & rightRef(void) {
    int && tmp = 114514;
    return tmp;
}

const int & constRef(void) {
    const int & tmp2 = 11451;
    return tmp2;
}

void argRef(int &&x) {
    printf("%d\n", x+1);
}


int main() {
    int &pntRightRef = rightRef();
    pntRightRef += 1;
    printf("res = %d\n", pntRightRef);

    const int &pntConstRef = constRef();
    //pntConstRef += 1; //cannot be modified
    printf("res = %d\n", pntConstRef);

    argRef(10);
}


