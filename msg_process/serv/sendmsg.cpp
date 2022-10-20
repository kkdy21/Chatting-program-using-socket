#include <cstring>
using namespace std;
#include "sendmsg.h"
#include "send.h"
#define MAX_BUF 100
#define MAX_NAME 50

void SendMsg::SendMsgData(int flag, int sock, int *socks, char *name, char *msg, int clnt_cnt)
{
    Write<int, char> w;
    char t_msg[MAX_BUF + MAX_NAME];

    if (flag == -1)
    {
        sprintf(t_msg, "%s : %s", name, msg);

        for (int i = 0; i < clnt_cnt; i++)
        {
            w.WriteData(socks[i], t_msg, sizeof(t_msg));
        }
    }
    else
    {
        sprintf(t_msg, "\033[0;32m%s : %s\033[0m", name, msg);

        w.WriteData(sock, t_msg, sizeof(t_msg));
        w.WriteData(socks[flag], t_msg, sizeof(t_msg));
    }
}