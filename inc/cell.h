/**
 * @file cell.h
 * @author Jan Runge
 * 
 * @brief This file provides representations for all the cells that can be part of the Yosys Intermediate Representation
 */

#ifndef CELL_H_
#define CELL_H_
#include <string>
#include <vector>
#include "net.h"
#include <iostream>
#include "nlohmann/json.hpp"

struct module_t;

using json = nlohmann::json;



/**
 * @brief This Enum holds representations for the different cell types
 */
enum cellType_t
{
    TypeAdd,
    TypeAdff,
    TypeAllConst,
    TypeAllSeq,
    TypeAlu,
    TypeAnd,
    TypeAnyConst,
    TypeAnySeq,
    TypeAssert,
    TypeAssume,
    TypeConcat,
    TypeCover,
    TypeDff,
    TypeDffe,
    TypeDffsr,
    TypeDiv,
    TypeDLatch,
    TypeDLatchSR,
    TypeEq,
    TypeEquiv,
    TypeEqx,
    TypeFa,
    TypeFair,
    TypeFf,
    TypeFsm,
    TypeGe,
    TypeGt,
    TypeInitState,
    TypeLcu,
    TypeLe,
    TypeLive,
    TypeLogicAnd,
    TypeLogicNot,
    TypeLogicOr,
    TypeLt,
    TypeLut,
    TypeMacc,
    TypeMem,
    TypeMemInit,
    TypeMemRd,
    TypeMemWr,
    TypeMod,
    TypeMul,
    TypeMux,
    TypeNe,
    TypeNeg,
    TypeNex,
    TypeNot,
    TypeOr,
    TypePMux,
    TypePos,
    TypePow,
    TypeReduceAnd,
    TypeReduceBool,
    TypeReduceOr,
    TypeReduceXnor,
    TypeReduceXor,
    TypeShift,
    TypeShiftX,
    TypeShl,
    TypeShr,
    TypeSlice,
    TypeSop,
    TypeSpecify2,
    TypeSpecify3,
    TypeSpecRule,
    TypeSr,
    TypeSshl,
    TypeSshr,
    TypeSub,
    TypeTriBuf,
    TypeXnor,
    TypeXor,
    TypeUnknown
};


/**
 * @brief This struct serves as a base struct for all further cell implementations
 */
struct cell_t
{
    cell_t(std::string newName, bool hide, cellType_t newType) : name(newName), hideName(hide), type(newType){};
    const std::string name; //<! The name of this cell
    const bool hideName;    //<! true, if this cells name should be hidden, false otherwise
    const cellType_t type;  //<! the exact type of this cell
    std::vector<std::pair<std::string, std::string>> attributes; //<! All the attributes given to the cell
};
/**
 * @brief This struct servers as a representation for all cells of arithmetic type 
 * Belonging Types:
 * TypeAdd, TypeAnd, TypeDiv, TypeEq, TypeEqx, TypeGe, TypeGt, TypeLe, TypeLogicAnd, TypeLogicOr, TypeLt,
 * TypeMod, TypeMul, TypeNe, TypeNex, TypeOr, TypePow, TypeShift, TypeShiftX, TypeShl, TypeShr, TypeSshl,
 * TypeSshr, TypeSub, TypeXnor, TypeXor
 */
struct cellArithmetic_t : public cell_t{
    
    cellArithmetic_t(std::string newName, bool hide, cellType_t newType, const bool inASigned, const bool inBSigned, 
              const unsigned int inAWidth, const unsigned int inBWidth, const unsigned int inYWidth) : 
                aSigned(inASigned), bSigned(inBSigned), aWidth(inAWidth), bWidth(inBWidth), yWidth(inYWidth), 
                cell_t(newName, hide, newType){};
    const bool aSigned;         //<! true, if a is a signed value, false otherwise
    const bool bSigned;         //<! true, if b is a signed value, false otherwise
    const unsigned int aWidth;  //<! The width of input a
    const unsigned int bWidth;  //<! The width of input b
    const unsigned int yWidth;  //<! The width of output y
    std::vector<port_t> a;      //<! vector of ports which act as the a input.
    std::vector<port_t> b;      //<! vector of ports which act as the b input.
    std::vector<port_t> y;      //<! vector of ports which act as the y output.

