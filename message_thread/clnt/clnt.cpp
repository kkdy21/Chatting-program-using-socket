#include <iostream>
using namespace std;
#include "clntmain.h"

int main(int argc, char *argv[])
{
    if(argc !=3)
    {
        cout << " Usage : " << argv[0] << " <port> <IP>\n";
    }

    ClntMain cm(atoi(argv[1]),argv[2]);
    
    cm.Main();
}