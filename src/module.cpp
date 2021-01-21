#include "module.h"

using namespace std;

bool module_t::containsNetWithId(unsigned int findBitId)
{
    for (vector<net_t>::iterator it = netsInternal.begin(); it != netsInternal.end(); it++)
    {
        if (it->bitId == findBitId)
        {
            return true;
        }
    }
    return false;
}

net_t &module_t::getNetWithId(unsigned int getBitId)
{
    if (getBitId == 0)
    {
        return zeroNet;
    }
    if (getBitId == 1)
    {
        return oneNet;
    }
    for (vector<net_t>::iterator it = netsInternal.begin(); it != netsInternal.end(); it++)
    {
        if (it->bitId == getBitId)
        {
            return *it;
        }
    }
    elementDoesNotExistException *e = new elementDoesNotExistException("net", getBitId);
    throw *e;
}