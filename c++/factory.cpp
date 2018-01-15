/*************************************************************************
	> File Name: factory.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Mon 15 Jan 2018 03:03:47 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
/***********************************Factory mode*******************************/

/*-------------------------------this is common product class-----------------*/
class Product
{
	public:
		virtual void show() = 0;
};

class ProductA:public Product
{
	public:
		void show()
		{
			cout<<"this is product A"<<endl;
		}

};
class ProductA1:public Product
{
	public:
		void show()
		{
			cout<<"this is product A1"<<endl;
		}

};
class ProductB:public Product
{
	public:
		void show()
		{
			cout<<"this is product B"<<endl;
		}
};
class ProductB1:public Product
{
	public:
		void show()
		{
			cout<<"this is product B1"<<endl;
		}
};
/*-------------------------------this is simple factory mode, but need to fix factory class when add new product-----------------*/
/*-------------------------------this is simple factory mode, but need to fix factory class when add new product-----------------*/

class Factory
{
	public:
		Product* Creat(int i)
		{
			switch(i)
			{
				case 1:
					return new ProductA();
					break;
				case 2:
					return new ProductB();
					break;
				default:
					break;
			}
		}
};
/*-------------------------------------------------------------------------------*/
/*-------------------------------this is factory method mode ----------------------------*/

class FactoryMethod
{
	public:
		virtual Product* Creat() = 0;
};

class FactoryMethodA:public FactoryMethod
{
	public:
		Product* Creat()
		{
			return new ProductA;
		}
};
class FactoryMethodB:public FactoryMethod
{
	public:
		Product* Creat()
		{
			return new ProductB;
		}
};
/*-------------------------------------------------------------------------------*/

class FactoryAbstract
{
	public:
		virtual Product* Creat1() = 0;
		virtual Product* Creat2() = 0;

};
class FactoryAbstractA
{
	public:
		virtual Product* Creat1()
		{
			return new ProductA();
		}
		virtual Product* Creat2()
		{
			return new ProductA1();
		}

};
class FactoryAbstractB
{
	public:
		virtual Product* Creat1()
		{
			return new ProductB();
		}
		virtual Product* Creat2()
		{
			return new ProductB1();
		}

};
	




int main()
{
	Factory* factory = new Factory();
	factory->Creat(1)->show();
	factory->Creat(2)->show();

	FactoryMethodA* factoryMethodA = new FactoryMethodA();
	FactoryMethodB* factoryMethodB = new FactoryMethodB();
	factoryMethodA->Creat()->show();
	factoryMethodB->Creat()->show();\

	FactoryAbstractA* factoryAbstractA = new FactoryAbstractA();
	factoryAbstractA->Creat1()->show();
	factoryAbstractA->Creat2()->show();

	FactoryAbstractB* factoryAbstractB = new FactoryAbstractB();
	factoryAbstractB->Creat1()->show();
	factoryAbstractB->Creat2()->show();
	return 0;
}
