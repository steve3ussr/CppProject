#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

class Student 
{
    public:
        
        void print_info(void)
        {
            int assess_math = assess(score_math);
            int assess_eng = assess(score_eng);

            std::cout << "Student's: " << name;
            printf(",  math res: %d, eng res: %d\n", assess_math, assess_eng);
        };

        Student(std::string str, int math, int eng)
        {
            score_eng = eng;
            score_math = math;
            name = str;
        };

    private:
        std::string name;
        int score_math;
        int score_eng;
        int assess(int a_score)
        {
            if (a_score >= 90){return 5;}
            else if (a_score >= 80){return 4;}
            else if (a_score >= 70){return 3;}
            else if (a_score >= 60){return 2;}
            else {return 0;}
        }
};

int main()
{
    Student colin = Student("Colin McRae", 97, 86);
    Student mary = Student("Fucking Mary", 76, 62);
    colin.print_info();
    mary.print_info();
    return 0;
}