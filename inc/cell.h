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
 * @brief This function will return the cellType_t belonging to a string version of it
 * 
 * @param inString The string for which the cellType_t should be returned
 * 
 * @return The cellType_t beloning to the string
 */
cellType_t getCellType(std::string inString);

/**
 * @brief This function will return a string belonging to the cellType_t version of it
 * 
 * @param inType The cellType_t for which the string should be returned
 * 
 * @return The string beloning to the cellType_t
 */
std::string getCellType(cellType_t inType);

/**
 * @brief This struct serves as a base struct for all further cell implementations
 */
struct cell_t
{
    cell_t(std::string newName, bool hide, cellType_t newType) : name(newName), hideName(hide), type(newType){};
    const std::string name; //!< The name of this cell
    const bool hideName;    //!< true, if this cells name should be hidden, false otherwise
    const cellType_t type;  //!< The exact type of this cell
    std::vector<std::pair<std::string, std::string>> attributes; //!< All the attributes given to the cell

    /**
     * @brief This function will store all the common information of cells in a json and the specific information belonging to the cell type
     * This function will call the storeAdditionalInJson function belonging to the type of the cell
     * 
     * @return A json representation of this cell with respect to its type
     */
    json storeInJson();
    
    /**
     * @brief This Function will add all information of the struct that overrides this function to the json description
     * 
     * @return A json object holding the details about a cell
     */
    virtual json storeAdditionalInJson() = 0;
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

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    const bool aSigned;         //!< true, if a is a signed value, false otherwise
    const bool bSigned;         //!< true, if b is a signed value, false otherwise
    const unsigned int aWidth;  //!< The width of input a
    const unsigned int bWidth;  //!< The width of input b
    const unsigned int yWidth;  //!< The width of output y
    std::vector<port_t> a;      //!< vector of ports which act as the a input.
    std::vector<port_t> b;      //!< vector of ports which act as the b input.
    std::vector<port_t> y;      //!< vector of ports which act as the y output.

    //virtual void cellToJson() = 0;
    //virtual void cellFromJson() = 0;

};

/**
 * @brief This struct represents D-FlipFlops
 * Belonging type:
 * TypeDff
 */
struct cellDFlipFlop_t : public cell_t{

    cellDFlipFlop_t(std::string newName, bool hide, const unsigned int newWidth, const unsigned int newClkPolarity, 
                    cellType_t newType, port_t newClk) : width(newWidth), clkPolarity(newClkPolarity), clk(newClk), cell_t(newName, hide, newType){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    virtual json storeAdditionalInJson();

    const unsigned int width;       //!< The width of D and Q
    const unsigned int clkPolarity; //!< The polarity of the CLK
    port_t clk;                     //!< The port working as the CLK
    std::vector<port_t> d;          //!< The input port D
    std::vector<port_t> q;          //!< The output port Q
};
/**
 * @brief This struct represents a D-FlipFlop with an extra enable pin
 * 
 */
struct cellDFlipFlopEnable_t : public cellDFlipFlop_t{
    cellDFlipFlopEnable_t(std::string newName, bool hide, const unsigned int newWidth, const unsigned int newClkPolarity, const unsigned int newEnPolarity, cellType_t newType,
                          port_t newClk, port_t newEn) : enPolarity(newEnPolarity), en(newEn), cellDFlipFlop_t(newName, hide, newWidth, newClkPolarity, newType, newClk) {};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    const unsigned int enPolarity;  //!< The polarity of the enable pin
    port_t en;                      //!< The port working as the enable pin
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

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();
    
