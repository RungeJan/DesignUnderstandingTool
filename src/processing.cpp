#include <string>
#include <vector>
#include <iostream>

#include "processing.h"
#include "module.h"
#include "net.h"
#include "cell.h"

using namespace std;

port_t *createPort(json inJ, direction_t inDir, module_t *inModule, int inPos = 0)
{
    int netId;
    bool isString = ((inJ["bits"].at(inPos).type()) == json::value_t::string);
    port_t *outPort = NULL;
    try
    {
        if (isString)
        {
            string temp = inJ["bits"].at(inPos);
            if (temp != "x")
            {
                netId = stoi(temp);
                outPort = new port_t(DirectionInput, inModule->getNetWithId(netId));
            }
            else
            {
                outPort = &dontCarePort;
            }
        }
        else
        {
            netId = inJ["bits"].at(inPos);
            outPort = new port_t(DirectionInput, inModule->getNetWithId(netId));
        }
    }
    catch (const elementDoesNotExistException &e)
    {
        cerr << e.what() << endl;
    }
    return outPort;
}

inline void removeSignInString(char inSign, string &inString)
{
    int pos;
    while ((pos = inString.find(inSign)) != -1)
    {
        inString.erase(pos, 1);
    };
}

void processAttributesIntoVector(json &inJson, vector<pair<string, string>> &inOutAtts)
{
    string inString = inJson.dump();
    removeSignInString('\"', inString);
    removeSignInString('{', inString);
    removeSignInString('}', inString);
    int pos = 0;
    while ((pos = inString.find(",")) != -1)
    {
        int delimPos = inString.find(":");
        string key = inString.substr(0, delimPos);
        string value = inString.substr(delimPos + 1, pos - delimPos - 1);
        inOutAtts.push_back(make_pair(key, value));

        inString = inString.substr(pos + 1);
    }
    int delimPos = inString.find(":");
    string key = inString.substr(0, delimPos);
    string value = inString.substr(delimPos + 1, pos - delimPos - 1);
    inOutAtts.push_back(make_pair(key, value));
}

void processCellsIntoVector(json &inJson, module_t *inModule)
{
    int jSize = inJson.size();
    for (int i = 0; i < jSize; i++)
    {
        string name = inJson.dump();
        name = name.substr(2, name.find("\":") - 2);
        cell_t *newCell = NULL;
        cellFromYosysJson(inJson[name], name, inModule, &newCell);
        inJson.erase(name);
        inModule->cells.push_back(newCell);
    }
}

void processNetsIntoVector(json &inJson, module_t *inModule)
{
    net_t *newNet;
    int jSize = inJson.size();
    json::iterator it = inJson.begin();
    while (it != inJson.end())
    {
        string netName = inJson.dump();
        netName = netName.substr(2, netName.find("\":") - 2);
        int numberOfBits = (*it)["bits"].size();
        if (1 == numberOfBits)
        {
            newNet = new net_t(netName, (*it)["bits"].at(0), (*it)["hide_name"] == 1 ? true : false);
            if ((*it)["attributes"].size() > 0)
            {
                processAttributesIntoVector((*it)["attributes"], newNet->attributes);
            }
            inModule->netsInternal.push_back(*newNet);
        }
        else
        {
            for (int j = 0; j < numberOfBits; j++)
            {
                newNet = new net_t(netName + "[" + to_string(j) + "]", (*it)["bits"].at(j), (*it)["hide_name"] == 1 ? true : false);
                if ((*it)["attributes"].size() > 0)
                {
                    processAttributesIntoVector((*it)["attributes"], newNet->attributes);
                }
                inModule->netsInternal.push_back(*newNet);
            }
        }
        inJson.erase(it);
        it = inJson.begin();
    }
}

void processPortsIntoVector(json &inJson, module_t *inModule)
{
    port_t *newPort;
    json::iterator it = inJson.begin();
    while (it != inJson.end())
    {
        string portName = inJson.dump();
        portName = portName.substr(2, portName.find("\":") - 2);
        int numberOfBits = (*it)["bits"].size();

        for (int j = 0; j < numberOfBits; j++)
        {
            newPort = createPort((*it), (*it)["direction"] == "output" ? DirectionOutput : DirectionInput, inModule, j);
            inModule->ports.push_back(*newPort);
        }
        inJson.erase(it);
        it = inJson.begin();
    }
}
