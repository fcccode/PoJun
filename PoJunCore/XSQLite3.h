#pragma once
#include "XPJCoreHead.h"
#include <sqlite3.h>

class XSQLite3
{ 
private:
    XSQLite3();
    ~XSQLite3();

public:
    static XSQLite3* pins();
    static XSQLite3* m_This;

    bool init_sql(XString& path);

private:
    bool co_db();
    
    bool init_db();

    bool open_db();
     

private:
    XString sql_path;

    sqlite3 *db;
};

