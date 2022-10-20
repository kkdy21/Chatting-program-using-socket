#include <iostream>
#include <unistd.h>
#include <cstring>
using namespace std;
#include "send.h"
#include "recv.h"
#include "msgmain.h"
#include "useroverlap.h"
#include "sendmsg.h"

#define MAX_NAME 50
#define MAX_BUF 100

void MsgMain::MsgHandling(int arg)
{
    SendMsg smg;
    Recv<int, char> rc;
    int clnt_sock = arg;
    char sysmsg[MAX_BUF * 2] = "\0";
    char message[MAX_BUF] = "\0";
    char name[MAX_NAME] = "\0";
    string ext;
    int cnt = 0, flag = 0, flags = -1, room_flag = -1;
    int cnt_c = 0;
    inv = -1;
    room.resize(2);
    room.shrink_to_fit();
    room_use_name.resize(2);
    room_use_name.shrink_to_fit();

    flag = UserResistration(clnt_sock, MAX_NAME, name);

    for (;;)
    {
        if (room_flag == -1)
        {
            room_flag = SelectRoom(clnt_sock, name);
        }
        else if (room_flag == 2)
        {
            break;
        }
        else
        {
            int notice_judgment = 0;

            if (cnt_c == 0)
            {
                sprintf(sysmsg, "%s님이 입장하셨습니다.", name);
                smg.SendMsgData(flags, clnt_sock, room[room_flag].data(), (char *)"SYSTM", sysmsg, room[room_flag].size());
                cnt_c = 1;
                continue;
            }
            if (flag != 0)
            {
                break;
            }

            if (rc.RecvData(clnt_sock, message, sizeof(message)) != 0)
            {
                break;
            }
            ext = message;
            if (ext == "/exit")
            {
                ExitRom(room_flag, ClntSpace(clnt_sock, room_flag));
                smg.SendMsgData(flags, clnt_sock, room[room_flag].data(), name, message, room[room_flag].size());

                room_flag = -1;
                cnt_c = 0;
                continue;
            }
            flags = Whisper(message, message, room_flag, clnt_sock);
            notice_judgment = Notice(message, message, name, room_flag);
            if (flags == -1 && notice_judgment == 1) //공지메세지
            {
                Write<int, char> w;

                sprintf(sysmsg, "\033[0;31m%s의 공지 : %s\033[0m", name, message);
                for (int i = 0; i < room[room_flag].size(); i++)
                    w.WriteData(room[room_flag].at(i), sysmsg, sizeof(sysmsg));
                continue;
            }
            smg.SendMsgData(flags, clnt_sock, room[room_flag].data(), name, message, room[room_flag].size());
            flags = -1;
        }
    }

    cout << "유저가 떠났습니다." << clnt_cnt << endl;

    for (int i = 0; i < clnt_cnt; i++)
    {
        if (clnt_socks[i] == clnt_sock)
        {
            vector<int>::iterator itr = clnt_socks.begin();
            clnt_socks.erase(itr + i);
            clnt_socks.shrink_to_fit();
            vector<string>::iterator itr1 = user_names.begin();
            user_names.erase(itr1 + i);
            user_names.shrink_to_fit();
            clnt_cnt--;

            break;
        }
    }
    close(clnt_sock);
}

int MsgMain::UserResistration(int sock, int size, char *name)
{

    int res = 0;
    UserOverlap u;
    Recv<int, char> r;
    Write<int, char> w;

    for (;;)
    {
        if (r.RecvData(sock, name, size) == 0)
        {

            if (res = u.Overlap(user_names.data(), name, clnt_cnt + 1) != 0)
            {
                Write<int, int> w;
                w.WriteData(sock, &res, 1);
            }
            else
            {

                Write<int, int> w;
                w.WriteData(sock, &res, 1);
                break;
            }
        }
        else
        {
            return 1;
        }
    }

    user_names.push_back(name);
    user_names.shrink_to_fit();
    clnt_socks.push_back(sock);
    clnt_socks.shrink_to_fit();
    clnt_cnt++;

    if (notice_flag == 1) //공지 전송
    {
        w.WriteData(sock, notice, sizeof(notice));
    }

    return 0;
}

