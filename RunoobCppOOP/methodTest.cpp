#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>

class People
{
    public:
        void virtual print_info() = 0;
};

class Student: public People
{
    public:
        int age;
        std::string name;
        float score_math;
        float score_eng;
        float score_chs;
        Student(std::string &&str, int a){name = str; age = a;}
        void print_stm(void){print_info();}

    private:
        void print_info(void);
};

void Student::print_info(void) 
{
    std::cout << name;
    printf(" 今年 %d 岁\n", age);
}

int main() {
    std::vector<Student *> lst;

    Student McRae = Student("McRae", 15);
    lst.push_back(&McRae);

    Student Amily = Student("Amily", 14);
    lst.push_back(&Amily);

    Student Ujung = Student("Ujung", 16);
    lst.push_back(&Ujung);

    for(int i=0; i<lst.size(); i++) {
        lst[i]->print_stm();
    }

    //McRae.print_stm();
    return 0;
};