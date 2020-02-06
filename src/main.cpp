#include "socketcomm.hpp"



int main(int argc, char *argv[])
{
    cSocketComm* pSocketComm = new cSocketComm();

    if(pSocketComm->initConnection())
    {
        pSocketComm->readSocket();
    }

    

    return 0;
}