#ifndef SERVERMAIN_H
#define SERVERMAIN_H

#include <vector>
#include <string>
#include "servsock.h"

using namespace std;

class ServMain : public Servsock
{

private:

    vector<int> clnt_socks;
    vector<pid_t> process;
    vector<pid_t> sub_process;
    struct sockaddr_in clnt_addr;


    int pipe_1[2], pipe_2[2];
    pid_t main_process;

    int clnt_sock = 0;
    int clnt_cnt;
    int port = 0;
    int str_len;
   
public:
    ServMain(int pt);
    void Main();
    void Accept();
};

#endif