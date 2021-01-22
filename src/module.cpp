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
        vector<port_t>::iterator it = this->ports.begin();
        while (it != this->ports.end())
        {
            string tempId = it->portRefId < 10 ? "00" + to_string(it->portRefId) : it->portRefId < 100 ? "0" + to_string(it->portRefId) : to_string(it->portRefId);
            string tempName = "port_" + tempId;
            description["ports"][tempName] =  it->storeInJson();
            it++;
        }
    }

    if (this->netsInternal.empty() == false)
    {
        int i = 1;
        vector<net_t>::iterator it = this->netsInternal.begin();
        while (it != this->netsInternal.end())
        {
            string tempId = it->netRefId < 10 ? "00" + to_string(it->netRefId) : it->netRefId < 100 ? "0" + to_string(it->netRefId) : to_string(it->netRefId);
            string tempName = "net_" + tempId;
            description["nets"][tempName] =  it->storeInJson();
            it++;
            i++;
        }
    }

    if(this->usedModules.empty() == false){
        int i = 1;
        vector<module_t>::iterator it = this->usedModules.begin();
        while(it != this->usedModules.end()){
            string tempId = i < 10 ? "0" + to_string(i) : to_string(i) ;
            string tempName = "module_" + tempId;
            description["modules"][tempName] = it->storeInJson();
            it++;
            i++;
        }
    }

    if(this->cells.empty() == false){
        int i = 1;
        vector<cell_t *>::iterator it = this->cells.begin();
        while(it != this->cells.end()){
            string tempId = i < 10 ? "00" + to_string(i) : i < 100 ? "0" + to_string(i) : to_string(i);
            string tempName = "cell_" + tempId;
            description["cells"][tempName] = (*it)->storeInJson();
            it++;
            i++;
        }
    }

    return description;
}