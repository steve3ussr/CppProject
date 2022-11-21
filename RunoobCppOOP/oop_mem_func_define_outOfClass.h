#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

class Student 
{
    public:
        
        void print_info(void);
        Student(std::string, int, int);
        Student();
        ~Student(){std::cout << "Student(" << name << ") died.\n";};

    private:
        std::string name;
        int score_math;
        int score_eng;
        int assess(int);
        
};
