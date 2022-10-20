#ifndef __CLNTRECV_H_
#define __CLNTRECV_H_
#include <string>
#include <vector>
using namespace std;

class ClntRecv
{
protected:
    vector<string> messages;
    int range_min = 0, range_max = 10;

public:
    void clntRecv(int sock);
    void PrintMsg(string msg);
};

#endif