    const unsigned int setPolarity;     //!< The polarity of the set pin
    const unsigned int clrPolarity;     //!< The polarity of the clear pin
    std::vector<port_t> set;            //!< The port working as the set pin, has the width of the D-FlipFlop it is inherited from
    std::vector<port_t> clr;            //!< The port working as the clr pin, has the width of the D-FlipFlop it is inherited from
};

/**
 * @brief This struct represents an A-Reset-D-FlipFlop
 * This flipflops output will be set to a certain value when a reset is triggered. otherwise it behaves like a D-Flip-Flop
 */

struct cellAdff_t : public cellDFlipFlop_t{
    cellAdff_t(std::string newName, bool hide, unsigned int newWidth, unsigned int newClkPolarity, unsigned int newArstPolarity, unsigned int newArstValue,
               port_t newClk, port_t newArst) : arstPolarity(newArstPolarity), arstValue(newArstValue), arst(newArst), 
               cellDFlipFlop_t(newName, hide, newWidth, newClkPolarity,TypeAdff, newClk) {};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    const unsigned int arstPolarity;    //!< The polarity of the A-Reset signal
    const unsigned int arstValue;       //!< The value to which Q will be resetted
    port_t arst;                        //!< The port for the A-Reset input       
};


/**
 * @brief This struct represents a D-FlipFlip but with an global clock
 * @warning INCOMPLETE
 */
struct cellFlipFlop_t : public cell_t{ // TODO Add global clock ?

    cellFlipFlop_t(std::string newName, bool hide, unsigned int newWidth) : width(newWidth), cell_t(newName, hide, TypeFf){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    const unsigned int width;   //!< The width of D and Q
    std::vector<port_t> d;      //!< The input pins D
    std::vector<port_t> q;      //!< The output pins Q
};

/**
 * @brief This struct represents a D-Latch
 */
struct cellDLatch_t : public cell_t{
    

    cellDLatch_t(std::string newName, bool hide,  cellType_t newType, const unsigned int newWidth, const unsigned int newEnPolarity, port_t newEn) : width(newWidth), enPolarity(newEnPolarity),
                 en(newEn), cell_t(newName, hide, newType){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    virtual json storeAdditionalInJson();

    const unsigned int width;       //!< The width of D and Q
    const unsigned int enPolarity;  //!< The polarity of the enable pin
    port_t en;                      //!< The enabel pin
    std::vector<port_t> d;          //!< The input pins D
    std::vector<port_t> q;          //!< The output pins Q
};

/**
 * @brief This struct represents a Set-Reset-D-Latch
 */
struct cellDLatchSR_t : public cellDLatch_t{

    cellDLatchSR_t(std::string newName, bool hide, cellType_t newType, const unsigned int newWidth, const unsigned int newEnPolarity,  port_t newEn,
                   unsigned int newSetPolarity, unsigned int newClrPolarity) : setPolarity(newSetPolarity), clrPolarity(newClrPolarity),
                   cellDLatch_t(newName, hide, newType, newWidth, newEnPolarity, newEn){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    const unsigned int setPolarity;     //!< The polarity of the set pin
    const unsigned int clrPolarity;     //!< The polarity of the clear pin

    std::vector<port_t> set;            //!< The set port, has the width of the DLatch it is inherited from
    std::vector<port_t> clr;            //!< The clr port, has the width of the DLatch it is inherited from
};

/**
 * @brief This struct represents a constant assignment
 */
struct cellConstAssign_t : public cell_t{
    cellConstAssign_t(std::string newName, bool hide, cellType_t newType, unsigned int newWidth) : cell_t(newName, hide, newType){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    unsigned int width;         //!< The width of the constant value
    std::vector<port_t> y;      //!< The output port holding the value
};

/**
 * @brief This struct represents an ALU unit
 * It is based on a normal arithmetic operation, but with additional signals:
 * carry in
 * carry out
 */
struct cellAlu_t : public cellArithmetic_t{

    cellAlu_t(std::string newName, bool hide, const bool inASigned, const bool inBSigned, const unsigned int inAWidth,
               const unsigned int inBWidth, const unsigned int inYWidth, port_t newCi, port_t newBi) : ci(newCi), bi(newBi),
              cellArithmetic_t(newName, hide, TypeAlu, inASigned, inBSigned, inAWidth, inBWidth, inYWidth){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    port_t ci;                  //!< The pin for the carry in signal
    port_t bi;
    std::vector<port_t> x;
    std::vector<port_t> co;     //!< The pins for the carry out signal
};

/**
 * @brief This struct represents cells with an A and an Enable port
 * Belonging Types:
 * TypeAssert, TypeAssume, TypeCover, TypeFair, TypeLive
 */
struct cellAEn_t : public cell_t{

