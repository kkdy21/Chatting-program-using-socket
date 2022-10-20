#include "servermain.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string>

ServMain::ServMain(int pt)
{
    port = pt;
    process.resize(1);
    sub_process.resize(1);
    clnt_cnt = 0;
}

void ServMain::Main()
{
    char buf[100];
    char name[50];

    pipe(pipe_1);
    pipe(pipe_2);
    process.at(0) = fork();

    if (process.at(0) == 0)
    {
        for (;;)
        {
            read(pipe_1[0], buf, sizeof(buf)); //클라이언트로 부터 온 메세지를 읽음
            for (int i = 0; i < clnt_cnt + 2; i++)
            {
                write(pipe_2[1], buf, sizeof(buf)); //메세지를 클라이언트와 연결된 프로세스에 뿌려줌
            }
        }
    }
    else
    {
        Servsock::CreateSock();
        Servsock::SetAddr(port);
        Servsock::Binding();
        Servsock::Listen();

        for (;;)
        {
            Accept();
            cout << "클라이언트가 접속했습니다." << endl;
            clnt_cnt++;
            process.resize(clnt_cnt + 1);

            process.at(clnt_cnt) = fork();

            if (process.at(clnt_cnt) == 0)
            {
                close(my_sock);

                sub_process.resize(clnt_cnt);
                sub_process.at(clnt_cnt - 1) = fork();
                if (sub_process.at(clnt_cnt - 1) == 0)
                {
                    for (;;)
                    {
                        read(clnt_sock, buf, sizeof(buf));  //클라이언트로부터 메세지 읽음
                        write(pipe_1[1], buf, sizeof(buf)); //write 프로세스로 메세지 보냄
                    }
                }

                else
                {
                    for (;;)
                    {

                        read(pipe_2[0], buf, sizeof(buf)); //write프로세스로 부터 메세지를 읽음

                        write(clnt_sock, buf, sizeof(buf)); //연결된 클라이언트로 메세지 보냄
                    }
                }

                return;
            }

            else
            {
                close(clnt_sock);
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

