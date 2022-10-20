#include "clntmain.h"

int main(int argc, char *argv[])
{

    if(argc!=3)
    {
        std::cout<<"port, IP 주소 입력해주세요"<<std::endl;
        exit(1);
    }

    ClntMain clnt(atoi(argv[1]),argv[2]);

    clnt.Clntmain();

    return 0;
}