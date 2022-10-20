#ifndef __RECV_
#define __RECV_
#include <iostream>
#include <unistd.h>
#include <vector>
using namespace std;

template <typename T, typename T2>

class Recv
{
public:
    Recv() {}
    ~Recv() {}
    int RecvData(T sock, T2 *input, int size);
};

template <typename T, typename T2>
int Recv<T, T2>::RecvData(T sock, T2 *input, int size)
{

    vector<T2> buf(size);

    copy(&input[0], &input[0] + size, &buf[0]);

    if (read(sock, buf.data(), buf.size() + 1) == 0)
    {
        return 1;
    }
    copy(&buf[0], &buf[0] + size, &input[0]);
    return 0;
}

#endif
