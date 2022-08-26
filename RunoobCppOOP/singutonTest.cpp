#include <stdio.h>
#include <iostream>
#define mian main

class Student
{
    public:
        int score;
    private:
        Student(int a) {
            this->score = a;
        }
};

int mian() {
    Student inst = Student(23);
};

// TODO: 1