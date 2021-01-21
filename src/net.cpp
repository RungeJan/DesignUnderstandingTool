#include "net.h"


net_t zeroNet("Logical_0", 0, false);

net_t oneNet("Logical_1", 1, false);

port_t zeroPort(DirectionInput, zeroNet);

port_t onePort(DirectionInput, oneNet);

net_t dontCareNet("x", -1, false);

port_t dontCarePort(DirectionInOut, dontCareNet);

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
    description["direction"] = this->direction == DirectionInput ? "Input" : (this->direction == DirectionOutput ? "Output" : "InOut");
    description["net"] = this->net.storeInJson();

    return description;
}