    cellAEn_t(std::string newName, bool hide, const cellType_t type, port_t newA, port_t newEn) : a(newA), en(newEn), cell_t(newName, hide, type){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    port_t a;       //!< The a port of this cell
    port_t en;      //!< The enable port of this cell
};

/**
 * @brief This struct represents a cell concatinating two signals
 */
struct cellConcat_t : public cell_t{

    cellConcat_t(std::string newName, bool hide, unsigned int newAWidth, unsigned int newBWidth) : aWidth(newAWidth), bWidth(newBWidth), cell_t(newName, hide, TypeConcat){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    const unsigned int aWidth;  //!< The width of the input a
    const unsigned int bWidth;  //!< the width of the input b

    std::vector<port_t> a;      //!< The input ports a
    std::vector<port_t> b;      //!< The input ports b
    std::vector<port_t> y;      //!< The output ports y, width is aWidth+bWidth

};

/**
 * @brief This struct represents an equiv cell. It will set an output to the inputs value if they are the same otherwise to don't care
 */
struct cellEquiv_t : public cell_t{

    cellEquiv_t(std::string newName, bool hide, port_t newA, port_t newB, port_t newY) : a(newA), b(newB), y(newY), cell_t(newName, hide, TypeEquiv){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    port_t a;   //!< The a input pin
    port_t b;   //!< The b input pin
    port_t y;   //!< The y output pin
};

struct cellFa_t : public cell_t{

    cellFa_t(std::string newName, bool hide, unsigned int newWidth) : width(newWidth), cell_t(newName, hide, TypeFa){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    const unsigned int width;   //!< The width of all the ports

    std::vector<port_t> a;      //!< The ports acting as the a input
    std::vector<port_t> b;      //!< The ports acting as the b input
    std::vector<port_t> c;      //!< The ports acting as the c input
    std::vector<port_t> x;      //!< The ports acting as the x output
    std::vector<port_t> y;      //!< The ports acting as the y output
};

struct cellFsm_t : public cell_t{

    cellFsm_t(std::string newName, bool hide, unsigned int newClkPolarity, unsigned int newArstPolarity, unsigned int newCtrlInWidth, unsigned int newCtrlOutWidth,
              unsigned int newStateBits, unsigned int newStateNum, unsigned int newStateNumLog2, unsigned int newStateRst, unsigned int newStateTable, unsigned int newTransNum,
              unsigned int newTransTable, port_t newClk, port_t newArst) : clkPolarity(newClkPolarity), arstPolarity(newArstPolarity), ctrlInWidth(newCtrlInWidth),
              ctrlOutWidth(newCtrlOutWidth), stateBits(newStateBits), stateNum(newStateNum), stateNumLog2(newStateNumLog2), stateRst(newStateRst), stateTable(newStateTable),
              transNum(newTransNum), transTable(newTransTable), clk(newClk), arst(newArst), cell_t(newName, hide, TypeFsm){};
    
    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();
    
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

    std::vector<port_t> ctrlIn;          //!< The ports acting as the ctrlIn input
    std::vector<port_t> ctrlOut;         //!< The ports acting as the ctrlOut output
};

struct cellInitState_t : public cell_t{

    cellInitState_t(std::string newName, bool hide, port_t newY) : y(newY), cell_t(newName, hide, TypeInitState){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    port_t y;  //!< The port acting as the y output
};

struct cellLcu_t : public cell_t{
    cellLcu_t(std::string newName, bool hide,unsigned int newWidth, port_t newCi) : width(newWidth), ci(newCi), cell_t(newName, hide, TypeLcu){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    const unsigned int width;   //!< The width of all the ports

    port_t ci;                  //!< The port acting as the carry in input

    std::vector<port_t> p;      //!< The ports acting as the p input
    std::vector<port_t> g;      //!< The ports acting as the g input
    std::vector<port_t> co;     //!< The ports acting as the co output
};

struct cellAY_t : public cell_t{

