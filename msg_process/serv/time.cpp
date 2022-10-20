#include "time.h"

void Time::Timeset()
{
    time.tv_sec = 5;
    time.tv_usec = 5000;
}
