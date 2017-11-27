// DebugTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h" 
#include <memory.h>

int _tmain(int argc, _TCHAR* argv[])
{
    char sz[10] = { 0 };
    bool status = true;
    printf("aaaaaaaaaaaa \r\n");

    while (status)
    {
        for (int i = 0; i < 10; i++)
        {
            sz[i] = i;
        }

        for (int i = 0; i < 10; i++)
        {
            int j = sz[i];
            printf("%d", j);
        }

        printf("\r\n");
        memset(sz, 0x0, 10);
    }

	return 0;
}