    cellAY_t(std::string newName, bool hide, cellType_t newType, unsigned int newASigned, unsigned int newAWidth, unsigned int newYWidth) : aSigned(newASigned),
             aWidth(newAWidth), yWidth(newYWidth), cell_t(newName, hide, newType){};
    
    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();
    
    const bool aSigned;
    const unsigned int aWidth;  //!< The width of the a port
    const unsigned int yWidth;  //!< The width of the y port

    std::vector<port_t> a;      //!< The ports acting as the a input
    std::vector<port_t> y;      //!< The ports acting as the y output
};

struct cellLut_t : public cell_t{
    
    cellLut_t(std::string newName, bool hide, unsigned int newWidth, unsigned int newLut, port_t newY) : width(newWidth), lut(newLut), y(newY), 
              cell_t(newName, hide, TypeLut){};
    
    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();
    
    const unsigned int width;   //!< The width of all the ports
    const unsigned int lut;

    port_t y;                   //!< The ports acting as the y output

    std::vector<port_t> a;      //!< The ports acting as the a input
};

struct cellMacc_t : public cell_t{
    cellMacc_t(std::string newName, bool hide, const unsigned int inAWidth, const unsigned int inBWidth, const unsigned int inYWidth, 
               const unsigned int inConfig, const unsigned int inConfigWidth) : aWidth(inAWidth), bWidth(inBWidth), yWidth(inYWidth),
               config(inConfig), configWidth(inConfigWidth), cell_t(newName, hide, TypeMacc){};
    
    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    const unsigned int aWidth;          //!< The width of the a port
    const unsigned int bWidth;          //!< The width of the b port
    const unsigned int yWidth;          //!< The width of the y port
    const unsigned int config;
    const unsigned int configWidth;

    std::vector<port_t> a;              //!< The ports acting as the a input
    std::vector<port_t> b;              //!< The ports acting as the a input
    std::vector<port_t> y;              //!< The ports acting as the y output
};

struct cellMem_t : public cell_t{

    cellMem_t(std::string newName, bool hide, const unsigned int inMemId, const int inSize, const int inOffset, const int inABits,
              const int inWidth, const int inInit, const int inRdPorts, const unsigned int inRdClkEnable, const unsigned int inRdClkPolarity,
              const unsigned int inRdTransparent, const int inWrPorts, const unsigned int inWrClkEnable, const unsigned int inWrClkPolarity) :
              memId(inMemId), size(inSize), offset(inOffset), aBits(inABits), width(inWidth), init(inInit), rdPorts(inRdPorts), rdClkEnable(inRdClkEnable),
              rdClkPolarity(inRdClkPolarity), rdTransparent(inRdTransparent), wrPorts(inWrPorts), wrClkEnable(inWrClkEnable), wrClkPolarity(inWrClkPolarity),
              cell_t(newName, hide, TypeMem) {};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    const unsigned int memId;
    const int size;
    const int offset;
    const int aBits;
    const int width;                    //!< The width of all the ports
    const int init;
    const int rdPorts;
    const unsigned int rdClkEnable;
    const unsigned int rdClkPolarity;
    const unsigned int rdTransparent;
    const int wrPorts;
    const unsigned int wrClkEnable;
    const unsigned int wrClkPolarity;

    std::vector<port_t> rdClk;          //!< The ports acting as the read clock input
    std::vector<port_t> rdEn;           //!< The ports acting as the read enable input
    std::vector<port_t> rdAddr;         //!< The ports acting as the read address input
    std::vector<port_t> rdData;         //!< The ports acting as the read data output
    std::vector<port_t> wrClk;          //!< The ports acting as the write clock input
    std::vector<port_t> wrEn;           //!< The ports acting as the write enable input
    std::vector<port_t> wrAddr;         //!< The ports acting as the write address input
    std::vector<port_t> wrData;         //!< The ports acting as the write data input
};

struct cellMemInit_t : public cell_t{

