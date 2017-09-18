/*************************************************************************
	> File Name: box_class.h
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Thu 14 Sep 2017 08:48:23 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

void f(int var);

template<typename T>
inline void callWithMax(const T& a, const T& b);

class Box
{
    public:
    Box();//default constructor
    Box(const Box& rhs);//copy constructor
    Box& operator=(const Box& rhs);//copy assignment operator
    ~Box();
    double getVolume(void);
    void setLength(double len);
    void setBreadth(double bre);
    void setHeight(double hei);
    double getFudgeFactor(void);

    double length;
    double breadth;
    double height;

    private:
    static const double FudgeFactor;
    enum {NumTurns = 5};

    int scores[NumTurns];
};
