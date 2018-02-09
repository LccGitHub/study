/*************************************************************************
	> File Name: effective.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Fri 09 Feb 2018 05:32:31 PM CST
 ************************************************************************/

#include "effective.h"

bool validateStudent(const Student& s);
/*bool validateStudent(Student s);*/

Person::Person()
{
    printf("this is construct funciton [Person] \n");
}

Person::~Person()
{
    printf("this is deconstruct funciton [~Person] \n");
}

Student::Student()
{
    printf("this is construct funciton [Student] \n");
}

Student::~Student()
{
    printf("this is deconstruct funciton [~Student] \n");
}

bool validateStudent(const Student& s)
/*Effective rule20: Prefer pass-by-reference-to-const to pass-by-vaule */
/*bool validateStudent(Student s)  */
{
    printf("this is deconstruct funciton [validateStudent] \n");
    return false;
}

int main()
{
    Student plato;
    bool platoIsOk = validateStudent(plato);
    printf("platoIsOk = %d \n", platoIsOk);
    return 0;
}


