#include "net.h"

net_t zeroNet("Logical_0", 0, false);

net_t oneNet("Logical_1", 1, false);

port_t zeroPort(DirectionInput, zeroNet);

port_t onePort(DirectionInput, oneNet);

net_t dontCareNet("x", -1, false);

port_t dontCarePort(DirectionInOut, dontCareNet);