    //virtual void cellToJson() = 0;
    //virtual void cellFromJson() = 0;

};

/**
 * @brief This struct represents D-FlipFlops
 * Belonging type:
 * TypeDff
 */
struct cellDFlipFlop_t : public cell_t{

    cellDFlipFlop_t(std::string newName, bool hide, const unsigned int newWidth, const unsigned int newClkPolarity, cellType_t newType, port_t newClk) :
        width(newWidth), clkPolarity(newClkPolarity), clk(newClk), cell_t(newName, hide, newType){};

    const unsigned int width;       //<! The width of D and Q
    const unsigned int clkPolarity; //<! The polarity of the CLK
    port_t clk;                     //<! The port working as the CLK
    std::vector<port_t> d;          //<! The input port D
    std::vector<port_t> q;          //<! The output port Q
};
/**
 * @brief This struct represents a D-FlipFlop with an extra enable pin
 * 
 */
struct cellDFlipFlopEnable_t : public cellDFlipFlop_t{
    cellDFlipFlopEnable_t(std::string newName, bool hide, const unsigned int newWidth, const unsigned int newClkPolarity, const unsigned int newEnPolarity, cellType_t newType,
                          port_t newClk, port_t newEn) : enPolarity(newEnPolarity), en(newEn), cellDFlipFlop_t(newName, hide, newWidth, newClkPolarity, newType, newClk) {};

    const unsigned int enPolarity;  //<! The polarity of the enable pin
    port_t en;                      //<! The port working as the enable pin
};

/**
 * @brief This struct represents an RS-FlipFlop
 * 
 * 
 */
struct cellDFlipFlopSetReset_t : cellDFlipFlop_t {

    cellDFlipFlopSetReset_t(std::string newName, bool hide, const unsigned int newWidth, const unsigned int newClkPolarity, const unsigned int newSetPolarity, 
                            unsigned int newClrPolarity, cellType_t newType, port_t newClk) : setPolarity(newSetPolarity), clrPolarity(newClrPolarity),  
                            cellDFlipFlop_t(newName, hide, newWidth, newClkPolarity, newType, newClk) {};

    const unsigned int setPolarity;     //<! The polarity of the set pin
    const unsigned int clrPolarity;     //<! The polarity of the clear pin
    std::vector<port_t> set;            //<! The port working as the set pin, has the width of the D-FlipFlop it is inherited from
    std::vector<port_t> clr;            //<! The port working as the clr pin, has the width of the D-FlipFlop it is inherited from
};

/**
 * @brief This struct represents a D-FlipFlip but with an global clock
 * @warning INCOMPLETE
 */
struct cellFlipFlop_t : public cell_t{ // TODO Add global clock ?

    cellFlipFlop_t(std::string newName, bool hide, unsigned int newWidth) : width(newWidth), cell_t(newName, hide, TypeFf){};

    const unsigned int width;   //<! The width of D and Q
    std::vector<port_t> d;      //<! The input pins D
    std::vector<port_t> q;      //<! The output pins Q
};

/**
 * @brief This struct represents a D-Latch
 */
struct cellDLatch_t : public cell_t{
    

    cellDLatch_t(std::string newName, bool hide,  cellType_t newType, const unsigned int newWidth, const unsigned int newEnPolarity, port_t newEn) : width(newWidth), enPolarity(newEnPolarity),
                 en(newEn), cell_t(newName, hide, newType){};

    const unsigned int width;       //<! The width of D and Q
    const unsigned int enPolarity;  //<! The polarity of the enable pin
    port_t en;                      //<! The enabel pin
    std::vector<port_t> d;          //<! The input pins D
    std::vector<port_t> q;          //<! The output pins Q
};

/**
 * @brief This struct represents a Set-Reset-D-Latch
 */
struct cellDLatchSR_t : public cellDLatch_t{

    cellDLatchSR_t(std::string newName, bool hide, cellType_t newType, const unsigned int newWidth, const unsigned int newEnPolarity,  port_t newEn,
                   unsigned int newSetPolarity, unsigned int newClrPolarity) : setPolarity(newSetPolarity), clrPolarity(newClrPolarity),
                   cellDLatch_t(newName, hide, newType, newWidth, newEnPolarity, newEn){};

