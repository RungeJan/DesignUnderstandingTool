/**
 * @file functionalities.h
 * @author Jan Runge
 * 
 * @brief This file will provide functions to add functionalities to the tool
 */

#ifndef FUNCTIONALITIES_H_
#define FUNCTIONALITIES_H_

#include "module.h"

/**
 * @brief This function will find all the nets in the module that have an impact on the control flow of the passed module
 * 
 * @param inModule The module of which the nets are checked and marked
 */
void markCFInfluencingNets(module_t &inModule);

void createCFGraph(module_t &inModule);

#endif // FUNCTIONALITIES_H_