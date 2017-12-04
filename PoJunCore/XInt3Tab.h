#pragma once
#include "XPJCoreHead.h"
#include <map>

class XInt3Tab
{
public:
    XInt3Tab();
    ~XInt3Tab();

    static XInt3Tab* m_This;
    static XInt3Tab* pins();

    void create_process(CREATE_PROCESS_DEBUG_INFO* cp, HANDLE process);
    
    bool is_start_opcode(DWORD opcode);
    
    bool reduction_oep(HANDLE handle);

    bool reduction_cc(HANDLE handle, DWORD address, bool status);

    bool reduction_break_point(HANDLE process, const XString& file_name, DWORD address);

    bool set_reduction_single_step(CONTEXT& context);
      
    DWORD get_reduction_single_step(); 

    bool insert_table(CC_BREAK_POINT& table);

    bool insert_cc(HANDLE handle, DWORD address);

    bool remove_cc(HANDLE handle, DWORD address);
      
    bool is_my_cc(HANDLE handle, DWORD address);

    bool set_cc_status(HANDLE handle, int index, bool status);
    
    bool get_cc_table(std::map<DWORD, CC_BREAK_POINT>& out_map);

    bool delete_cc_inedx(int inedx);

    bool insert_p_single_step(HANDLE handle, DWORD address);

    bool is_p_single_step(HANDLE handle, DWORD address);

private:
    bool set_opcode(HANDLE handle, DWORD address, BYTE& i_opcode, BYTE& o_opcode);

    int get_index();

private:
    BYTE int3;
    DWORD start_oep;  
    BYTE start_opcode;

    //int3�����
    //DWORD:��ַ��BYTE:�����ǵ�Դopcode
    std::map<DWORD, CC_BREAK_POINT> cc_table;
    std::vector<int> cc_table_num_mgr;

    //������
    std::map<DWORD, BYTE> single_step_table;

    DWORD reduction_address; 
};

