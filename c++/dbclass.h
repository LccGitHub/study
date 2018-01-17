#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sqlite3.h>

struct DBConfig{
    char key[128];
    char value[128];
};

class DateBase
{
	public:
        DateBase(const char *dbPath);
        ~DateBase();
		int OpenDateBase();
        int IsOpenedDateBase();
		int CloseDateBase();
        int CreateTable(const char *tableName);
        int IsExitTable(char *tableName);
        int InsertDateBase(DBConfig dbConfig);
        int UpdateDateBase(DBConfig dbConfig);
        int DeleteDateBase(const char *key);
        int SearchDateBase(const char *key, DBConfig* dbConfig);
        int ExecNoResDateBase(const char *sql);
	private:
        char m_dbpath[128];
        char m_tableName[128];
        DBConfig m_dbConfig;
        static sqlite3 *m_datebase;

};

