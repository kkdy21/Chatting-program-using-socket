#ifndef SELECT_H
#define SELECT_H

#include <sys/select.h>
#include "FD_func.h"
#include "time.h"

class Select : public FD_func , public Time
{
    public:

    int Select_func(int *fd_max);

};

#endif