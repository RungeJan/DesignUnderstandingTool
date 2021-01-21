/**
 * @file processing.h 
 * @author Jan Runge
 * 
 * @brief This file provides functions for processing json descriptions into the software representation
 */
#ifndef PROCESS_H_
#define PROCESS_H_

#include <vector>
#include <string>

#include "module.h"
#include "net.h"
#include "cell.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

/**
 * @brief This function will find all the nets that are given in a Yosys intermediate representation
 * @note This function will fill the netsInternal vector of the passed module
 * 
 * @param inJson A reference to the json description of netnames of a module <json_name>["modules"][<module_name>]["netnames"]
 * @param inModule A pointer to the module to which the nets should be added
 */
void processYosysNetsIntoVector(json &inJson, module_t *inModule);

/**
 * @brief Passes all the attributes given in a Yosys intermediate representation into a vector of pairs
 * 
 * @param inJson A reference to a json description of attributes <json_name>[*]["attributes"]
 * @param inOutAtts A <std::vector> of <std::pair><<std::string>,<std::string>> that will be filled with the attributes
 */
void processYosysAttributesIntoVector(json &inJson, std::vector<std::pair<std::string, std::string>> &inOutAtts);

/**
 * @brief This function will find all the cells that are given in a Yosys intermediate representation and add them to a module
 * @note This function will fill the cell vector of the passed module_t object
 * 
 * @param inJson A reference to a json object holding the cells of the Yosys IR <json_name>["modules"][<module_name>]["cells"]
 * @param inModule A pointer to the module in that the cells should be found and to which the cells will be added
 */
void processYosysCellsIntoVector(json &inJson,module_t *inModulew);

/**
 * @brief This function will find all ports given in a Yosys Intermediate Representation and add them to a bodule
 * 
 * @note Typically should be called after processNetsIntoVector, not before since nets might be unknown then
 * 
 * @param inJson A reference to a json object holding the port descriptions of the Yosys IR, <json_name>["modules"][<module_name>]["ports"]
 * @param inModule A pointer to the module i that the ports should be added. Needs to contain the nets these ports are referring to
 */
void processYosysPortsIntoVector(json &inJson, module_t *inModule);



#endif // PROCESS_H_