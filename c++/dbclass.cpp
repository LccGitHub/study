#include"dbclass.h"

sqlite3* DateBase::m_datebase = NULL;

DateBase::DateBase(const char* dbPath)
    : m_dbpath()
    , m_tableName()
    , m_dbConfig()
{
    if (dbPath ==  NULL) {
        printf("parameter is error!!!");
    }
    else {
        strncpy(m_dbpath, dbPath, sizeof(m_dbpath));
    }
}
DateBase::~DateBase()
{
    m_datebase = NULL;
}
int DateBase::OpenDateBase()
{
    int rc = 0;
    rc = sqlite3_open(m_dbpath, &m_datebase);
    if (rc == SQLITE_OK) {

    }
    else {
        printf("open database failed!!!\n");
    }
    return rc;
}

int DateBase::IsOpenedDateBase()
{
}

int DateBase::CloseDateBase()
{
    int rc = 0;
    rc = sqlite3_close(m_datebase);
    if (rc == SQLITE_OK) {

    }
    else {
        printf("open database failed!!!\n");
    }
    return rc;
}

int DateBase::CreateTable(const char* tableName)
{
    int rc = 0;
    char *sql = NULL;
    if (tableName == NULL) {
        printf("table name is NULL!!!");
    }
    else {
        sql = sqlite3_mprintf("CREATE TABLE IF NOT EXISTS '%q' (KEY TEXT PRIMARY KEY,VALUE TEXT)", tableName);
        rc = ExecNoResDateBase(sql);
        if (SQLITE_OK == rc){
            strncpy(m_tableName, tableName, sizeof(m_tableName));
        }
        sqlite3_free(sql);
    }
    return rc;
}

int DateBase::IsExitTable(char* tableName)
{
}

int DateBase::InsertDateBase(DBConfig dbConfig)
{
    int rc = 0;
    char *sql = NULL;
    sql = sqlite3_mprintf("INSERT INTO '%q' (KEY,VALUE) VALUES ('%q', '%q')", m_tableName, dbConfig.key, dbConfig.value);
    rc = ExecNoResDateBase(sql);
    sqlite3_free(sql);
    return rc;
}

int DateBase::UpdateDateBase(DBConfig dbConfig)
{
    int rc = 0;
    char *sql = NULL;
    sql = sqlite3_mprintf("UPDATE '%q' SET VALUE =  '%q' WHERE KEY =  '%q'", m_tableName, dbConfig.value, dbConfig.key);
    rc = ExecNoResDateBase(sql);
    sqlite3_free(sql);
    return rc;
}

int DateBase::DeleteDateBase(const char* key)
{
    int rc = 0;
    char *sql = NULL;
    sql = sqlite3_mprintf("DELETE FROM '%q' WHERE KEY =  '%q'", m_tableName, key);
    rc = ExecNoResDateBase(sql);
    sqlite3_free(sql);
    return rc;
}

int DateBase::SearchDateBase(const char* key, DBConfig* dbConfig)
{
    int rc = 0;
    char * sql = NULL;
    char **dbResult;
    int nRow = 0;
    int nColumn = 0;
    char *error_message = NULL;
    sql = sqlite3_mprintf("SELECT * FROM '%q' WHERE KEY = '%q'", m_tableName, key);
    rc = sqlite3_get_table(m_datebase, sql, &dbResult, &nRow, &nColumn, &error_message);
    if ((error_message != NULL) || (rc != SQLITE_OK )) {
        printf("Error executing the get table, error: [%s] ret: [%d].\n",error_message, rc);
    }
    else {
        if (nRow < 1) {
            printf("no qualified result.\n");
        }
        else if (nRow > 1) {
            printf("record error.\n");
        }
        else {
            strcpy(dbConfig->value, dbResult[nColumn + 1]);
        }
        sqlite3_free_table(dbResult);
    }
    sqlite3_free(error_message);
    sqlite3_free(sql);
}

int DateBase::ExecNoResDateBase(const char *sql)
{
    int rc = 0;
    char *error_message = NULL;
    if (sql == NULL) {
        printf("sql  is NULL!!!");
    }
    else {
        printf("Executing query [%s].\n", sql);
        rc = sqlite3_exec(m_datebase, sql, NULL, 0, &error_message);
        if ((error_message != NULL) || (rc != SQLITE_OK )) {
            printf("Error executing the query, error: [%s] ret: [%d].\n",error_message, rc);
        }
        else {

        }
        sqlite3_free(error_message);
    }
    return rc;
}

int main()
{
   DateBase db("test.db");
   DateBase db1("test1.db");
   DBConfig dbcfg;
   strcpy(dbcfg.key, "lily");
   strcpy(dbcfg.value, "woman");
   int rc = 0;
   //rc = db.OpenDateBase();
   if (SQLITE_OK != db.OpenDateBase()) {
       printf("open datebase failed \n");
   }
   else if (SQLITE_OK != db.CreateTable("table1")){
       printf("create table failed \n");
   }
   else {
       db.InsertDateBase(dbcfg);
       strcpy(dbcfg.key, "lilei");
       strcpy(dbcfg.value, "man");
       db.InsertDateBase(dbcfg);

       strcpy(dbcfg.key, "john");
       strcpy(dbcfg.value, "man");
       db.InsertDateBase(dbcfg);

       strcpy(dbcfg.key, "john");
       strcpy(dbcfg.value, "xxxman");
       db.UpdateDateBase(dbcfg);
       db.SearchDateBase("lilei", &dbcfg);
       printf("search result lilei is [%s] \n", dbcfg.value);
       db.DeleteDateBase("john");
       db.CloseDateBase();
   }


   if (SQLITE_OK != db1.OpenDateBase()) {
       printf("open datebase failed \n");
   }
   else if (SQLITE_OK != db1.CreateTable("table1")){
       printf("create table failed \n");
   }
   else {
       db1.InsertDateBase(dbcfg);
       strcpy(dbcfg.key, "lilei");
       strcpy(dbcfg.value, "1man");
       db1.InsertDateBase(dbcfg);

       strcpy(dbcfg.key, "john");
       strcpy(dbcfg.value, "2man");
       db1.InsertDateBase(dbcfg);

       strcpy(dbcfg.key, "john");
       strcpy(dbcfg.value, "111man");
       db1.UpdateDateBase(dbcfg);
       db1.SearchDateBase("lilei", &dbcfg);
       printf("search result lilei is [%s] \n", dbcfg.value);
       //db1.DeleteDateBase("john");
       db1.CloseDateBase();
   }

}

