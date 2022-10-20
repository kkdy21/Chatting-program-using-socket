#include "useroverlap.h"

int UserOverlap::Overlap(string *names, char *name, int cnt)
{
    for (int i = 0; i < cnt - 1; i++)
    {
        if (names[i].find(name) == 0)   //0이면 중복x
            return i + 1;
    }

    return 0;
}