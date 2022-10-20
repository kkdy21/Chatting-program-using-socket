#ifndef __SOCK_H_
#define __SOCK_H_

class Sock
{
protected :
    int my_sock = 0;
public :
    Sock(){};
    ~Sock(){};
    void CreateSock();
    int ReturnSock();
};

#endif