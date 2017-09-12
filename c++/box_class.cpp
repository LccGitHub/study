/*************************************************************************
	> File Name: box_class.cpp
	> Created Time: Tue 12 Sep 2017 05:04:53 PM CST
	类的对象的公共数据成员可以使用直接成员访问运算符 (.) 来访问
	私有的成员和受保护的成员不能使用直接成员访问运算符 (.) 来直接访问
 ************************************************************************/

#include<iostream>
using namespace std;

class Box
{
	public:
		double length;
		double breadth;
		double height;
};

int main()
{
	Box Box1;
	Box Box2;
	double volume = 0.0;

	/* this is Box1 config */
	Box1.height = 5.0;
	Box1.length = 6.0;
	Box1.breadth = 7.0;

	/* this is Box2 config */
	Box2.height = 10.0;
	Box2.length = 12.0;
	Box2.breadth = 13.0;

	volume = Box1.height*Box1.length*Box1.breadth;
	cout << "Box1' volume:"<< volume <<endl;


	volume = Box2.height*Box2.length*Box2.breadth;
	cout << "Box2' volume:"<< volume <<endl;

	return 0;

}
