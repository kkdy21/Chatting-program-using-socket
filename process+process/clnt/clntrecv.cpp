#include <sys/wait.h>
#include <iostream>
using namespace std;
#define MAX_BUF 100
#define MAX_NAME 100
#include "clntrecv.h"
#include "recv.h"

void ClntRecv::clntRecv(int sock)
{
    int status;
    char message[MAX_BUF + MAX_NAME] = "\0";
    Recv<int, char> rc;
    for (;;)
    {
        if (rc.RecvData(sock, message, sizeof(message)) == 1)
        {
            cout << "종료1" << endl;
            return;
        }

        PrintMsg(message);
    }
}

void ClntRecv::PrintMsg(string msg)
{
    system("clear");
    cout << "=====================================================================" << endl;
    cout << "                              MESSAGE" << endl;
    cout << "=====================================================================" << endl;
    if (msg.find("/+") != string::npos)
    {
        range_min++;
        range_max++;
        for (int i = messages.size() - range_max; i < messages.size() - range_min; i++)
            cout << messages[i] << endl;
    }

    else if (msg.find("/-") != string::npos)
    {
        range_min--;
        range_max--;
        if (range_min < 0)
        {
            range_min = 0;
            range_max = 10;
        }
        for (int i = messages.size() - range_max; i < messages.size() - range_min; i++)
            cout << messages[i] << endl;
    }
    else
    {
        messages.push_back(msg);
        messages.shrink_to_fit();
        range_min = 0;
        range_max = 10;

        for (int i = messages.size() - range_max; i < messages.size() - range_min; i++)
            cout << messages[i] << endl;
    }
    cout << "=====================================================================" << endl;
    cout << "    /+: 메세지로그 올리기 | /- 메세지로그 내리기 | /사용자명 귓속말" << endl;
    cout << "=====================================================================" << endl;
}