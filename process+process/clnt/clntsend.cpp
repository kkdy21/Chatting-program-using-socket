#include "clntsend.h"
#include "send.h"
#include <sys/socket.h>

using namespace std;

#define MAX_BUF 100

void ClntSend::clntSend(int sock)
{
    Write<int, char> w;

    char message[MAX_BUF] = "\0";

    for (;;)
    {
        rewind(stdin);
        cin.getline(message, sizeof(message));

        if (message[0] == 'q' || message[0] == 'Q')
        {
            if (message[1] == '\0')
            {
                // w.WriteData(sock, message, sizeof(message));    //종료메세지
                return;
                
            }
        }
        w.WriteData(sock, message, sizeof(message));
    }
}