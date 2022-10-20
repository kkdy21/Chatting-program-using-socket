#include <iostream>
#include "clntsock.h"

using namespace std;

void ClntSock::Connect()
{
    if(connect(my_sock,(struct sockaddr *)&addr, sizeof(addr)) ==-1)
    {
        cout << "connect error" << endl;
        exit(1);
    }
}