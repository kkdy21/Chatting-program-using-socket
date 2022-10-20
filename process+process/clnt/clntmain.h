#ifndef CLNTMAIN_H
#define CLNTMAIN_H

#include "clntsock.h"
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include "recv.h"
#include "clntsend.h"
#include "clntrecv.h"

class ClntMain : public ClntSock , public ClntRecv
{
private:
    int port;
    char *addr;

    pid_t process;

    char buf[100];
    char name[50];

public:
    ClntMain(int port, char *addr);
    void Clntmain();
    int UserRegistration();
};


#endif