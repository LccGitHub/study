#include <sqlite3.h>
#include"dbclass.h"

static sqlite3 DateBase::*database = NULL;

DateBase::DateBase(char* dbPath)
    :dbpath()
{
    if (dbPath ==  NULL) {
        printf("parameter is error!!!");
    }
    else {
        strcpy(dbpath, dbPath);
    }
}
DateBase::~DataBase()
{
    *database = NULL;
}
int DateBase::OpenDateBase()
{
    int rc = 0;
    rc = sqlite3_open(dbpath, &database);
    if (rc == SQLITE_OK) {

    }
    else {
        printf("open database failed!!!\n");
    }
    return rc;
}

int DateBase::IsOpenedDataBase()
{
}

int DateBase::CloseDateBase()
{
    int rc = 0;
    rc = sqlite3_close(database);
    if (rc == SQLITE_OK) {

    }
    else {
        printf("open database failed!!!\n");
    }
    return rc;
}

int DateBase::CreateTable(char* tableName)
{
    int rc = 0;
    char *error_message = NULL;
    char *sql = NULL;
    if (tableName == NULL) {
        printf("table name is NULL!!!");
    }
    else {
        sql = sqlite3_snprintf("CREATE TABLE IF NOT EXISTS '%q' (KEY VALUE)", tableName);
        printf("Executing query [%s].", sql);
        rc = sqlite3_exec(database, sql, NULL, 0, &error_message);
        if ((error_message != NULL) || (rc != SQLITE_OK )) {
            printf("Error executing the query, error: [%s] ret: [%d].",error_message, rc);
        }
        else {

        }
    }
}

int DateBase::IsExitTable(Char* tableName)
{
}

int DateBase::InsertDataBase()
{
}

int DateBase::UpdateDataBase()
{
}

int DateBase::DeleteDataBase()
{
}

int DateBase::SearchDataBase()
{
}

