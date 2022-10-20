#ifndef SERVERMAIN_H
#define SERVERMAIN_H

#include <vector>
#include <string>

#include "Select.h"
#include "servsock.h"

using namespace std;

class ServMain : public Select , public Servsock
{

private:
    vector<int> clnt_socks;
    vector<string> user_names;

    struct sockaddr_in clnt_addr;
    int clnt_sock = 0;
    int clnt_cnt = 0;
    int port = 0;
    int fd_max;
    int fd_num;
    int str_len;

public:
    ServMain(int pt);
    void Main();
    void Accept();
    int UserResistration(int sock, int size, char *name);
    int Whisper(string msg, char *rmsg);
    
};

#endif