#include<iostream>
using namespace std;

class DateBase
{
	public:
		DateBase(char* dbPath);
		~DataBase();
		int OpenDateBase();
		int IsOpenedDataBase();
		int CloseDateBase();
		int CreateTable(char* tableName);
		int IsExitTable(Char* tableName);
		int InsertDataBase();
		int UpdateDataBase();
		int DeleteDataBase();
		int SearchDataBase();
	private:
		char dbpath[128];
        static sqlite3 *database;
};

