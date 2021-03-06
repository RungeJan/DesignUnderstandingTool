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

enum direction_t
{
    DirectionInput,
    DirectionOutput,
    DirectionInOut
};

enum cfInfluence_t
{
    CFInfluenceNone,        //!< A net has no influence on the CF
    CFInfluencePrimary,     //!< A net has direct impact on the CF, typically a multiplexers S connection
    CFInfluenceSecondary    //!< A net has indirect impact on the CF, e.g. it is input to an arithmetic operation of which the output is of secondary or primary influence
}; //<! This enum holds different levels of control flow (CF) influence

/**
 * @brief This struct represents a net in the design
 */
struct net_t
{

    net_t(std::string newName, const unsigned int newId, const unsigned int newRefId, const bool inHideName) : name(newName), bitId(newId), netRefId(newRefId), hideName(inHideName),
                                                                                                               hasCFInfluence(CFInfluenceNone){};

    /**
     * @brief This function will parse the struct instance into a json object
     * 
     * @return A json object holding the information about this instance
     */
    json storeInJson();

    static net_t *createFromJson(json &inJ, const unsigned int inRefId);

    std::string name;                                            //!< The name under which this net can be found in code
    const unsigned int bitId;                                    //!< A unique identifier for this net, given by Yosys, global
    const unsigned int netRefId;                                 //!< A unique identifier for this net, given by this tool, local within a module
    const bool hideName;                                         //!< true, if the name should be hidden, false otherwise
    cfInfluence_t hasCFInfluence;                                //!< Will hold the control flow influence level of this net
    std::vector<std::pair<std::string, std::string>> attributes; //!< A list of attributes for the net
};

struct port_t
{

    port_t(direction_t newDirection, unsigned int newRefId, unsigned int newNet) : direction(newDirection), netId(newNet), portRefId(newRefId){};

    /**
     * @brief This function will parse the struct instance into a json object
     * 
     * @return A json object holding the information about this instance
     */
    json storeInJson();

    const unsigned int netId; //!< The Id of the net this port belongs to
    direction_t direction;    //!< The direction of this port
    unsigned int portRefId;   //!< A unique identifier for this port, given by this tool, local within modules, cells, etc.
};

extern net_t zeroNet; //!< A net represetning an connection which is always logical 0

extern net_t oneNet; //!< A net representing a connection which is always logical 1

extern net_t dontCareNet; //!< A net representing a connection which is always don't care

extern port_t zeroPort; //!< A port belonging to the zeroNet

extern port_t onePort; //!< A port belonging to the oneNet

extern port_t dontCarePort; //!< A port belonging to the dontCareNet

#endif // NET_H_