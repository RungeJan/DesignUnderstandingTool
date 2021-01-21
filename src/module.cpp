#include "module.h"
#include "localExceptions.h"

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

json module_t::storeInJson()
{
    json description;
    description["name"] = this->name;
    description["attributes"] = json(this->attributes);

    if (this->ports.empty() == false)
    {
        int i = 1;
        vector<port_t>::iterator it = this->ports.begin();
        while (it != this->ports.end())
        {
            string tempName = "port_" + to_string(i);
            description["ports"][tempName] =  it->storeInJson();
            it++;
            i++;
        }
    }

    if (this->netsInternal.empty() == false)
    {
        int i = 1;
        vector<net_t>::iterator it = this->netsInternal.begin();
        while (it != this->netsInternal.end())
        {
            string tempName = "net_" + to_string(i);
            description["nets"][tempName] =  it->storeInJson();
            it++;
            i++;
        }
    }

    if(this->usedModules.empty() == false){
        int i = 1;
        vector<module_t>::iterator it = this->usedModules.begin();
        while(it != this->usedModules.end()){
            string tempName = "module_" + to_string(i);
            description["modules"][tempName] = it->storeInJson();
            it++;
            i++;
        }
    }

    return description;
}