#include <bits/stdc++.h>

void add1(int & ele) {
    ele += 1;
}

const int MAX = 6;

int main() {
    int vec[MAX] = {1, 1, 4, 5, 1, 4};
    printf("%d\n", vec[0]);
    int (&r)[MAX] = vec;
    
    for(int i=0;i<6;i++)
    {
        add1(r[i]);
        printf("%d\n", vec[i]);
    }
    
    return 0;
}