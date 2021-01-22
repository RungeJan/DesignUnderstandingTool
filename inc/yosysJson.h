/**
 * @file yosysJson.h
 * @author Jan Runge
 * 
 * @brief This file provides functions for creating new cells from their Yosys Json representation
 */

#ifndef YOSYS_JSON_H_
#define YOSYS_JSON_H_

#include <string>
#include "nlohmann/json.hpp"
#include "module.h"
#include "cell.h"

using json = nlohmann::json;

/**
 * @{
 * @brief This functions will create an cell struct from its Yosys Json representation
 * The kind of struct that will be created depends on the cell that is passed to the function
 * 
 * @param inJ The json object from which the cell should be extracted
 * @param inCellName The name for this cell
 * @param inModule The module this cell belongs to and in which the nets belonging to the cells ports are
 * @param outCell A pointer to a pointer of the cell that will be created within the function. 
 * @note The type of the outCell parameter will determine the type of the cell that is created
 */

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cell_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellDFlipFlop_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellDFlipFlopEnable_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellDFlipFlopSetReset_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellFlipFlop_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellAdff_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellAlu_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellConcat_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellDLatch_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellDLatchSR_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellEquiv_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellFa_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellFsm_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellInitState_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellLcu_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellLut_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellMacc_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellMem_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellMemInit_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellMemRd_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellMemWr_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellMux_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellPMux_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellSlice_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellSop_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellSpecify2_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellSpecify3_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellTriBuf_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellSr_t **outCell);
/**
 * @}
 */

/**
 * @{
 * @brief This functions will create an cell struct from its Yosys Json representation
 * The kind of struct that will be created depends on the cell that is passed to the function
 * 
 * @param inJ The json object from which the cell should be extracted
 * @param inCellName The name for this cell
 * @param inCellType The type of this cell. Needed if multiple types have the same base structure
 * @param inModule The module this cell belongs to and in which the nets belonging to the cells ports are
 * @param outCell A pointer to a pointer of the cell that will be created within the function. 
 * @note The type of the outCell parameter will determine the type of the cell that is created
 */
void cellFromYosysJson(json &inJ, const std::string inCellName, const cellType_t inCellType, module_t *inModule, cellArithmetic_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, const cellType_t inCellType, module_t *inModule, cellConstAssign_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, const cellType_t inCellType, module_t *inModule, cellAEn_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, const cellType_t inCellType, module_t *inModule, cellAY_t **outCell);
/**
 * @}
 */

#endif // YOSYS_JSON_H_