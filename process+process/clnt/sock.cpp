#include <arpa/inet.h>
#include <sys/socket.h>
#include "sock.h"

void Sock::CreateSock()
{
    my_sock = socket(PF_INET, SOCK_STREAM,0);
}

int Sock::ReturnSock()
{
    return my_sock;
}