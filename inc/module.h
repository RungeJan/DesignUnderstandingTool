/**
 * @file module.h
 * @author Jan Runge
 * 
 * @brief This file contains a structure representing verilog modules
 */

#ifndef MODULE_H_
#define MODULE_H_

#include <string>
#include <vector>

#include "net.h"
#include "cell.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

struct module_t
{
    module_t() : numberOfNets(2), numberOfPorts(2), numberOfCells(0){};

    // External known information
    /**
     * @brief This function will check if a net with the given id is already represented in the module 
     * 
     * @param findBitId The id of the net of which the existence should be checked
     * 
     * @return true, if the belonging net is part of the module, false otherwise
     */
    bool containsNetWithId(unsigned int findBitId);

    /**
     * @brief This function will get a net with the given id from the module
     * 
     * @param getBitId The id of the net that should be returned
     * 
     * @return A reference to a net inside the module, which has the id that was passed to the function
     * @throw elementDoesNotExistException if there is no net with the passed id
     */
    net_t &getNetWithId(unsigned int getBitId);

    /**
    * @brief This function will parse the struct instance into a json object
    * 
    * @return A json object holding the information about this instance
    */
    json storeInJson();

    std::string name;                                            //!< The name of the module
    std::vector<port_t> ports;                                   //!< The input and output ports to the module, ports are mapped to the internal nets
    std::vector<std::pair<std::string, std::string>> attributes; //!< All the attributes given to the module
    std::vector<cell_t *> cells;                                 //!< Pointers to all the cells that where introduced by Yosys (pointers since there are multiple cell types derived from cell_t)

    // Internal known information
    std::vector<net_t> netsInternal;      //!< All the nets that are used inside the module
    std::vector<module_t> usedModules;    //!< All the modules that are used in this module

    unsigned int numberOfNets;          //!< A counter for the nets of this module
    unsigned int numberOfPorts;         //!< A counter for the ports of this module
    unsigned int numberOfCells;         //!< A counter for the cells of this module
};

#endif //MODULE_H_