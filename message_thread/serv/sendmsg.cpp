#include <cstring>
using namespace std;
#include "sendmsg.h"
#include "send.h"
#define MAX_BUF 100
#define MAX_NAME 50

void SendMsg::SendMsgData(int flag, int sock, int *socks, char *name, char *msg, int size)
{
    Write<int, char> w;
    string opt = msg;
    char t_msg[MAX_BUF + MAX_NAME];

    if (flag == -1)
    {
        if (opt == "/+" || opt == "/-")
        {
            sprintf(t_msg, "%s", msg);
            w.WriteData(sock, msg, sizeof(t_msg));
        }
        else if (opt == "/exit")
        {
            sprintf(t_msg, "%s", msg);
            w.WriteData(sock, msg, sizeof(t_msg));
            sprintf(msg, "SYSTEM : %s님이 퇴장하였습니다.", name);
            for (int i = 0; i < size; i++)
            {
                w.WriteData(socks[i], msg, sizeof(t_msg));
            }
        }
        else
        {
            sprintf(t_msg, "%s : %s", name, msg);

            for (int i = 0; i < size; i++)
            {
                w.WriteData(socks[i], t_msg, sizeof(t_msg));
            }
        }
    }
    else if (flag == 7 || flag == 8)
    {
        sprintf(t_msg, "\033[0;33mSYSTEM : 초대 요청을 보냈습니다.\033[0m");
        w.WriteData(sock, t_msg, sizeof(t_msg));
    }
    else
    {
        sprintf(t_msg, "\033[0;32m%s : %s\033[0m", name, msg);

        w.WriteData(sock, t_msg, sizeof(t_msg));
        w.WriteData(socks[flag], t_msg, sizeof(t_msg));
    }
}