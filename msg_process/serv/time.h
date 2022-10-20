#ifndef TIME_H
#define TIME_H

#include <sys/time.h>

class Time
{
protected: 
    struct timeval time;

public:
    void Timeset();
};

#endif