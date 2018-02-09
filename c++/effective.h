/*************************************************************************
	> File Name: effective.h
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Fri 09 Feb 2018 05:31:50 PM CST
 ************************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<stdbool.h>

class Person
{
public:
    Person();
    virtual ~Person();

private:
    std::string name;
    std::string address;
};

class Student: public Person
{
public:
    Student();
    ~Student();


private:
    std::string schoolName;
    std::string schoolAddress;

};

