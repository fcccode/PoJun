#include "XOutPutWindow.h"
#include "XDateCenter.h"


XOutPutWindow::XOutPutWindow(QWidget *parent)
    : QDockWidget(parent)
{
    opw.setupUi(this);
    opw.vlayout->setMargin(0);
    opw.vlayout->setSpacing(0);
    opw.widget->setLayout(opw.vlayout);
}


XOutPutWindow::~XOutPutWindow()
{
} 

void XOutPutWindow::show_asm()
{
    XString str;
    std::vector<OUT_DATE> out_date;
    XDateCenter::pins()->get_out_date(out_date);

    std::vector<OUT_DATE>::iterator it = out_date.begin();
    for (it; it != out_date.end(); it++)
    { 
        DWORD dwFlags = 0;
        DWORD dwbite[8] = { 11, 10, 8, 7, 6, 4, 2, 0 };
        WCHAR chbite[8][2][3] = { { L"OV", L"NV" }, { L"DN", L"UP" }, { L"EI", L"DI" }, { L"NG", L"PL" },
        { L"ZR", L"NZ" }, { L"AC", L"NA" }, { L"PE", L"PO" }, { L"CY", L"NC" } };

        str << L"EAX=" << XString(it->context.Eax).to_hex_str() << L" "
            << L"EDX=" << XString(it->context.Edx).to_hex_str() << L" "
            << L"ECX=" << XString(it->context.Ecx).to_hex_str() << L" "
            << L"EBX=" << XString(it->context.Ebx).to_hex_str() << L" "
            << L"ESI=" << XString(it->context.Esi).to_hex_str() << L" "
            << L"EDI=" << XString(it->context.Edi).to_hex_str() << L"\r\n"
            << L"EIP=" << XString(it->context.Eip).to_hex_str() << L" "
            << L"ESP=" << XString(it->context.Esp).to_hex_str() << L" "
            << L"EBP=" << XString(it->context.Ebp).to_hex_str() << L"                ";

        for (int i = 0; i < 8; i++)
        {
            DWORD m = dwFlags;
            m = m >> dwbite[i] & 1;

            if (m == 1)
            {
                str << chbite[i][0] << L" ";
            }
            else
            {
                str << chbite[i][1] << L" ";
            }
        } 

        str << L"\r\n" 
            << L"CS=" << XString(it->context.SegCs).to_word_str() << L" "
            << L"SS=" << XString(it->context.SegSs).to_word_str() << L" "
            << L"DS=" << XString(it->context.SegDs).to_word_str() << L" "
            << L"ES=" << XString(it->context.SegEs).to_word_str() << L" "
            << L"FS=" << XString(it->context.SegFs).to_word_str() << L" "
            << L"GS=" << XString(it->context.SegGs).to_word_str() << L" "
            << L"          "
            << L"EFL=" << XString(it->context.SegGs).to_word_str() << L" "
            << L"        \r\n";  
         
        std::list<DECODEING_ASM>::const_iterator ait = it->asm_tab.cbegin();
        int i = 0;
        for (ait; ait != it->asm_tab.cend() && i < 1; ait++, i++)
        { 
            str << XString(ait->address).to_hex_str() << L":   " << ait->asm_str.w_cstr();
        }

        str << L"\r\n";

        QString qstr = QString::fromLocal8Bit(str.get_str().c_str());
        opw.show_text->append(qstr);
        str = L"";
    }  
}

void XOutPutWindow::show_run_command()
{
    DEBUG_MODULE_DATA md = XDateCenter::pins()->get_module_date();
    
    if (md.type == D_DB)
    {
        show_db(md.d_memory.memory_byte, md.d_memory.address);
    }
    else if (md.type == D_DW)
    {
        show_dw(md.d_memory.memory_byte, md.d_memory.address);
    }
    else if (md.type == D_DD)
    {
        show_dd(md.d_memory.memory_byte, md.d_memory.address);
    }
    else if (md.type == D_LM)
    {
        show_lm(md.module_table);
    }
    else if (md.type == D_THREAD)
    {
        show_thread(md.thread_table);
    }
}