    cellMemInit_t(std::string newName, bool hide, const unsigned int inMemId, const unsigned int inABits, const unsigned int inWidth,
                  const unsigned int inWords, const unsigned int inPriority) : memId(inMemId), aBits(inABits), width(inWidth), words(inWords),
                  priority(inPriority), cell_t(newName, hide, TypeMemInit){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    const unsigned int memId;
    const unsigned int aBits;
    const unsigned int width;       //!< The width of all the ports
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

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    const unsigned int memId;
    const unsigned int aBits;
    const unsigned int width;           //!< The width of all the ports
    const unsigned int clkEnable;
    const unsigned int clkPolarity; 
    const unsigned int transparent;

    port_t clk;
    port_t en;

    std::vector<port_t> addr;           //!< The ports acting as the read address input
    std::vector<port_t> data;           //!< The ports acting as the read data output
};

struct cellMemWr_t : public cell_t{
    
    cellMemWr_t(std::string newName, bool hide, const unsigned int inMemId, const unsigned int inABits, const unsigned int inWidth,
                  const unsigned int inClkEnable, const unsigned int inClkPolarity, const unsigned int inTransparnt, port_t inClk) : 
                  memId(inMemId), aBits(inABits), width(inWidth), clkEnable(inClkEnable), clkPolarity(inClkPolarity), transparent(inTransparnt), 
                  clk(inClk), cell_t(newName, hide, TypeMemInit){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    const unsigned int memId;
    const unsigned int aBits;
    const unsigned int width;           //!< The width of all the ports
    const unsigned int clkEnable;
    const unsigned int clkPolarity;
    const unsigned int transparent;

    port_t clk;
    
    std::vector<port_t> en;             //!< The ports acting as the write enable input
    std::vector<port_t> addr;           //!< The ports acting as the write address input
    std::vector<port_t> data;           //!< The ports acting as the write data input
};

struct cellMux_t : public cell_t{

    cellMux_t(std::string newName, bool hide, const unsigned int inWidth, port_t inS) : width(inWidth), s(inS), cell_t(newName, hide, TypeMux){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    const unsigned int width;   //!< The width of all the ports
    port_t s;

    std::vector<port_t> a;      //!< The ports acting as the a input
    std::vector<port_t> b;      //!< The ports acting as the b input
    std::vector<port_t> y;      //!< The ports acting as the y output
};

struct cellPMux_t : public cell_t{

    cellPMux_t(std::string newName, bool hide, const unsigned int inWidth, const unsigned int inSWidth) : width(inWidth), sWidth(inSWidth), cell_t(newName, hide, TypePMux){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    const unsigned int width;   //!< The width of all the a,b,y ports
    const unsigned int sWidth;  //!< The width of the s ports

    std::vector<port_t> s;      //!< The ports acting as the s input
    std::vector<port_t> a;      //!< The ports acting as the a input
    std::vector<port_t> b;      //!< The ports acting as the b input
    std::vector<port_t> y;      //!< The ports acting as the y output
};

struct cellSlice_t : public cell_t{

    cellSlice_t(std::string newName, bool hide, const unsigned int inOffset, const unsigned int inAWidth, const unsigned int inYWidth) : offset(inOffset),
                aWidth(inAWidth), yWidth(inYWidth), cell_t(newName, hide, TypeSlice){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    const unsigned int offset;
    const unsigned int aWidth;  //!< The width of the a port
    const unsigned int yWidth;  //!< The width of the y port

    std::vector<port_t> a;      //!< The ports acting as the a input
    std::vector<port_t> y;      //!< The ports acting as the y output
};

struct cellSop_t : public cell_t{

    cellSop_t(std::string newName, bool hide, const unsigned int inWidth, const unsigned int inDepth, port_t inY) : width(inWidth), depth(inDepth), y(inY), cell_t(newName, hide, TypeSop){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    const unsigned int width;   //!< The width of all the ports
    const unsigned int depth;
    unsigned int *table;

    port_t y;                   //!< The port acting as the y output
    std::vector<port_t> a;      //!< The ports acting as the a input

};

struct cellSpecify2_t : public cell_t{

