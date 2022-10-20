#include <cstring>
using namespace std;
#include "clntsend.h"
#include "send.h"
#include "recv.h"
#define MAX_BUF 100

void ClntSend::clntSend(int sock)
{
    Write<int, char> w;
    int flag = 0;

    char message[MAX_BUF] = "\0";

    for (;;)
    {
        if (flag == 0)
        {
            char room_num = '\0';
            cin >> room_num;
            cin.ignore();

            if (room_num == '1' || room_num == '2')
            {
                room_num -= 1;
                w.WriteData(sock, &room_num, sizeof(room_num));
                flag = 1;
            }
            else if (room_num == '3')
            {
                w.WriteData(sock, &room_num, sizeof(room_num));
                exit(0);
            }
            else if (room_num == 'y' || room_num == 'Y')
            {
                char res = '0';
                Recv<int, char> rc;
                w.WriteData(sock, &room_num, sizeof(room_num));
                if (rc.RecvData(sock, &res, sizeof(res)) == 1)
                {
                    exit(1);
                }
                if (res == '1')
                {
                    flag = 1;
                }
            }
            else if (room_num == 'N' || room_num == 'n')
            {
                w.WriteData(sock, &room_num, sizeof(room_num));
            }
        }
        else if (flag == 1)
        {
            rewind(stdin);
            cin.getline(message, sizeof(message));

            if (message[0] == 'q' || message[0] == 'Q')
            {
                if (message[1] == '\0')
                    exit(0);
            }
            else if (strcmp(message, "/exit") == 0)
            {
                flag = 0;
            }
            w.WriteData(sock, message, sizeof(message));
        }
    }
}