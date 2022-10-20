#include <iostream>
using namespace std;
#include "servsock.h"

#define MAX_READY 5

void Servsock::Binding()
{
    if(bind(my_sock, (struct sockaddr*)&addr,sizeof(addr)))
    {
        cout << "bind() error" << endl;
        exit(1);
    }
}

void Servsock::Listen()
{
    if(listen(my_sock, MAX_READY))
    {
        cout << "listen() error" << endl;
        exit(1); 
    }
}