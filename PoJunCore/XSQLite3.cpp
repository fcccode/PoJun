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

bool XSQLite3::init_db()
{
    return true;
}
 
bool XSQLite3::open_db()
{
    return true;
}