void XOutPutWindow::show_db(const BYTE* memory_byte, DWORD address)
{ 
    const int ROW = 8;
    const int COL = 16;
    opw.show_text->append("");
    for (int i_row = 0; i_row < ROW; i_row++, address += 16)
    {
        XString str_mem_data;
        str_mem_data << XString(address).to_hex_str() << L":    " << XString(memory_byte + i_row * COL, COL) << L"     ";

        for (int i = 0; i < COL; i++)
        {
            char ch = *(char*)(memory_byte + i_row * ROW + i);
            if (ch > 0x7F || ch == 0x00 || ch == 0x07 || ch == 0x08
                || ch == 0x0A || ch == 0x0D || ch == 0x20 || ch == 0x25
                || ch == 0xFF)
            {
                str_mem_data << XString('.');
            }
            else
            {
                str_mem_data << XString(ch);
            }
        }

        opw.show_text->append(str_mem_data.get_str().c_str());
    }
     
    delete[] memory_byte;
}

void XOutPutWindow::show_dw(const BYTE* memory_byte, DWORD address)
{
    const int ROW = 8;
    const int COL = 8; 

    opw.show_text->append(""); 
    for (int i_row = 0; i_row < ROW; i_row++, address += 16)
    {
        XString str_mem_data;
        str_mem_data << XString(address).to_hex_str() << L":    ";
        for (int i_col = 0; i_col < COL; i_col)
        {
            BYTE low = *(memory_byte + i_row * ROW + i_col++);
            BYTE high = *(memory_byte + i_row * ROW + i_col++);

            XString::byte2str(high, str_mem_data);
            XString::byte2str(low, str_mem_data);
            str_mem_data << L"  ";
        }

        opw.show_text->append(str_mem_data.get_str().c_str()); 
    }
     
    delete[] memory_byte;
}

void XOutPutWindow::show_dd(const BYTE* memory_byte, DWORD address)
{
    const int ROW = 8;
    const int COL = 16;

    opw.show_text->append("");

    for (int i_row = 0; i_row < ROW; i_row++, address += 16)
    { 
        XString str_mem_data;
        str_mem_data << XString(address).to_hex_str() << L":    ";

        for (int i_col = 0; i_col < COL; i_col += 4)
        {
            BYTE low = *(memory_byte + i_row * (ROW * 2) + i_col);
            BYTE high = *(memory_byte + i_row * (ROW * 2) + i_col + 1);
            BYTE lowex = *(memory_byte + i_row * (ROW * 2) + i_col + 2);
            BYTE highex = *(memory_byte + i_row * (ROW * 2) + i_col + 3);
              
            XString::byte2str(highex, str_mem_data);
            XString::byte2str(lowex, str_mem_data);
            XString::byte2str(high, str_mem_data);
            XString::byte2str(low, str_mem_data);
            str_mem_data << L"  ";
        }
          
        opw.show_text->append(str_mem_data.get_str().c_str());
    }

    delete[] memory_byte;
}

void XOutPutWindow::show_lm(const std::map<DWORD, MODULE_INFO>& lm)
{
    std::map<DWORD, MODULE_INFO>::const_iterator it = lm.begin();

    int max_name_length = 0;
    for (it; it != lm.end(); it++)
    {
        int name_length = it->second.file_path.get_short_name().length(); 
        if (max_name_length < name_length)
        {
            max_name_length = name_length;
        }  
    }

    XString show_str;
    show_str << L"  基址       大小       入口     ";

    for (int i = 0; i < (max_name_length / 2) - 1; i++)
    {
        show_str << L" ";
    }

    show_str << L"名称";

    for (int i = 0; i < max_name_length / 2; i++)
    {
        show_str << L" ";
    }

    show_str << L"   版本       路径 \r\n";
      
    for (it = lm.begin(); it != lm.end(); it++)
    { 
        show_str << XString(it->first).to_hex_str() << L" | "
            << XString(it->second.size).to_hex_str() << L" | "
            << XString(it->second.enter).to_hex_str() << L" | "
            << it->second.file_path.get_short_name();

        for (int i = it->second.file_path.get_short_name().length(); i < max_name_length; i++)
        {
            show_str << L" ";
        }
        
        show_str << L" |  " 
            << XString(it->second.file_version).to_hex_str() << L" | "
            << it->second.file_path << L"\r\n"; 
    }
     
    QString qstr = QString::fromLocal8Bit(show_str.get_str().c_str()); 
    opw.show_text->append(qstr);
}

void XOutPutWindow::show_thread(const std::vector<THREAD_DATA>& lm)
{
    int i = 0;
}