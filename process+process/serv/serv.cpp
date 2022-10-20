#include <iostream>
using namespace std;
#include "servermain.h"

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        cout << " Usage : " << argv[0] << " <port>\n";
        exit(1);
    }

    ServMain serv(atoi(argv[1]));

    serv.Main();

    return 0;
}