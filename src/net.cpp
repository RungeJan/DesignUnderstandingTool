#include "net.h"

#include <string>

using namespace std;

net_t zeroNet("Logical_0", 0, 0, false);

net_t oneNet("Logical_1", 1, 1, false);

port_t zeroPort(DirectionInput,0, zeroNet);

port_t onePort(DirectionInput,1, oneNet);

net_t dontCareNet("x", -1, -1, false);

port_t dontCarePort(DirectionInOut,-1, dontCareNet);

json net_t::storeInJson(){
    json description;
    description["name"] = this->name;
    description["bitId"] = this->bitId;
    description["hide_name"] = this->hideName;
    description["attributes"] = json(this->attributes);

    return description;
}

json port_t::storeInJson(){
    json description;
    string tempId = this->net.netRefId < 10 ? "00" + to_string(this->net.netRefId) : this->net.netRefId < 100 ? "0" + to_string(this->net.netRefId) : to_string(this->net.netRefId);
    description["direction"] = this->direction == DirectionInput ? "Input" : (this->direction == DirectionOutput ? "Output" : "InOut");
    description["net"] = "net_" + tempId;

    return description;
}