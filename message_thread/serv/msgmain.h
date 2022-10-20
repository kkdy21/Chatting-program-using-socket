#ifndef __MSGMAIN_H_
#define __MSGMAIN_H_
#include <vector>
#include <string>
using namespace std;

class MsgMain
{
protected:
    vector<vector<int>> room;
    vector<vector<char *>> room_use_name;
    vector<int> clnt_socks;
    vector<string> user_names;
    int clnt_cnt = 0;
    int inv = 0;
    int inv_sock = 0;
    int notice_flag = 0;
    char notice[150] = "\0";

public:
    MsgMain() {}
    ~MsgMain() {}
    void MsgHandling(int arg);
    int UserResistration(int sock, int size, char *name);
    int Whisper(string msg, char *rmsg, int room_num, int sock);
    int SelectRoom(int sock, char *name);
    int ClntSpace(int sock, int room_num);
    int ExitRom(int room_num, int clnt_point);
    int Notice(string msg, char *rmsg, char *name, int cnt);
};

#endif