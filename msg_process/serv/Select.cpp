#include "Select.h"
#include <iostream>
using namespace std;

int Select::Select_func(int *fd_max)
{
    Copy_discriptors();
    Timeset();

    return select(*fd_max + 1, &cpy_discriptors, 0, 0, &time);
}
