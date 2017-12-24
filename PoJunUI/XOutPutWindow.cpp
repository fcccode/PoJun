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
            << L"EBP=" << XString(it->context.Ebp).to_hex_str() << L"\r\n"
            << L"CS=" << XString(it->context.SegCs).to_hex_str() << L" "
            << L"SS=" << XString(it->context.SegSs).to_hex_str() << L" "
            << L"DS=" << XString(it->context.SegDs).to_hex_str() << L" "
            << L"ES=" << XString(it->context.SegEs).to_hex_str() << L" "
            << L"FS=" << XString(it->context.SegFs).to_hex_str() << L" "
            << L"GS=" << XString(it->context.SegGs).to_hex_str() << L" "
            << L"        ";

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
        str << L"\r\n";

        std::list<DECODEING_ASM>::const_iterator ait = it->asm_tab.cbegin();
        int i = 0;
        for (ait; ait != it->asm_tab.cend() && i < 1; ait++, i++)
        { 
            str << XString(ait->address).to_hex_str() << L":   " << ait->asm_str.w_cstr() << "L\r\n";
        }

        opw.show_text->setText(str.get_str().c_str());
        str = L"";
    } 
}