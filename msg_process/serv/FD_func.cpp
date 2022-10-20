#include "FD_func.h"

void FD_func::Copy_discriptors()
{
    cpy_discriptors = discriptors;
}

void FD_func::FD_ZERO_FUNC()
{
    FD_ZERO(&discriptors);
}

void FD_func::FD_SET_FUNC(int sock)
{
    FD_SET(sock, &discriptors);
}

void FD_func::FD_CLEAR_FUNC(int target)
{
    FD_CLR(target,&discriptors);
}

int FD_func::FD_ISSET_FUNC(int target)
{
    return  FD_ISSET(target,&cpy_discriptors);
}