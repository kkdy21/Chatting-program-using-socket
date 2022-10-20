#ifndef __ADDR_H_
#define __ADDR_H_

#include <arpa/inet.h>

class Addr
{
protected : 
    struct  sockaddr_in addr;
public :
   void SetAddr(int port);
   void SetAddr(int port, char *adr);
};

#endif

