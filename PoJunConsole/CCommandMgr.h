#pragma once

enum _CommandUI
{
    E_,
    E_OPEN_FILE,
    E_ACTIVE_PROCESS
};


class CCommandMgr
{
public:
    CCommandMgr();
    ~CCommandMgr();

    static CCommandMgr* m_This;
    static CCommandMgr* pins();

    void command_ui(int type);

};

