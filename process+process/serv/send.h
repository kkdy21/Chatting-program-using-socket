#ifndef __SEND_H_
#define __SEND_H_
#include <iostream>
#include <unistd.h>
#include <vector>
using namespace std;

template <typename T, typename T2>

class Write
{
public:
    Write() {}
    ~Write() {}
    int WriteData(T sock, T2 *input, int size);
};

template <typename T, typename T2>
int Write<T, T2>::WriteData(T sock, T2 *input, int size)
{

    vector<T2> buf(size);

    copy(&input[0], &input[0] + size, &buf[0]);

    write(sock, buf.data(), buf.size() + 1);

    return 0;
}

#endif