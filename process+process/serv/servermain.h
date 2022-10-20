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
    vector<string> user_names;


    vector<pid_t> process;
    struct sockaddr_in clnt_addr;
    
    int pipe_1[2], pipe_2[2];
    pid_t main_process;
    // pid_t process[4];
    pid_t sub_process;

    int clnt_sock = 0;
    int clnt_cnt;
    int port = 0;
    int str_len;
   
public:
    ServMain(int pt);
    void Main();
    void Accept();
    int UserResistration(int sock, int size, char *name);
    int Whisper(string msg, char *rmsg);
};

#endif