    cellSpecify2_t(std::string newName, bool hide, cellType_t newType, const unsigned int inFull, const unsigned int inSrcWidth, const unsigned int inDstWidth, const unsigned int inSrcDstPen,
                   const unsigned int inSrcDstPol, const unsigned int inTRiseMin, const unsigned int inTRiseTyp, const unsigned int inTRiseMax, const unsigned int inTFallMin,
                   const unsigned int inTFallTyp, const unsigned int inTFallMax, port_t inEn) : full(inFull), srcWidth(inSrcWidth), dstWidth(inDstWidth), srcDstPen(inSrcDstPen),
                   srcDstPol(inSrcDstPol), tRiseMin(inTRiseMin), tRiseTyp(inTRiseTyp), tRiseMax(inTRiseMax), tFallMin(inTFallMin), tFallTyp(inTFallTyp), tFallMax(inTFallMax), 
                   en(inEn), cell_t(newName, hide, newType){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    const unsigned int full;
    const unsigned int srcWidth;    //!< The width of the src port
    const unsigned int dstWidth;    //!< The width of the dst port
    const unsigned int srcDstPen;
    const unsigned int srcDstPol;
    const unsigned int tRiseMin;
    const unsigned int tRiseTyp;
    const unsigned int tRiseMax;
    const unsigned int tFallMin;
    const unsigned int tFallTyp;
    const unsigned int tFallMax;

    port_t en;                      //!< The port acting as the enable input
    std::vector<port_t> src;        //!< The ports acting as the src input
    std::vector<port_t> dst;        //!< The ports acting as the dst input
};

struct cellSpecify3_t : public cellSpecify2_t{

    cellSpecify3_t(std::string newName, bool hide, cellType_t newType, const unsigned int inFull, const unsigned int inSrcWidth, const unsigned int inDstWidth, const unsigned int inSrcDstPen,
                   const unsigned int inSrcDstPol, const unsigned int inTRiseMin, const unsigned int inTRiseTyp, const unsigned int inTRiseMax, const unsigned int inTFallMin,
                   const unsigned int inTFallTyp, const unsigned int inTFallMax, const unsigned int inEdgeEn, const unsigned int inEdgePol, const unsigned int inDatDstPen,
                   const unsigned int inDatDstPol, port_t inEn) : edgeEn(inEdgeEn), edgePol(inEdgePol), datDstPen(inDatDstPen), datDstPol(inDatDstPol), cellSpecify2_t(newName, hide, 
                   newType, inFull, inSrcWidth, inDstWidth, inSrcDstPen, inSrcDstPol, inTRiseMin, inTRiseTyp, inTRiseMax, inTFallMin, inTFallTyp, inTFallMax, inEn){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    const unsigned int edgeEn;
    const unsigned int edgePol;
    const unsigned int datDstPen;
    const unsigned int datDstPol;

    std::vector<port_t> dat;
};

struct cellTriBuf_t : public cell_t{

    cellTriBuf_t(std::string newName, bool hide, const unsigned int inWidth, port_t inEn) : width(inWidth), en(inEn), cell_t(newName, hide, TypeTriBuf){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();

    const unsigned int width;   //!< The width of all the ports

    port_t en;                  //!< The ports acting as the enable input
    std::vector<port_t> a;      //!< The ports acting as the a input
    std::vector<port_t> y;      //!< The ports acting as the y output
};

struct cellSr_t : public cell_t{

    cellSr_t(std::string newName, bool hide, const unsigned int inWidth, const unsigned char inSetPolarity, const unsigned char inClrPolarity) : width(inWidth),
             setPolarity(inSetPolarity), clrPolarity(inClrPolarity), cell_t(newName, hide, TypeSr){};

    /**
     * @brief This function will add the specific elements of this cell type to a json representation
     * 
     * @return A json representation if this cell
     */
    json storeAdditionalInJson();
    
    const unsigned int width;           //!< The width of all the ports
    const unsigned char setPolarity;    //!< The polarity of the set signals
    const unsigned char clrPolarity;    //!< The polarity of the clear signals

    std::vector<port_t> set;            //!< The ports acting as the set input
    std::vector<port_t> clr;            //!< The ports acting as the clear input
    std::vector<port_t> q;              //!< The ports acting as the q output
};

#endif // CELL_H_