/*************************************************************************
	> File Name: singleton.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Mon 15 Jan 2018 11:57:13 AM CST
 ************************************************************************/

#include<iostream>
#include<pthread.h>
using namespace std;
/************************************idler singleton**************************/
/*----------------------this is classics idler singleton, but is not safe thread----------------*/
class idler{
	protected:
		idler(){}
	private:
		static idler* p;
	public:
		static idler* instance();
};

idler* idler::p = NULL;

idler* idler::instance()
{
	if (p == NULL) {
		p = new idler();
	}
	return p;
}
/*---------------------------------------------------------------------------------------*/
/*----------------------this is  classics lock idler singleton, and  is  safe thread----------------*/
class idlerLock{
	protected:
		idlerLock()
		{
			pthread_mutex_init(&mutex, NULL);
		}
	private:
		static idlerLock* p;
	public:
		static pthread_mutex_t mutex;
		static idlerLock* instance();
};

idlerLock* idlerLock::p = NULL;
pthread_mutex_t idlerLock::mutex;

idlerLock* idlerLock::instance()
{
	if (p == NULL) {
		pthread_mutex_lock(&mutex);
		if (p == NULL) {
			p = new idlerLock();
		}
		pthread_mutex_unlock(&mutex);
	}
	return p;
}
/*---------------------------------------------------------------------------------------*/
/*----------------------this is  internal static variable idler singleton, and  is  safe thread----------------*/
class idlerStaticVar{
	protected:
		idlerStaticVar()
		{
			pthread_mutex_init(&mutex, NULL);
		}
	private:

	public:
		static pthread_mutex_t mutex;
		static idlerStaticVar* instance();
};

pthread_mutex_t idlerStaticVar::mutex;

idlerStaticVar* idlerStaticVar::instance()
{
	pthread_mutex_lock(&mutex);
	static idlerStaticVar p;
	pthread_mutex_unlock(&mutex);
	return &p;
}
/*---------------------------------------------------------------------------------------*/
class Eager{
	protected:
		Eager(){}
	private:
		static Eager* p;
	public:
		static Eager* instance();
};
Eager* Eager::p = new Eager();
Eager* Eager::instance()
{
	return p;
}

int main()
{
	idler* pIdler = idler::instance();
	idlerLock* pIdlerLock = idlerLock::instance();
	idlerStaticVar* pIdlerStaticVar = idlerStaticVar::instance();
	Eager* pEager = Eager::instance();
	cout<<"Idler instance="<<pIdler<<endl;
	cout<<"Idler Lock instance="<<pIdlerLock<<endl;
	cout<<"Idler static variable instance="<<pIdlerStaticVar<<endl;
	cout<<"Eager instance="<<pEager<<endl;
	return 0;
}
