/**
 * @file design.h
 * @author Jan Runge
 * 
 * @brief This file contains a struct representing a verilog design
 * 
 */

#include <vector>

#include "module.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

struct design_t{

    /**
    * @brief This function will parse the struct instance into a json object
    * 
    * @return A json object holding the information about this instance
    */
    json storeInJson();
    //void createFromJson(json &inJ){};

    std::string name;                   //<! The name of this design
    std::vector<module_t> modules;      //<! all the modules that are within this file
}; //<! This structure holds all the information of a verilog design