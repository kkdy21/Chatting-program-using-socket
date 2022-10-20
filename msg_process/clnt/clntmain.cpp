#include "clntmain.h"
#include "send.h"
#include <sys/wait.h>
using namespace std;

ClntMain::ClntMain(int port, char *addr)
{
    this->port = port;
    this->addr = addr;
}

void ClntMain::Clntmain()
{
    int status;
    messages.resize(10);
    ClntSend c;
    CreateSock();
    SetAddr(port, addr);
    Connect();
    UserRegistration();

    process = fork();

    if (process == -1)
        exit(1);

    else if (process == 0)
    {
        c.clntSend(my_sock);
        process = getppid();
        kill(process, SIGKILL);
    }

    else
    {

        clntRecv(my_sock);
    }
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
