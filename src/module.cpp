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
    else if (getBitId == 1)
    {
        return oneNet;
    }
    else if(getBitId == -1){
        return dontCareNet;
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
            description["ports"][tempName] = it->storeInJson();
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
            description["nets"][tempName] = it->storeInJson();
            it++;
            i++;
        }
    }

    if (this->usedModules.empty() == false)
    {
        int i = 1;
        vector<module_t>::iterator it = this->usedModules.begin();
        while (it != this->usedModules.end())
        {
            string tempId = i < 10 ? "0" + to_string(i) : to_string(i);
            string tempName = "module_" + tempId;
            description["modules"][tempName] = it->storeInJson();
            it++;
            i++;
        }
    }

    if (this->cells.empty() == false)
    {
        int i = 1;
        vector<cell_t *>::iterator it = this->cells.begin();
        while (it != this->cells.end())
        {
            string tempId = i < 10 ? "00" + to_string(i) : i < 100 ? "0" + to_string(i) : to_string(i);
            string tempName = "cell_" + tempId;
            description["cells"][tempName] = (*it)->storeInJson();
            it++;
            i++;
        }
    }

    return description;
}

module_t *module_t::createFromJson(json &inJ)
{
    module_t *newModule = new module_t(inJ["name"]);
    if (inJ.contains("nets"))
    {
        json::iterator it = inJ["nets"].begin();
        while (it != inJ["nets"].end())
        {
            net_t *newNet = net_t::createFromJson(*it, newModule->numberOfNets++);
            newModule->netsInternal.push_back(*newNet);
            it++;
        }
    }
    if (inJ.contains("ports"))
    {
        json::iterator it = inJ["ports"].begin();
        while (it != inJ["ports"].end())
        {
            string netName = (*it)["net"];
            direction_t dir = (*it)["direction"] == "Output" ? DirectionOutput : (*it)["direction"] == "Input" ? DirectionInput : DirectionInOut;
            port_t *newPort = new port_t(dir, newModule->numberOfPorts++, inJ["nets"][netName]["bitId"]);
            newModule->ports.push_back(*newPort);
            it++;
        }
    }
    if (inJ.contains("modules"))
    {
        json::iterator it = inJ["modules"].begin();
        while (it != inJ["modules"].end())
        {
            module_t *newInternalModule = module_t::createFromJson(*it);
            newModule->usedModules.push_back(*newInternalModule);
            it++;
        }
    }

    if (inJ.contains("cells"))
    {
        json::iterator it = inJ["cells"].begin();
        while (it != inJ["cells"].end())
        {
            cell_t *newCell = cell_t::createFromJson(*it, inJ["nets"], *newModule);
            if (NULL != newCell)
            {
                newModule->cells.push_back(newCell);
            }
            it++;
        }
    }
    if (inJ.contains("attributes"))
    {
        json::iterator it = inJ["attributes"].begin();
        while (it != inJ["attributes"].end())
        {
            newModule->attributes.push_back(make_pair(string(it->at(0)), string(it->at(1))));
            it++;
        }
    }
    return newModule;
}