    const unsigned int setPolarity;     //<! The polarity of the set pin
    const unsigned int clrPolarity;     //<! The polarity of the clear pin

    std::vector<port_t> set;            //<! The set port, has the width of the DLatch it is inherited from
    std::vector<port_t> clr;            //<! The clr port, has the width of the DLatch it is inherited from
};

/**
 * @brief This struct represents an A-Reset-D-FlipFlop
 * This flipflops output will be set to a certain value when a reset is triggered. otherwise it behaves like a D-Flip-Flop
 */

struct cellAdff_t : public cellDFlipFlop_t{
    cellAdff_t(std::string newName, bool hide, unsigned int newWidth, unsigned int newClkPolarity, unsigned int newArstPolarity, unsigned int newArstValue,
               port_t newClk, port_t newArst) : arstPolarity(newArstPolarity), arstValue(newArstValue), arst(newArst), 
               cellDFlipFlop_t(newName, hide, newWidth, newClkPolarity,TypeAdff, newClk) {};

    const unsigned int arstPolarity;    //<! The polarity of the A-Reset signal
    const unsigned int arstValue;       //<! The value to which Q will be resetted
    port_t arst;                        //<! The port for the A-Reset input       
};

struct cellConstAssign_t : public cell_t{
    cellConstAssign_t(std::string newName, bool hide, cellType_t newType, unsigned int newWidth) : cell_t(newName, hide, newType){};

    unsigned int width;
    std::vector<port_t> y;
};

struct cellAlu_t : public cellArithmetic_t{

    cellAlu_t(std::string newName, bool hide, const bool inASigned, const bool inBSigned, const unsigned int inAWidth,
               const unsigned int inBWidth, const unsigned int inYWidth, port_t newCi, port_t newBi) : ci(newCi), bi(newBi),
              cellArithmetic_t(newName, hide, TypeAlu, inASigned, inBSigned, inAWidth, inBWidth, inYWidth){};

    port_t ci;
    port_t bi;
    std::vector<port_t> x;
    std::vector<port_t> co;
};

struct cellAEn_t : public cell_t{

    cellAEn_t(std::string newName, bool hide, const cellType_t type, port_t newA, port_t newEn) : a(newA), en(newEn), cell_t(newName, hide, type){};

    port_t a;
    port_t en;
};

struct cellConcat_t : public cell_t{

    cellConcat_t(std::string newName, bool hide, unsigned int newAWidth, unsigned int newBWidth) : aWidth(newAWidth), bWidth(newBWidth), cell_t(newName, hide, TypeConcat){};

    const unsigned int aWidth;
    const unsigned int bWidth;

    std::vector<port_t> a;
    std::vector<port_t> b;
    std::vector<port_t> y;

};

struct cellEquiv_t : public cell_t{

    cellEquiv_t(std::string newName, bool hide, port_t newA, port_t newB, port_t newY) : a(newA), b(newB), y(newY), cell_t(newName, hide, TypeEquiv){};

    port_t a;
    port_t b;
    port_t y;
};

struct cellFa_t : public cell_t{

    cellFa_t(std::string newName, bool hide, unsigned int newWidth) : width(newWidth), cell_t(newName, hide, TypeFa){};

    const unsigned int width;

    std::vector<port_t> a;
    std::vector<port_t> b;
    std::vector<port_t> c;
    std::vector<port_t> x;
    std::vector<port_t> y;
};

struct cellFsm_t : public cell_t{

    cellFsm_t(std::string newName, bool hide, unsigned int newClkPolarity, unsigned int newArstPolarity, unsigned int newCtrlInWidth, unsigned int newCtrlOutWidth,
              unsigned int newStateBits, unsigned int newStateNum, unsigned int newStateNumLog2, unsigned int newStateRst, unsigned int newStateTable, unsigned int newTransNum,
              unsigned int newTransTable, port_t newClk, port_t newArst) : clkPolarity(newClkPolarity), arstPolarity(newArstPolarity), ctrlInWidth(newCtrlInWidth),
              ctrlOutWidth(newCtrlOutWidth), stateBits(newStateBits), stateNum(newStateNum), stateNumLog2(newStateNumLog2), stateRst(newStateRst), stateTable(newStateTable),
              transNum(newTransNum), transTable(newTransTable), clk(newClk), arst(newArst), cell_t(newName, hide, TypeFsm){};
    const unsigned int clkPolarity;
    const unsigned int arstPolarity;
    const unsigned int ctrlInWidth;
    const unsigned int ctrlOutWidth;
    const unsigned int stateBits;
    const unsigned int stateNum;
    const unsigned int stateNumLog2;
    const unsigned int stateRst;
    const unsigned int stateTable;
    const unsigned int transNum;
    const unsigned int transTable;

