#ifndef __SENDMSG_H_
#define __SENDMSG_H_

class SendMsg
{
public:
    void SendMsgData(int flag, int sock, int *socks, char *name, char *msg, int size);
};

#endif