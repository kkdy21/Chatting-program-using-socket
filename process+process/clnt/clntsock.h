#ifndef CLNTSOCK_H
#define CLNTSOCK_H

#include "sock.h"
#include "addr.h"

class ClntSock : public Sock, public Addr
{
public :
    void Connect();    
};

#endif