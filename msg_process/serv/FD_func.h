#ifndef FD_FUNC_H
#define FD_FUNC_H

#include <sys/select.h>

class FD_func 
{
    protected:
    fd_set discriptors, cpy_discriptors;

    public:
    void Copy_discriptors();
    void FD_ZERO_FUNC();
    void FD_SET_FUNC(int sock);
    void FD_CLEAR_FUNC(int target);
    int FD_ISSET_FUNC(int target);
   
};

#endif