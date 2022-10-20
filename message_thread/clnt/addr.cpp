#include <iostream>
#include <cstring>

using namespace std;

#include "addr.h"

void Addr::SetAddr(int port)
{
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
}

void Addr::SetAddr(int port, char *adr)
{
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(adr);
    addr.sin_port = htons(port);
}