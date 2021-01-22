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

#include "nlohmann/json.hpp"

using json = nlohmann::json;

enum direction_t {DirectionInput, DirectionOutput, DirectionInOut};

/**
 * @brief This struct represents a net in the design
 */
struct net_t{

    net_t(std::string newName, const unsigned int newId, const unsigned int newRefId, const bool inHideName):name(newName), bitId(newId), netRefId(newRefId), hideName(inHideName){};

    /**
     * @brief This function will parse the struct instance into a json object
     * 
     * @return A json object holding the information about this instance
     */
    json storeInJson();       

    std::string name;               //!< The name under which this net can be found in code
    const unsigned int bitId;       //!< A unique identifier for this net, given by Yosys, global
    const unsigned int netRefId;    //!< A unique identifier for this net, given by this tool, local within a module
    const bool hideName;            //!< true, if the name should be hidden, false otherwise
    std::vector<std::pair<std::string, std::string>> attributes;    //!< A list of attributes for the net
};

struct port_t{

    port_t(direction_t newDirection, unsigned int newRefId, net_t & newNet) : direction(newDirection), net(newNet), portRefId(newRefId){};

    /**
     * @brief This function will parse the struct instance into a json object
     * 
     * @return A json object holding the information about this instance
     */
    json storeInJson();

    net_t &net;             //!< The net this port belongs to
    direction_t direction;  //!< The direction of this port
    unsigned int portRefId; //!< A unique identifier for this port, given by this tool, local within modules, cells, etc.
};

extern net_t zeroNet;   //!< A net represetning an connection which is always logical 0

extern net_t oneNet;    //!< A net representing a connection which is always logical 1

extern net_t dontCareNet;   //!< A net representing a connection which is always don't care

extern port_t zeroPort;     //!< A port belonging to the zeroNet

extern port_t onePort;      //!< A port belonging to the oneNet

extern port_t dontCarePort; //!< A port belonging to the dontCareNet


#endif // NET_H_