#include "sock.h"
#include "addr.h"

class ClntSock : public Sock, public Addr
{
public :
    void Connect();    
};