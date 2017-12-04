#pragma once
#include "XPJCoreHead.h"
#include <sqlite3.h>

#define CC_TAB "CREATE TABLE cc_break_point(" \
        "module_name TEXT,"\
        "offset      INT," \
        "number      INT," \
        "opcode      INT," \
        "activation  BOOL);"

#define HARD_TAB "CREATE TABLE hard_break_point(" \
        "address    INT," \
        "dr_number  INT," \
        "length     INT," \
        "type       INT);"

#define MEMORY_TAB "CREATE TABLE memory_break_point(" \
        "number      INT," \
        "page_base   INT," \
        "address     INT," \
        "length      INT," \
        "type        INT," \
        "old_protect INT);"
 
#define COMMENT_TAB "CREATE TABLE comments(" \
        "address    INT," \
        "str        TEXT" \
        "type       BOOL);"

#define ALIAS_TAB "CREATE TABLE alias(" \
        "address    INT," \
        "str        TEXT);"

#define SELECT_CC_TAB "SELECT * from cc_break_point"

#define SELECT_HARD_TAB "SELECT * from hard_break_point"

#define SELECT_MEMORY_TAB "SELECT * from memory_break_point"

#define SELECT_COMMENTS_TAB "SELECT * from comments"

#define SELECT_ALIAS_TAB "SELECT * from alias"
 
class XSQLite3
{ 
private:
    XSQLite3();
    ~XSQLite3();

public:
    static XSQLite3* pins();
    static XSQLite3* m_This;

    bool init_sql(XString& path);

    bool insert_break_point(CC_BREAK_POINT& bp);

private:
    bool co_db();
    
    bool init_db();

    bool open_db();
    
    static int cc_callback(void *data, int argc, char **argv, char **azColName);

    static int hard_callback(void *data, int argc, char **argv, char **azColName);

    static int memory_callback(void *data, int argc, char **argv, char **azColName);

    static int comments_callback(void *data, int argc, char **argv, char **azColName);

    static int alias_callback(void *data, int argc, char **argv, char **azColName);

private:
    XString sql_path;

    sqlite3 *db;
};

