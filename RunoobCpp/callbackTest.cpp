#include <stdio.h>

void funcAux(int& var) {
    var += 5;
}

const int MAX = 6;

void oprLstFuncPnt(int (&aLst)[MAX], int lmt, void (*func)(int &)) {
    for(int i=0; i<lmt; i++) {
        int &tmp = aLst[i];
        func(tmp);
    }
}

void oprLstFunc(int (&aLst)[MAX], int lmt, void func(int &)) {
    for(int i=0; i<lmt; i++) {
        int &tmp = aLst[i];
        func(tmp);
    }
}

void prtLst(int (&l)[MAX]) {
    for(int i=0; i<MAX; i++) {
        printf("第%d个元素是%d\n", i+1, l[i]);
    }
}

int main() {
    int lst[MAX] = {1,1,4,5,1,4};
    int (&reLst)[MAX] = lst;
    void (*f)(int &) = &funcAux;

    oprLstFuncPnt(reLst, MAX, f);
    prtLst(reLst);

    printf("----------------\n");

    oprLstFunc(reLst, MAX, funcAux);
    prtLst(reLst);
    return 0;
}