#include <iostream>
#include <thread>
#include <unistd.h>
#include <string>
#include <vector>
using namespace std;
#include "clntmain.h"
#include "send.h"
#include "recv.h"

ClntMain::ClntMain(int pt, char *adr)
{
    port = pt;
    addr = adr;
}

void ClntMain::Main()
{
    messages.resize(10);
    Write<int, char> w;

    CreateSock();

    SetAddr(port, addr);

    Connect();

    if (UserRegistration() == 1)
    {
        exit(0);
    }
    thread trecv(&ClntMain::clntRecv, this, my_sock);
    thread tsend(&ClntMain::clntSend, this, my_sock);

    tsend.join();
    trecv.join();

    close(my_sock);
}

int ClntMain::UserRegistration()
{
    int res = 0;
    Write<int, char> w;
    Recv<int, int> r;
    for (;;)
    {
        system("clear");
        cout << "닉네임을 지정해 주세요.(종료시 q)";
        cin >> name;
        cin.ignore();

        if (name[0] == 'q' && name[1] == '\0')
            return 1;
        else
        {

            w.WriteData(my_sock, name, sizeof(name));

            if (r.RecvData(my_sock, &res, 1) == 1)
                return 1;
            if (res == 0)
            {
                system("clear");
                cout << "등록 되었습니다." << endl;
                sleep(1);
                break;
            }
            else if (res == 1)
            {
                system("clear");
                cout << "중복되었습니다. 다시 입력해 주세요." << endl;
                sleep(1);
            }
        }
    }
    return 0;
}