#include <string>
#include <iostream>
using namespace std;
#define MAX_BUF 100
#define MAX_NAME 50
#include "clntrecv.h"
#include "recv.h"

void ClntRecv::clntRecv(int sock)
{
    char message[MAX_BUF + MAX_NAME] = "\0";
    int flag = 0;
    string ext;
    string notice;
    Recv<int, char> rc;
    for (;;)
    {
        if (flag == 0)
        {
            system("clear");
            char res = '0';
            PrintChatLog();
            if (rc.RecvData(sock, &res, sizeof(res)) == 1)
            {
                exit(1);
            }
            if (res == '7' || res == '8')
            {
                system("clear");
                cout << atoi(&res) - 6 << "번 방에서 초대가 왔습니다!" << endl;
                cout << "들어가시겠습니까?<y/n>" << endl;

                if (rc.RecvData(sock, &res, sizeof(res)) == 1)
                {
                    exit(1);
                }
            }

            if (res == '1')
            {
                flag = 1;
            }
            else if (res == '3')
            {
                res = '0';
            }
        }
        else
        {
            if (rc.RecvData(sock, message, sizeof(message)) == 1)
            {
                exit(1);
            }
            ext = message;
            if (ext == "/exit")
            {
                flag = 0;
                for (int i = 0; i < messages.size(); i++)
                {
                    messages[i].clear();
                }
                messages.resize(10);
                messages.shrink_to_fit();
                continue;
            }
            else if (ext.find("[공지]") != string::npos)
            {
                notice = message;
            }
            PrintMsg(message, notice);
        }
    }
}
void ClntRecv::PrintChatLog()
{
    cout << "=====================================================================" << endl;
    cout << "                         Chat Room List" << endl;
    cout << "=====================================================================" << endl;
    cout << "\n\n1번 채팅방 모두 신나는 채팅 타임~!" << endl;
    cout << "\n\n2번 채팅방 불타오르는 채팅 타임~!" << endl;
    cout << "\n\n3번 나가기" << endl;
    cout << "\n\n=====================================================================" << endl;
    cout << "                        실행할 번호 + Enter" << endl;
    cout << "=====================================================================" << endl;
}

void ClntRecv::PrintMsg(string msg, string notice)
{
    system("clear");
    cout << "=====================================================================" << endl;
    cout << "                              MESSAGE" << endl;
    cout << "=====================================================================" << endl;
    cout << notice << endl;
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
    cout << "  /+ : 메세지로그 올리기 | /- : 메세지로그 내리기 | /사용자명 : 귓속말" << endl;
    cout << "=====================================================================" << endl;
    cout << "  /공지 : 공지 보내기    |  /i 초대자명 : 유저 초대" << endl;
    cout << "=====================================================================" << endl;
}