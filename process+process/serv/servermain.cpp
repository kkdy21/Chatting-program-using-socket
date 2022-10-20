#include "servermain.h"
#include "useroverlap.h"
#include "recv.h"
#include "send.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string>

ServMain::ServMain(int pt)
{
    port = pt;
    clnt_cnt = 0;
}

void ServMain::Main()
{
    char buf[200] = "\0";
    char name[50];

    pipe(pipe_1);
    pipe(pipe_2);

    main_process = fork();

    if (main_process == 0)
    {
        Servsock::CreateSock();
        Servsock::SetAddr(port);
        Servsock::Binding();
        Servsock::Listen();

        for (;;)
        {
            Accept();
            UserResistration(clnt_sock, sizeof(name), name);
            cout << "클라이언트가 접속했습니다." << endl;
            process.resize(clnt_cnt + 1);

            strcpy(buf, "클라수증가");
            write(pipe_1[1], buf, sizeof(buf));
            buf[0] = '\0';

            process.at(clnt_cnt) = fork();

            if (process.at(clnt_cnt) == 0)
            {
                close(my_sock);

                sub_process = fork();

                if (sub_process == 0)
                {   
                    char t_buf[150];

                    for (;;)
                    {
                        int disconnect = 0;
                        if (read(clnt_sock, t_buf, sizeof(t_buf)) == 0) //클라이언트로부터 메세지 읽음
                        {
                            cout << "연결이끊겼습니다." << endl;
                            strcpy(buf, "연결이끊겼습니다.");

                            write(pipe_1[1], buf, sizeof(buf));
                            close(clnt_sock);
                            return;
                        }
                        cout << "클라이언트로 부터 메세지를 읽었습니다." << endl;

                        sprintf(buf, "%s : %s", user_names.at(clnt_cnt).data(), t_buf);

                        write(pipe_1[1], buf, sizeof(buf)); //write 프로세스로 메세지 보냄

                        cout << "write 프로세스로 메세지를 보냅니다." << endl;
                    }
                }

                else
                {
                    char t_buf[200];
                    int number = -1;

                    for (;;)
                    {
                        read(pipe_2[0], buf, sizeof(buf)); //write프로세스로 부터 메세지를 읽음
                        cout << buf << clnt_sock << endl;
                        cout << "write 프로세스로 부터 메세지를 읽었습니다. : " << sub_process << " 이 읽었습니다.@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

                        number = Whisper(buf, buf);

                      
                        if(number ==1)
                        {
                            //sprintf(t_buf, "\033[0;32m%s\033[0m",buf);
                            
                            
                            cout << "귓속말작동!@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
                        }

                        if (write(clnt_sock, buf, sizeof(buf)) == -1)
                        {
                            close(clnt_sock);
                            return;
                        } //연결된 클라이언트로 메세지 보냄

                        cout << "연결된 클라이언트로 메세지를 보냅니다." << endl;
                        usleep(3000); // 차례로 받게하기위해
                    }
                }

                return;
            }

            else
            {
                close(clnt_sock);
                clnt_cnt++;
            }
        }
    }
    else
    {
        for (;;)
        {
            read(pipe_1[0], buf, sizeof(buf)); //클라이언트로 부터 온 메세지를 읽음
            if (strcmp(buf, "클라수증가") == 0)
            {
                clnt_cnt++;
                buf[0] = '\0';
                continue;
            }

            else if (strcmp(buf, "연결이끊겼습니다.") == 0)
            {
                clnt_cnt--;
                buf[0] = '\0';
                continue;
            }

            cout << "파이프로 연결된 클라이언트프로세스로 부터 메세지를 읽습니다." << endl;

            // cout<<clnt_cnt<<endl;
            for (int i = 0; i < clnt_cnt; i++)
            {

                write(pipe_2[1], buf, sizeof(buf)); //메세지를 클라이언트와 연결된 프로세스에 뿌려줌
                cout << "클라이언트 수 만큼 메세지를 뿌려줍니다." << endl;
            }
        }
    }
    return;
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

    return 0;
}

int ServMain::Whisper(string msg, char *rmsg)
{
    //    /내이름 -> 정제시작

    if (msg.find(("/" + user_names[clnt_cnt])) != string::npos)
    {
        cout << user_names[clnt_cnt] << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
        msg.replace(0, user_names[clnt_cnt].size() + 2, "");
        copy(&msg[0], &msg[0] + msg.size() + 1, &rmsg[0]);
        return 1;
    }

    return -1;
}