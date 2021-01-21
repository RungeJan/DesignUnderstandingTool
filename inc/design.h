/**
 * @file design.h
 * @author Jan Runge
 * 
 * @brief This file contains a struct representing a verilog design
 * 
 */

#include <vector>

#include "module.h"

struct design_t{
    std::vector<module_t> modules;      //<! all the modules that are within this file
}; //<! This structure holds all the information of a verilog design