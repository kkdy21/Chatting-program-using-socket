#include "servermain.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include "recv.h"
#include "send.h"
#include "useroverlap.h"

ServMain::ServMain(int pt)
{
    port = pt;
}

void ServMain::Main()
{
    char buf[100];
    Servsock::CreateSock();
    Servsock::SetAddr(port);
    Servsock::Binding();
    Servsock::Listen();
    Select::FD_ZERO_FUNC();
    Select::FD_SET_FUNC(my_sock);
    fd_max = my_sock;

    Write<int, char> w;
    Recv<int, char> r;

    int temp;
    char name[50];

    for (;;)
    {
        if ((temp = Select_func(&fd_max)) == -1)
            break;

        if (temp == 0)
            continue;

        for (int i = 0; i < fd_max + 1; i++)
        {
            if (FD_ISSET_FUNC(i))
            {

                if (i == my_sock)
                {

                    Accept();
                    UserResistration(clnt_sock, sizeof(name), name);
                    FD_SET_FUNC(clnt_sock);

                    if (fd_max < clnt_sock)
                    {
                        fd_max = clnt_sock;
                        for (int j = my_sock + 1; j < fd_max + 1; j++)
                            w.WriteData(j, (char *)"유저가 접속했습니다.", sizeof(buf));
                    }
                }

                else
                {

                    if (r.RecvData(i, buf, sizeof(buf)) == 1) //종료요청이면
                    {
                        char quit = 'q';
                        write(i, &quit, sizeof(quit));
                        vector<string>::iterator itr = user_names.begin() + i - 4;
                        user_names.erase(itr);
                        user_names.shrink_to_fit();
                        FD_CLEAR_FUNC(i);
                        clnt_cnt--;
                        close(i);
                    }

                    else
                    {

                        int number = -1;
                        char t_buf[150] = "\0";
                        number = Whisper(buf, buf);
                        if (number == -1)
                        {
                            sprintf(t_buf, "%s : %s", user_names.at(i - 4).data(), buf);
                            for (int j = my_sock + 1; j < fd_max + 1; j++)
                                w.WriteData(j, t_buf, sizeof(t_buf));
                        }
                        else
                        {
                            sprintf(t_buf, "\033[0;32m%s : %s\033[0m", user_names.at(i - 4).data(), buf);
                            w.WriteData(i, t_buf, sizeof(t_buf));
                            w.WriteData(number + 4, t_buf, sizeof(t_buf));
                        }
                    }
                }
            }
        }
    }
}

void ServMain::Accept()
{
    int clnt_adr_sz = sizeof(clnt_addr);
    clnt_sock = accept(my_sock, (struct sockaddr *)&clnt_addr, (socklen_t *)&clnt_adr_sz);
}

int ServMain::UserResistration(int sock, int size, char *name)
{
    int res = 0;
    UserOverlap u;
    Recv<int, char> r;
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
    return 0;
}

int ServMain::Whisper(string msg, char *rmsg)
{
    for (int i = 0; i < clnt_cnt; i++)
    {
        if (msg.find(("/" + user_names[i])) != string::npos)
        {
            msg.replace(0, user_names[i].size() + 2, "");
            copy(&msg[0], &msg[0] + msg.size() + 1, &rmsg[0]);
            return i;
        }
    }
    return -1;
}