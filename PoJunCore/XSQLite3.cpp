#include "stdafx.h"
#include "XSQLite3.h"
#include <XFileMD5.h>
#include <XFile.h>
#include <XEnvironment.h>
#include <sqlite3.h> 


XSQLite3* XSQLite3::m_This = nullptr;
XSQLite3::XSQLite3()
{
    db = nullptr;
}


XSQLite3::~XSQLite3()
{
    if (db != nullptr)
    {
        sqlite3_close(db);
    }
}

XSQLite3* XSQLite3::pins()
{
    if (m_This == nullptr)
    {
        m_This = new XSQLite3;
    }

    return m_This;
}

bool XSQLite3::init_sql(XString& file_path)
{ 
    XString md5;
    if (!XFileMD5::get_file_md5(file_path, md5))
    {
        return false;
    }

    XString name = file_path.get_short_name_no_suffix();

    XString current_dir;
    XString current_exe;
    XEnvironment::get_exe_file_dir(current_dir, current_exe);
     
    XString db_path;
    db_path << current_dir << L"\\db\\";
    if (!XFile::is_file_exist_dir(db_path))
    {
        XFile::create_dir(db_path, false, false);
    }

    this->sql_path.clear();
    this->sql_path << db_path << name << L"_" << md5 << L".db";

    if (XFile::is_file_exist_file(this->sql_path))
    {
        return open_db();
    }
     
    return init_db();
}

bool XSQLite3::co_db()
{
    std::string utf_8;
    XString::ws2utf8(this->sql_path.get_wstr(), utf_8);

    if (utf_8.empty())
    {
        return false;
    }
      
    if (sqlite3_open(utf_8.c_str(), &db))
    {
        //fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return false;
    }

    return true;
}

bool XSQLite3::init_db()
{   
    if (!co_db())
    {
        //fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return false;
    }

    char *cc = "CREATE TABLE cc_break_point(" \
        "address     INT," \
        "number      INT," \
        "opcode      INT," \
        "activation  BOOL);";

    char *hard = "CREATE TABLE hard_break_point(" \
        "address    INT," \
        "dr_number  INT," \
        "length     INT," \
        "type       INT);";

    char *memory = "CREATE TABLE memory_break_point(" \
        "number      INT," \
        "page_base   INT," \
        "address     INT," \
        "length      INT," \
        "type        INT," \
        "old_protect INT);";

    char *comments = "CREATE TABLE comments(" \
        "address    INT," \
        "str        TEXT" \
        "type       BOOL);";

    char *alias = "CREATE TABLE alias(" \
        "address    INT," \
        "str        TEXT);";
     
    /* Execute SQL statement */
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, cc, nullptr, 0, &zErrMsg);
    if (rc != SQLITE_OK && zErrMsg != nullptr)
    { 
        sqlite3_free(zErrMsg);
        return false;
    }

    rc = sqlite3_exec(db, hard, nullptr, 0, &zErrMsg);
    if (rc != SQLITE_OK && zErrMsg != nullptr)
    {
        sqlite3_free(zErrMsg);
        return false;
    }

    rc = sqlite3_exec(db, memory, nullptr, 0, &zErrMsg);
    if (rc != SQLITE_OK && zErrMsg != nullptr)
    {
        sqlite3_free(zErrMsg);
        return false;
    }

    rc = sqlite3_exec(db, comments, nullptr, 0, &zErrMsg);
    if (rc != SQLITE_OK && zErrMsg != nullptr)
    {
        sqlite3_free(zErrMsg);
        return false;
    }

    rc = sqlite3_exec(db, alias, nullptr, 0, &zErrMsg);
    if (rc != SQLITE_OK && zErrMsg != nullptr)
    {
        sqlite3_free(zErrMsg);
        return false;
    }
     
    return true;
}
 
bool XSQLite3::open_db()
{
    if (!co_db())
    {
        //fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return false;
    }
     
    return true;
} 