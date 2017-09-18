/*************************************************************************
> File Name: box_class.cpp
	> Created Time: Tue 12 Sep 2017 05:04:53 PM CST
	类的对象的公共数据成员可以使用直接成员访问运算符 (.) 来访问
	私有的成员和受保护的成员不能使用直接成员访问运算符 (.) 来直接访问
	类的成员函数是指那些把定义和原型写在类定义内部的函数，就像类定义中的其他变量一样。类成员函数是类的一个成员，它可以操作类的任意对象，可以访问对象中的所有成员。
	公有成员在程序中类的外部是可访问的。您可以不使用任何成员函数来设置和获取公有变量的值
	私有成员变量或函数在类的外部是不可访问的，甚至是不可查看的。只有类和友元函数可以访问私有成员。
	默认情况下，类的所有成员都是私有的。
	私有成员变量或函数在类的外部是不可访问的，甚至是不可查看的。只有类和友元函数可以访问私有成员。
	默认情况下，类的所有成员都是私有的。
 ************************************************************************/

#include<iostream>
#include "box_class.h"

using namespace std;


#define CALL_WITH_MAX(a, b) f((a) > (b) ? (a) : (b))

template<typename T>
inline void callWithMax(const T& a, const T& b)
{
    f(a > b ? a:b);
}

void f(int var)
{
    cout<<"input var="<<var<<endl;
}

const double 
    Box::FudgeFactor = 1.35;

Box::Box(void)
{
    cout<<"this is base class construct function"<<endl;
}

Box::Box(const Box& rhs)
{
    length = rhs.length;
    breadth = rhs.breadth;
    height = rhs.height;
    cout<<"this is copy construct function"<<endl;
}

Box& Box::operator=(const Box& rhs)
{
    if (this == &rhs)
        return *this;
    length = rhs.length;
    breadth = rhs.breadth;
    height = rhs.height;
    cout<<"this is copy assignment operator"<<endl;
    return *this;
}

Box::~Box(void)
{
    cout<<"this is base class Deconstruct function"<<endl;
}

double Box::getVolume(void)
{
    return length*height*breadth;
}

double Box::getFudgeFactor(void)
{
    return FudgeFactor;
}

void Box::setLength(double len)
{
    length = len;
}

void Box::setBreadth(double bre)
{
    breadth = bre;
}

void Box::setHeight(double hei)
{
    height = hei;
}

int main()
{
    Box Box1;
    Box Box2;
    Box Box3(Box1);    //call copy constructor
    Box1 = Box3;       //call copy assignment constructor
    Box Box4 = Box1;   //call copy constructor
    double volume = 0.0;

    /* this is Box1 config */
    Box1.setHeight(5.0);
    Box1.setLength(6.0);
    Box1.setBreadth(7.0);

    /* this is Box2 config */
    Box2.setHeight(10.0);
    Box2.setLength(12.0);
    Box2.setBreadth(13.0);

    volume = Box1.getVolume();
    cout << "Box1' volume:"<< volume <<endl;


    volume = Box2.getVolume();
    cout << "Box2' volume:"<< volume <<endl;

    volume = Box3.getVolume();
    cout << "Box3' volume:"<< volume <<endl;

    cout << "Box2' FudgeFactor:"<< Box2.getFudgeFactor() <<endl;

    int a1 = 5, b1= 0;
    //CALL_WITH_MAX(++a1, b1); // a1 was added twice
    //CALL_WITH_MAX(++a1, b1+10); // a1 was added firt

    callWithMax(++a1, b1);  // a1 was added firt
    callWithMax(++a1, b1 + 10);  // a1 was added firt
    cout << "a1="<< a1 <<endl;

    char greeting[] = "hello";
    char gr[] = "hello";
    const char* p = greeting;
    p = gr;
    //*p = "helel";  //this is error, becase *p is const , it was not be changed
    char* const p1=greeting;
    //p1=gr;//this is error, becase *p is const , it was not be changed
    //*p1 = gr;  //this is error, becase *p is const , it was not be changed


    return 0;

}



