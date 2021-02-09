#include "net.h"

#include <string>
#include <iostream>

using namespace std;

net_t zeroNet("Logical_0", 0, 0, false);

net_t oneNet("Logical_1", 1, 1, false);

port_t zeroPort(DirectionInput, 0, 0);

port_t onePort(DirectionInput, 1, 1);

net_t dontCareNet("x", -1, -1, false);

port_t dontCarePort(DirectionInOut, -1, -1);

json net_t::storeInJson()
{
    json description;
    description["name"] = this->name;
    description["bitId"] = this->bitId;
    description["hide_name"] = this->hideName;
    description["attributes"] = json(this->attributes);
    description["cf_influencing"] = this->hasCFInfluence;

    return description;
}

net_t *net_t::createFromJson(json &inJ, const unsigned int inRefId)
{
    net_t *newNet = new net_t(inJ["name"], inJ["bitId"], inRefId, inJ["hide_name"]);
    if (inJ.contains("cf_influence")) // This is not always possible, depending on the version which that the json representation was created
    {
        newNet->hasCFInfluence = inJ["cf_influencing"];
    }
    json::iterator it = inJ["attributes"].begin();
    while (it != inJ["attributes"].end())
    {
        newNet->attributes.push_back(make_pair(string(it->at(0)), string(it->at(1))));
        it++;
    }
    return newNet;
}

json port_t::storeInJson()
{
    json description;
    string tempId = this->netId < 10 ? "00" + to_string(this->netId) : this->netId < 100 ? "0" + to_string(this->netId) : to_string(this->netId);
    description["direction"] = this->direction == DirectionInput ? "Input" : (this->direction == DirectionOutput ? "Output" : "InOut");
    description["net"] = "net_" + tempId;

    return description;
}
