#ifndef __SERVERMAIN_
#define __SERVERMAIN_

#include <vector>
using namespace std;
#include "servsock.h"
#include "msgmain.h"

class ServMain : public Servsock, public MsgMain
{
private:
    struct sockaddr_in clnt_addr;
    int clnt_sock = 0;
    int port = 0;
    pthread_t t_id;

public:
    ServMain() {}
    ~ServMain() {}
    ServMain(int pt);
    void Main();
    void Accept();
};

#endif