/*************************************************************************
	> File Name: box_class.cpp
	> Created Time: Tue 12 Sep 2017 05:04:53 PM CST
	类的对象的公共数据成员可以使用直接成员访问运算符 (.) 来访问
	私有的成员和受保护的成员不能使用直接成员访问运算符 (.) 来直接访问
	类的成员函数是指那些把定义和原型写在类定义内部的函数，就像类定义中的其他变量一样。类成员函数是类的一个成员，它可以操作类的任意对象，可以访问对象中的所有成员。
 ************************************************************************/

#include<iostream>
using namespace std;

class Box
{
	public:
		double length;
		double breadth;
		double height;

		double getVolume(void);
/*		{
			return length*height*breadth;
		}
*/
		void setLength(double len);
		void setBreadth(double bre);
		void setHeight(double hei);
};

double Box::getVolume(void)
{
	return length*height*breadth;
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

	return 0;

}