    port_t clk;
    port_t arst;

    std::vector<port_t> ctrlIn;
    std::vector<port_t> ctrlOut;
};

struct cellInitState_t : public cell_t{

    cellInitState_t(std::string newName, bool hide, port_t newY) : y(newY), cell_t(newName, hide, TypeInitState){};

    port_t y;
};

struct cellLcu_t : public cell_t{
    cellLcu_t(std::string newName, bool hide,unsigned int newWidth, port_t newCi) : width(newWidth), ci(newCi), cell_t(newName, hide, TypeLcu){};

    const unsigned int width;

    port_t ci;

    std::vector<port_t> p;
    std::vector<port_t> g;
    std::vector<port_t> co;
};

struct cellAY_t : public cell_t{

    cellAY_t(std::string newName, bool hide, cellType_t newType, unsigned int newASigned, unsigned int newAWidth, unsigned int newYWidth) : aSigned(newASigned),
             aWidth(newAWidth), yWidth(newYWidth), cell_t(newName, hide, newType){};
    
    const bool aSigned;
    const unsigned int aWidth;
    const unsigned int yWidth;

    std::vector<port_t> a;
    std::vector<port_t> y;
};

struct cellLut_t : public cell_t{
    
    cellLut_t(std::string newName, bool hide, unsigned int newWidth, unsigned int newLut, port_t newY) : width(newWidth), lut(newLut), y(newY), 
              cell_t(newName, hide, TypeLut){};
    const unsigned int width;
    const unsigned int lut;

    port_t y;

    std::vector<port_t> a;
};

struct cellMacc_t : public cell_t{
    cellMacc_t(std::string newName, bool hide, const unsigned int inAWidth, const unsigned int inBWidth, const unsigned int inYWidth, 
               const unsigned int inConfig, const unsigned int inConfigWidth) : aWidth(inAWidth), bWidth(inBWidth), yWidth(inYWidth),
               config(inConfig), configWidth(inConfigWidth), cell_t(newName, hide, TypeMacc){};
    const unsigned int aWidth;
    const unsigned int bWidth;
    const unsigned int yWidth;
    const unsigned int config;
    const unsigned int configWidth;

    std::vector<port_t> a;
    std::vector<port_t> b;
    std::vector<port_t> y;
};

struct cellMem_t : public cell_t{

    cellMem_t(std::string newName, bool hide, const unsigned int inMemId, const int inSize, const int inOffset, const int inABits,
              const int inWidth, const int inInit, const int inRdPorts, const unsigned int inRdClkEnable, const unsigned int inRdClkPolarity,
              const unsigned int inRdTransparent, const int inWrPorts, const unsigned int inWrClkEnable, const unsigned int inWrClkPolarity) :
              memId(inMemId), size(inSize), offset(inOffset), aBits(inABits), width(inWidth), init(inInit), rdPorts(inRdPorts), rdClkEnable(inRdClkEnable),
              rdClkPolarity(inRdClkPolarity), rdTransparent(inRdTransparent), wrPorts(inWrPorts), wrClkEnable(inWrClkEnable), wrClkPolarity(inWrClkPolarity),
              cell_t(newName, hide, TypeMem) {};

    const unsigned int memId;
    const int size;
    const int offset;
    const int aBits;
    const int width;
    const int init;
    const int rdPorts;
    const unsigned int rdClkEnable;
    const unsigned int rdClkPolarity;
    const unsigned int rdTransparent;
    const int wrPorts;
    const unsigned int wrClkEnable;
    const unsigned int wrClkPolarity;