int MsgMain::Whisper(string msg, char *rmsg, int room_num, int sock)
{

    msg.replace(0, 1, "");

    for (int i = 0; i < room[room_num].size(); i++)
    {
        if (msg.find(room_use_name[room_num][i]) != string::npos && rmsg[0] == '/')
        {
            msg.replace(0, strlen(room_use_name[room_num].at(i)) + 1, "");
            copy(&msg[0], &msg[0] + msg.size() + 1, &rmsg[0]);
            return i;
        }
        else if (rmsg[0] == '/' && rmsg[1] == 'i' && rmsg[2] == ' ')
        {
            msg.replace(0, 1, "");

            for (int j = 0; j < clnt_cnt; j++)
            {
                if (msg.find(user_names[j]) != string::npos)
                {
                    inv_sock = sock;
                    char flag = '0' + i + 7;
                    Write<int, char> w1;
                    w1.WriteData(clnt_socks[j], &flag, sizeof(flag));
                    inv = room_num;
                    return 7 + i;
                }
            }
        }
    }
    return -1;
}

int MsgMain::SelectRoom(int sock, char *name)
{

    Write<int, char> w;
    Recv<int, char> r;
    char res = '\0';
    if (r.RecvData(sock, &res, sizeof(res)) == 1)
    {
        return 2;
    }
    if (res == '0' || res == '1')
    {
        int t_res = atoi(&res);
        char flag = '1';
        room[t_res].push_back(sock);
        room[t_res].shrink_to_fit();
        room_use_name[t_res].push_back(name);
        room_use_name[t_res].shrink_to_fit();
        w.WriteData(sock, &flag, sizeof(flag));

        return t_res;
    }
    else if (res == '2')
    {
        return 2;
    }
    else if (res == 'Y' || res == 'y')
    {
        if (inv != -1)
        {
            int t_res = atoi(&res);
            char flag = '1';
            room[t_res].push_back(sock);
            room[t_res].shrink_to_fit();
            room_use_name[t_res].push_back(name);
            room_use_name[t_res].shrink_to_fit();
            w.WriteData(sock, &flag, sizeof(flag));
            w.WriteData(sock, &flag, sizeof(flag));
            inv = -1;
            return t_res;
        }
        else
        {
            char flag = '3';
            w.WriteData(sock, &flag, sizeof(flag));
            w.WriteData(sock, &flag, sizeof(flag));
            return -1;
        }
    }
    else if (res == 'N' || res == 'n')
    {
        char flag = '3';
        w.WriteData(sock, &flag, sizeof(flag));
        if (inv != -1)
        {
            w.WriteData(inv_sock, (char *)"\033[0;31mSYSTEM : 초대가 거부되었습니다.\033[0m", sizeof("\033[0;31mSYSTEM : 초대가 거부되었습니다.\033[0m"));
            inv = -1;
        }
        return -1;
    }

    return 2;
}

int MsgMain::ClntSpace(int sock, int room_num)
{
    for (int i = 0; i < room[room_num].size(); i++)
    {
        if (room[room_num].at(i) == sock)
        {
            return i;
        }
    }
    return -1;
}

int MsgMain::ExitRom(int room_num, int clnt_point)
{
    vector<int>::iterator i_itr = room[room_num].begin();
    vector<char *>::iterator c_itr = room_use_name[room_num].begin();

    room[room_num].erase(i_itr + clnt_point);
    room[room_num].shrink_to_fit();
    room_use_name[room_num].erase(c_itr + clnt_point);
    room_use_name[room_num].shrink_to_fit();

    return 0;
}

int MsgMain::Notice(string msg, char *rmsg, char *name, int cnt)
{
    Write<int, char> w;

    if (msg.find("/공지") != string::npos)
    {
        msg.replace(0, sizeof("/공지"), "");
        copy(msg.begin(), msg.end() + 1, &rmsg[0]); //NULL값 까지 복사? &는 주소값부터 시작이므로
        sprintf(notice, "[공지] %s : %s", name, rmsg);
        notice_flag = 1;

        for (int i = 0; i < room[cnt].size(); i++) //공지전송
            w.WriteData(room[cnt].at(i), notice, sizeof(notice));

        return 1;
    }
    return 0;
}
