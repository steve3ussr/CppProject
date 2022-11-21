#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "oop_mem_func_define_outOfClass.h"


void Student::print_info(void)
{
    int assess_math = assess(score_math);
    int assess_eng = assess(score_eng);

    std::cout << "Student's: " << name;
    printf(",  math res: %d, eng res: %d\n", assess_math, assess_eng);
};


Student::Student(std::string str, int math, int eng)
{
    score_eng = eng;
    score_math = math;
    name = str;
}

Student::Student()
{
    score_eng = 0;
    score_math = 0;
    name = "NULL";
}


int Student::assess(int a_score)
{
    if (a_score >= 90){return 5;}
    else if (a_score >= 80){return 4;}
    else if (a_score >= 70){return 3;}
    else if (a_score >= 60){return 2;}
    else {return 0;}
}


int main()
{
    Student colin("Colin McRae", 97, 66);
    Student mary;
    colin = Student("CoLin McRae", 66, 97);
    colin.print_info();
    mary.print_info();
    return 0;
}