    std::vector<port_t> rdClk;
    std::vector<port_t> rdEn;
    std::vector<port_t> rdAddr;
    std::vector<port_t> rdData;
    std::vector<port_t> wrClk;
    std::vector<port_t> wrEn;
    std::vector<port_t> wrAddr;
    std::vector<port_t> wrData;
};

struct cellMemInit_t : public cell_t{

    cellMemInit_t(std::string newName, bool hide, const unsigned int inMemId, const unsigned int inABits, const unsigned int inWidth,
                  const unsigned int inWords, const unsigned int inPriority) : memId(inMemId), aBits(inABits), width(inWidth), words(inWords),
                  priority(inPriority), cell_t(newName, hide, TypeMemInit){};

    const unsigned int memId;
    const unsigned int aBits;
    const unsigned int width;
    const unsigned int words;
    const unsigned int priority;

    std::vector<port_t> addr;
    std::vector<port_t> data;
};

struct cellMemRd_t : public cell_t{
    
    cellMemRd_t(std::string newName, bool hide, const unsigned int inMemId, const unsigned int inABits, const unsigned int inWidth,
                  const unsigned int inClkEnable, const unsigned int inClkPolarity, const unsigned int inTransparnt, port_t inClk, port_t inEn) : 
                  memId(inMemId), aBits(inABits), width(inWidth), clkEnable(inClkEnable), clkPolarity(inClkPolarity), transparent(inTransparnt), 
                  clk(inClk), en(inEn), cell_t(newName, hide, TypeMemInit){};

    const unsigned int memId;
    const unsigned int aBits;
    const unsigned int width;
    const unsigned int clkEnable;
    const unsigned int clkPolarity;
    const unsigned int transparent;

    port_t clk;
    port_t en;

    std::vector<port_t> addr;
    std::vector<port_t> data;
};

struct cellMemWr_t : public cell_t{
    
    cellMemWr_t(std::string newName, bool hide, const unsigned int inMemId, const unsigned int inABits, const unsigned int inWidth,
                  const unsigned int inClkEnable, const unsigned int inClkPolarity, const unsigned int inTransparnt, port_t inClk) : 
                  memId(inMemId), aBits(inABits), width(inWidth), clkEnable(inClkEnable), clkPolarity(inClkPolarity), transparent(inTransparnt), 
                  clk(inClk), cell_t(newName, hide, TypeMemInit){};

    const unsigned int memId;
    const unsigned int aBits;
    const unsigned int width;
    const unsigned int clkEnable;
    const unsigned int clkPolarity;
    const unsigned int transparent;

    port_t clk;
    
    std::vector<port_t> en;
    std::vector<port_t> addr;
    std::vector<port_t> data;
};

struct cellMux_t : public cell_t{

    cellMux_t(std::string newName, bool hide, const unsigned int inWidth, port_t inS) : width(inWidth), s(inS), cell_t(newName, hide, TypeMux){};

    const unsigned int width;
    port_t s;

    std::vector<port_t> a;
    std::vector<port_t> b;
    std::vector<port_t> y;
};

struct cellPMux_t : public cell_t{

    cellPMux_t(std::string newName, bool hide, const unsigned int inWidth, const unsigned int inSWidth) : width(inWidth), sWidth(inSWidth), cell_t(newName, hide, TypePMux){};

    const unsigned int width;
    const unsigned int sWidth;

    std::vector<port_t> s;
    std::vector<port_t> a;
    std::vector<port_t> b;
    std::vector<port_t> y;
};

struct cellSlice_t : public cell_t{

    cellSlice_t(std::string newName, bool hide, const unsigned int inOffset, const unsigned int inAWidth, const unsigned int inYWidth) : offset(inOffset),
                aWidth(inAWidth), yWidth(inYWidth), cell_t(newName, hide, TypeSlice){};

    const unsigned int offset;
    const unsigned int aWidth;
    const unsigned int yWidth;

    std::vector<port_t> a;
    std::vector<port_t> y;
};

struct cellSop_t : public cell_t{

    cellSop_t(std::string newName, bool hide, const unsigned int inWidth, const unsigned int inDepth, port_t inY) : width(inWidth), depth(inDepth), y(inY), cell_t(newName, hide, TypeSop){};

    const unsigned int width;
    const unsigned int depth;
    unsigned int *table;

