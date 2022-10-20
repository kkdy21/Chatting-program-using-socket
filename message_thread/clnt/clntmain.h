#ifndef __CLNTMAIN_H
#define __CLNTMAIN_H

#include "clntsock.h"
#include "clntsend.h"
#include "clntrecv.h"
#define MAX_NAME 50

class ClntMain : public ClntSock, public ClntSend, public ClntRecv
{
private:
    int port = 0;
    char *addr;
    struct sockaddr_in serv_sock;
    char name[MAX_NAME] = "\0";

public:
    ClntMain() {}
    ~ClntMain() {}
    ClntMain(int pt, char *adr);
    void Main();
    int UserRegistration();
};
#endif