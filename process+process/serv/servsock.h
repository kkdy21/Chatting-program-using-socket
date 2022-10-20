#ifndef __SERVSOCK_H_
#define __SERVSOCK_H_

#include <sys/socket.h>
#include "addr.h"
#include "sock.h"

class Servsock : public Sock, public Addr
{
public:
    Servsock() {}
    ~Servsock() {}
    void Binding();
    void Listen();
};

#endif