    port_t y;
    std::vector<port_t> a;

};

struct cellSpecify2_t : public cell_t{

    cellSpecify2_t(std::string newName, bool hide, cellType_t newType, const unsigned int inFull, const unsigned int inSrcWidth, const unsigned int inDstWidth, const unsigned int inSrcDstPen,
                   const unsigned int inSrcDstPol, const unsigned int inTRiseMin, const unsigned int inTRiseTyp, const unsigned int inTRiseMax, const unsigned int inTFallMin,
                   const unsigned int inTFallTyp, const unsigned int inTFallMax, port_t inEn) : full(inFull), srcWidth(inSrcWidth), dstWidth(inDstWidth), srcDstPen(inSrcDstPen),
                   srcDstPol(inSrcDstPol), tRiseMin(inTRiseMin), tRiseTyp(inTRiseTyp), tRiseMax(inTRiseMax), tFallMin(inTFallMin), tFallTyp(inTFallTyp), tFallMax(inTFallMax), 
                   en(inEn), cell_t(newName, hide, newType){};

    const unsigned int full;
    const unsigned int srcWidth;
    const unsigned int dstWidth;
    const unsigned int srcDstPen;
    const unsigned int srcDstPol;
    const unsigned int tRiseMin;
    const unsigned int tRiseTyp;
    const unsigned int tRiseMax;
    const unsigned int tFallMin;
    const unsigned int tFallTyp;
    const unsigned int tFallMax;

    port_t en;
    std::vector<port_t> src;
    std::vector<port_t> dst;
};

struct cellSpecify3_t : public cellSpecify2_t{

    cellSpecify3_t(std::string newName, bool hide, cellType_t newType, const unsigned int inFull, const unsigned int inSrcWidth, const unsigned int inDstWidth, const unsigned int inSrcDstPen,
                   const unsigned int inSrcDstPol, const unsigned int inTRiseMin, const unsigned int inTRiseTyp, const unsigned int inTRiseMax, const unsigned int inTFallMin,
                   const unsigned int inTFallTyp, const unsigned int inTFallMax, const unsigned int inEdgeEn, const unsigned int inEdgePol, const unsigned int inDatDstPen,
                   const unsigned int inDatDstPol, port_t inEn) : edgeEn(inEdgeEn), edgePol(inEdgePol), datDstPen(inDatDstPen), datDstPol(inDatDstPol), cellSpecify2_t(newName, hide, 
                   newType, inFull, inSrcWidth, inDstWidth, inSrcDstPen, inSrcDstPol, inTRiseMin, inTRiseTyp, inTRiseMax, inTFallMin, inTFallTyp, inTFallMax, inEn){};

    const unsigned int edgeEn;
    const unsigned int edgePol;
    const unsigned int datDstPen;
    const unsigned int datDstPol;

    std::vector<port_t> dat;
};

struct cellTriBuf_t : public cell_t{

    cellTriBuf_t(std::string newName, bool hide, const unsigned int inWidth, port_t inEn) : width(inWidth), en(inEn), cell_t(newName, hide, TypeTriBuf){};

    const unsigned int width;

    port_t en;
    std::vector<port_t> a;
    std::vector<port_t> y;
};

struct cellSr_t : public cell_t{

    cellSr_t(std::string newName, bool hide, const unsigned int inWidth, const unsigned char inSetPolarity, const unsigned char inClrPolarity) : width(inWidth),
             setPolarity(inSetPolarity), clrPolarity(inClrPolarity), cell_t(newName, hide, TypeSr){};

    const unsigned int width;
    const unsigned char setPolarity;
    const unsigned char clrPolarity;

    std::vector<port_t> set;
    std::vector<port_t> clr;
    std::vector<port_t> q;
};

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
void cellFromYosysJson(json &inJ, const std::string inCellName, const cellType_t inCellType, module_t *inModule, cellArithmetic_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, const cellType_t inCellType, module_t *inModule, cellConstAssign_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, const cellType_t inCellType, module_t *inModule, cellAEn_t **outCell);
void cellFromYosysJson(json &inJ, const std::string inCellName, const cellType_t inCellType, module_t *inModule, cellAY_t **outCell);

#endif // CELL_H_