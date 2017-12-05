#include "stdafx.h"
#include "XSQLite3.h"
#include <XFileMD5.h>
#include <XFile.h>
#include <XEnvironment.h>
#include <sqlite3.h> 
#include "XInt3Tab.h"
#include "XHardwareBreak.h"


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
        return false;
    }
     
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, CC_TAB, nullptr, 0, &zErrMsg);
    if (rc != SQLITE_OK && zErrMsg != nullptr)
    { 
        sqlite3_free(zErrMsg);
        return false;
    }

    rc = sqlite3_exec(db, HARD_TAB, nullptr, 0, &zErrMsg);
    if (rc != SQLITE_OK && zErrMsg != nullptr)
    {
        sqlite3_free(zErrMsg);
        return false;
    } 

    rc = sqlite3_exec(db, COMMENT_TAB, nullptr, 0, &zErrMsg);
    if (rc != SQLITE_OK && zErrMsg != nullptr)
    {
        sqlite3_free(zErrMsg);
        return false;
    }

    rc = sqlite3_exec(db, ALIAS_TAB, nullptr, 0, &zErrMsg);
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

    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, SELECT_CC_TAB, cc_callback, nullptr, &zErrMsg);
    if (rc != SQLITE_OK){ 
        sqlite3_free(zErrMsg);
    }
     
    rc = sqlite3_exec(db, SELECT_HARD_TAB, hard_callback, nullptr, &zErrMsg);
    if (rc != SQLITE_OK){
        sqlite3_free(zErrMsg);
    }
      
    rc = sqlite3_exec(db, SELECT_COMMENTS_TAB, comments_callback, nullptr, &zErrMsg);
    if (rc != SQLITE_OK){
        sqlite3_free(zErrMsg);
    }

    rc = sqlite3_exec(db, SELECT_ALIAS_TAB, alias_callback, nullptr, &zErrMsg);
    if (rc != SQLITE_OK){
        sqlite3_free(zErrMsg);
    }
     
    return true;
} 

int XSQLite3::cc_callback(void *data, int argc, char **argv, char **azColName)
{
    if (argc != 5)
    {
        return 1;
    }

    CC_BREAK_POINT bp;
    bp.module_name = argv[0];
    bp.offset = XString(argv[1]).to_int();
    bp.number = XString(argv[2]).to_int();
    bp.opcode = XString(argv[3]).to_int();
    bp.activation = XString(argv[4]).to_int()? true : false;
    XInt3Tab::pins()->insert_table(bp); 

    return 0;
}

int XSQLite3::hard_callback(void *data, int argc, char **argv, char **azColName)
{
    if (argc != 4)
    {
        return 1;
    }

    HARD_DWARE_BREAK_POINT hb;
    hb.address = XString(argv[0]).to_int();
    hb.dr_number = XString(argv[1]).to_int();
    hb.length = XString(argv[2]).to_int();
    hb.type = XString(argv[3]).to_int();
    XHardwareBreak::pins()->insert(hb);

    return 0;
}
 
int XSQLite3::comments_callback(void *data, int argc, char **argv, char **azColName)
{
    return 0;
}

int XSQLite3::alias_callback(void *data, int argc, char **argv, char **azColName)
{
    return 0;
}

bool XSQLite3::insert_break_point(CC_BREAK_POINT& bp)
{
    int status = bp.activation;
    XString sql;
    sql << L"INSERT INTO cc_break_point VALUES ("
        << L"\"" << bp.module_name << L"\", "
        << bp.offset << L", "
        << bp.number << L", "
        << bp.opcode << L", "
        << status << L");";

    char* zErrMsg = nullptr;
    int rc = sqlite3_exec(this->db, sql.get_str().c_str(), nullptr, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        sqlite3_free(zErrMsg);
        return false;
    }

    return true;
}

bool XSQLite3::insert_hardwate_break(HARD_DWARE_BREAK_POINT& hb)
{
    XString sql;
    sql << L"INSERT INTO hard_break_point VALUES ("
        << hb.address   << L", "
        << hb.dr_number << L", "
        << hb.length    << L", "
        << hb.type      << L");";

    char* zErrMsg = nullptr;
    int rc = sqlite3_exec(this->db, sql.get_str().c_str(), nullptr, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        sqlite3_free(zErrMsg);
        return false;
    }

    return true;
}