#include <iostream>
#include <unistd.h>
#include <string>
#include <thread>
using namespace std;

#include "servermain.h"

ServMain::ServMain(int pt)
{
    port = pt;
}

void ServMain::Main()
{
    Servsock::CreateSock();
    Servsock::SetAddr(port);
    Servsock::Binding();
    Servsock::Listen();

    for (;;)
    {
        Accept();
        cout << "유저가 접속 하였습니다." << endl;
        thread t(&MsgMain::MsgHandling, this, clnt_sock);
        t.detach();
    }

    close(my_sock);
}

void ServMain::Accept()
{
    int clnt_adr_sz = sizeof(clnt_addr);
    clnt_sock = accept(my_sock, (struct sockaddr *)&clnt_addr, (socklen_t *)&clnt_adr_sz);
}