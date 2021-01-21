/**
 * @file net.h
 * @author Jan Runge
 * 
 * @brief This file will provide a structure for representing verilog nets
 */


#ifndef NET_H_
#define NET_H_
#include <string>
#include <vector>


enum direction_t {DirectionInput, DirectionOutput, DirectionInOut};

struct net_t{

    net_t(std::string newName, const unsigned int newId, const bool inHideName):name(newName), bitId(newId), hideName(inHideName){};

    std::string name;           //<! The name under which this net can be found in code
    const unsigned int bitId;   //<! A unique identifier for this net
    const bool hideName;        //<! true, if the name should be hidden, false otherwise
    std::vector<std::pair<std::string, std::string>> attributes;    // A list of attributes for the net
};

struct port_t{

    port_t(direction_t newDirection, net_t & newNet) : direction(newDirection), net(newNet){};

    net_t &net;             //<! The net this port belongs to
    direction_t direction;  //<! The direction of this port
};

extern net_t zeroNet;   //<! A net represetning an connection which is always logical 0

extern net_t oneNet;    //<! A net representing a connection which is always logical 1

extern net_t dontCareNet;   //<! A net representing a connection which is always don't care

extern port_t zeroPort;     //<! A port belonging to the zeroNet

extern port_t onePort;      //<! A port belonging to the oneNet

extern port_t dontCarePort; //<! A port belonging to the dontCareNet


#endif // NET_H_