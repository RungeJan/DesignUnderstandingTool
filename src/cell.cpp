#include "cell.h"
#include "module.h"
#include "processing.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

#include "localExceptions.h"

cellType_t getCellType(string inString)
{
    inString = inString.substr(1, inString.size() - 2);
    if ('a' == inString.at(1))
    {
        if ("$add" == inString)
        {
            return TypeAdd;
        }
        if ("$adff" == inString)
        {
            return TypeAdff;
        }
        if ("$allconst" == inString)
        {
            return TypeAllConst;
        }
        if ("$allseq" == inString)
        {
            return TypeAllSeq;
        }
        if ("$alu" == inString)
        {
            return TypeAlu;
        }
        if ("$and" == inString)
        {
            return TypeAnd;
        }
        if ("$anyconst" == inString)
        {
            return TypeAnyConst;
        }
        if ("$anyseq" == inString)
        {
            return TypeAnySeq;
        }
        if ("$assert" == inString)
        {
            return TypeAssert;
        }
        if ("$assume" == inString)
        {
            return TypeAssume;
        }
    }
    if ('c' == inString.at(1))
    {
        if ("$concat" == inString)
        {
            return TypeConcat;
        }
        if ("$cover" == inString)
        {
            return TypeCover;
        }
    }
    if ('d' == inString.at(1))
    {
        if ("$dff" == inString)
        {
            return TypeDff;
        }
        if ("$dffe" == inString)
        {
            return TypeDffe;
        }
        if ("$dffsr" == inString)
        {
            return TypeDffsr;
        }
        if ("$div" == inString)
        {
            return TypeDiv;
        }
        if ("$dlatch" == inString)
        {
            return TypeDLatch;
        }
        if ("$dlatchsr" == inString)
        {
            return TypeDLatchSR;
        }
    }
    if ('e' == inString.at(1))
    {
        if ("$eq" == inString)
        {
            return TypeEq;
        }
        if ("$equiv" == inString)
        {
            return TypeEquiv;
        }
        if ("$eqx" == inString)
        {
            return TypeEqx;
        }
    }
    if ('f' == inString.at(1))
    {
        if ("$fa" == inString)
        {
            return TypeFa;
        }
        if ("$fair" == inString)
        {
            return TypeFair;
        }
        if ("$ff" == inString)
        {
            return TypeFf;
        }
        if ("$fsm" == inString)
        {
            return TypeFsm;
        }
    }
    if ('g' == inString.at(1))
    {
        if ("$ge" == inString)
        {
            return TypeGe;
        }
        if ("$gt" == inString)
        {
            return TypeGt;
        }
    }
    if ('i' == inString.at(1))
    {
        if ("$initstate" == inString)
        {
            return TypeInitState;
        }
    }
    if ('l' == inString.at(1))
    {
        if ("$lcu" == inString)
        {
            return TypeLcu;
        }
        if ("$le" == inString)
        {
            return TypeLe;
        }
        if ("$live" == inString)
        {
            return TypeLive;
        }
        if ("$logic_and" == inString)
        {
            return TypeLogicAnd;
        }
        if ("$logic_not" == inString)
        {
            return TypeLogicNot;
        }
        if ("$logic_or" == inString)
        {
            return TypeLogicOr;
        }
        if ("$lt" == inString)
        {
            return TypeLt;
        }
        if ("$lut" == inString)
        {
            return TypeLut;
        }
    }
    if ('m' == inString.at(1))
    {
        if ("$macc" == inString)
        {
            return TypeMacc;
        }
        if ("$mem" == inString)
        {
            return TypeMem;
        }
        if ("$meminit" == inString)
        {
            return TypeMemInit;
        }
        if ("$memrd" == inString)
        {
            return TypeMemRd;
        }
        if ("$memwr" == inString)
        {
            return TypeMemWr;
        }
        if ("$mod" == inString)
        {
            return TypeMod;
        }
        if ("$mul" == inString)
        {
            return TypeMul;
        }
        if ("$mux" == inString)
        {
            return TypeMux;
        }
    }
    if ('n' == inString.at(1))
    {
        if ("$ne" == inString)
        {
            return TypeNe;
        }
        if ("$neg" == inString)
        {
            return TypeNeg;
        }
        if ("$nex" == inString)
        {
            return TypeNex;
        }
        if ("$not" == inString)
        {
            return TypeNot;
        }
    }
    if ('o' == inString.at(1))
    {
        if ("$or" == inString)
        {
            return TypeOr;
        }
    }
    if ('p' == inString.at(1))
    {
        if ("$pmux" == inString)
        {
            return TypePMux;
        }
        if ("$pos" == inString)
        {
            return TypePos;
        }
        if ("$pow" == inString)
        {
            return TypePow;
        }
    }
    if ('r' == inString.at(1))
    {
        if ("$reduce_and" == inString)
        {
            return TypeReduceAnd;
        }
        if ("$reduce_bool" == inString)
        {
            return TypeReduceBool;
        }
        if ("$reduce_or" == inString)
        {
            return TypeReduceOr;
        }
        if ("$reduce_xnor" == inString)
        {
            return TypeReduceXnor;
        }
        if ("$reduce_xor" == inString)
        {
            return TypeReduceXor;
        }
    }
    if ('s' == inString.at(1))
    {
        if ("$shift" == inString)
        {
            return TypeShift;
        }
        if ("$shiftx" == inString)
        {
            return TypeShiftX;
        }
        if ("$shl" == inString)
        {
            return TypeShl;
        }
        if ("$shr" == inString)
        {
            return TypeShr;
        }
        if ("$slice" == inString)
        {
            return TypeSlice;
        }
        if ("$sop" == inString)
        {
            return TypeSop;
        }
        if ("$specify2" == inString)
        {
            return TypeSpecify2;
        }
        if ("$specify3" == inString)
        {
            return TypeSpecify3;
        }
        if ("$sr" == inString)
        {
            return TypeSr;
        }
        if ("$sshl" == inString)
        {
            return TypeSshl;
        }
        if ("$sshr" == inString)
        {
            return TypeSshr;
        }
        if ("$sub" == inString)
        {
            return TypeSub;
        }
    }
    if ('t' == inString.at(1))
    {
        if ("$tribuf" == inString)
        {
            return TypeTriBuf;
        }
    }
    if ('x' == inString.at(1))
    {
        if ("xnor$" == inString)
        {
            return TypeXnor;
        }
        if ("$xor" == inString)
        {
            return TypeXor;
        }
    }

    cerr << "Unknown type: " << inString << endl;
    return TypeUnknown;
}

void cellFromYosysJson(json &inJ, string inCellName, module_t *inModule, cell_t **outCell)
{
    const cellType_t type = getCellType(inJ["type"].dump());
    switch (type)
    {
    // Cells with ports (A, B, Y)
    case TypeAdd:
    case TypeAnd:
    case TypeDiv:
    case TypeEq:
    case TypeEqx:
    case TypeGe:
    case TypeGt:
    case TypeLe:
    case TypeLogicAnd:
    case TypeLogicOr:
    case TypeLt:
    case TypeMod:
    case TypeMul:
    case TypeNe:
    case TypeNex:
    case TypeOr:
    case TypePow:
    case TypeShift:
    case TypeShiftX:
    case TypeShl:
    case TypeShr:
    case TypeSshl:
    case TypeSshr:
    case TypeSub:
    case TypeXnor:
    case TypeXor:
    {
        cellFromYosysJson(inJ, inCellName, type, inModule, (cellArithmetic_t **)outCell);
        break;
    }
    // Cells with port (CLK, D, Q)
    case TypeDff:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellDFlipFlop_t **)outCell);
        break;
    }
    // Cells with port (CLK, EN, D, Q)
    case TypeDffe:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellDFlipFlopEnable_t **)outCell);
        break;
    }
    // Cells with port (CLK, SET, CLR, D, Q)
    case TypeDffsr:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellDFlipFlopSetReset_t **)outCell);
        break;
    }
    // Cells for flipflops with global clock
    case TypeFf:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellFlipFlop_t **)outCell);
        break;
    }
    // Cells with port (EN, D, Q)
    case TypeDLatch:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellDLatch_t **)outCell);
        break;
    }
    case TypeDLatchSR:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellDLatchSR_t **)outCell);
        break;
    }
    case TypeAdff:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellAdff_t **)outCell);
        break;
    }
    // Cells for constant expressions
    case TypeAllConst:
    case TypeAllSeq:
    case TypeAnyConst:
    case TypeAnySeq:
    {
        cellFromYosysJson(inJ, inCellName, type, inModule, (cellConstAssign_t **)outCell);
        break;
    }
    case TypeAlu:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellAlu_t **)outCell);
        break;
    }
    case TypeAssert:
    case TypeAssume:
    case TypeCover:
    case TypeFair:
    case TypeLive:
    {
        cellFromYosysJson(inJ, inCellName, type, inModule, (cellAEn_t **)outCell);
        break;
    }
    case TypeConcat:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellConcat_t **)outCell);
        break;
    }
    case TypeEquiv:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellEquiv_t **)outCell);
        break;
    }
    case TypeFsm:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellFsm_t **)outCell);
        break;
    }
    case TypeInitState:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellInitState_t **)outCell);
        break;
    }
    case TypeLcu:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellLcu_t **)outCell);
        break;
    }
    case TypeLogicNot:
    case TypeNeg:
    case TypeNot:
    case TypePos:
    case TypeReduceAnd:
    case TypeReduceBool:
    case TypeReduceOr:
    case TypeReduceXnor:
    case TypeReduceXor:
    {
        cellFromYosysJson(inJ, inCellName, type, inModule, (cellAY_t **)outCell);
        break;
    }
    case TypeLut:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellLut_t **)outCell);
        break;
    }
    case TypeMacc:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellMacc_t **)outCell);
        break;
    }
    case TypeMem:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellMem_t **)outCell);
        break;
    }
    case TypeMemInit:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellMemInit_t **)outCell);
        break;
    }
    case TypeMemRd:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellMemRd_t **)outCell);
        break;
    }
    case TypeMemWr:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellMemWr_t **)outCell);
        break;
    }
    case TypeMux:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellMux_t **)outCell);
        break;
    }
    case TypePMux:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellPMux_t **)outCell);
        break;
    }
    case TypeSlice:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellSlice_t **)outCell);
        break;
    }
    case TypeSop:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellSop_t **)outCell);
        break;
    }
    case TypeSpecify2:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellSpecify2_t **)outCell);
        break;
    }
    case TypeSpecify3:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellSpecify3_t **)outCell);
        break;
    }
    case TypeTriBuf:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellTriBuf_t **)outCell);
        break;
    }
    case TypeSr:
    {
        cellFromYosysJson(inJ, inCellName, inModule, (cellSr_t **)outCell);
        break;
    }
    case TypeUnknown:
    default:
    {
        break;
    }
    }
    if (NULL != *outCell)
    {
        if (inJ.contains<string>("attributes"))
        {
            processYosysAttributesIntoVector(inJ["attributes"], (*outCell)->attributes);
        }
    }
}

port_t *createPort(json inJ, direction_t inDir, string inSignalName, module_t *inModule, int inPos = 0)
{
    int netId;
    bool isString = ((inJ["connections"][inSignalName].at(inPos).type()) == json::value_t::string);
    port_t *outPort = NULL;
    try
    {
        if (isString)
        {
            string temp = inJ["connections"][inSignalName].at(inPos);
            if (temp != "x")
            {
                netId = stoi(temp);
                outPort = new port_t(inDir, inModule->getNetWithId(netId));
            }
            else
            {
                outPort = &dontCarePort;
            }
        }
        else
        {
            netId = inJ["connections"][inSignalName].at(inPos);
            outPort = new port_t(inDir, inModule->getNetWithId(netId));
        }
    }
    catch (const elementDoesNotExistException &e)
    {
        cerr << e.what() << endl;
    }
    return outPort;
}

void cellFromYosysJson(json &inJ, const string inCellName, const cellType_t inCellType, module_t *inModule, cellArithmetic_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    *outCell = new cellArithmetic_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inCellType,
        inJ["parameters"]["A_SIGNED"].get<json::number_unsigned_t>(),
        inJ["parameters"]["B_SIGNED"].get<json::number_unsigned_t>(),
        inJ["parameters"]["A_WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["B_WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["Y_WIDTH"].get<json::number_unsigned_t>());

    for (int i = 0; i < (*outCell)->aWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "A", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->a.push_back(*newPort);
        }
    }

    for (int i = 0; i < (*outCell)->bWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "B", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->b.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->yWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionOutput, "Y", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->y.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const string inCellName, module_t *inModule, cellDFlipFlop_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    port_t *clkPort = createPort(inJ, DirectionInput, "CLK", inModule);

    *outCell = new cellDFlipFlop_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["CLK_POLARITY"].get<json::number_unsigned_t>(),
        TypeDff,
        *clkPort);
    for (int i = 0; i < (*outCell)->width; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "D", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->d.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionOutput, "Q", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->q.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const string inCellName, module_t *inModule, cellDFlipFlopEnable_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    port_t *clkPort = createPort(inJ, DirectionInput, "CLK", inModule);
    port_t *enPort = createPort(inJ, DirectionInput, "EN", inModule);

    *outCell = new cellDFlipFlopEnable_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["CLK_POLARITY"].get<json::number_unsigned_t>(),
        inJ["parameters"]["EN_POLARITY"].get<json::number_unsigned_t>(),
        TypeDffe,
        *clkPort,
        *enPort);
    for (int i = 0; i < (*outCell)->width; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "D", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->d.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionInput, "Q", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->q.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellDFlipFlopSetReset_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    port_t *clkPort = createPort(inJ, DirectionInput, "CLK", inModule);

    *outCell = new cellDFlipFlopSetReset_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["CLK_POLARITY"].get<json::number_unsigned_t>(),
        inJ["parameters"]["SET_POLARITY"].get<json::number_unsigned_t>(),
        inJ["parameters"]["CLR_POLARITY"].get<json::number_unsigned_t>(),
        TypeDffsr,
        *clkPort);

    for (int i = 0; i < (*outCell)->width; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "D", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->d.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionOutput, "Q", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->q.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionInput, "SET", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->set.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionInput, "CLR", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->clr.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellFlipFlop_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    *outCell = new cellFlipFlop_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["WIDTH"].get<json::number_unsigned_t>());

    for (int i = 0; i < (*outCell)->width; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "D", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->d.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionOutput, "Q", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->q.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellDLatch_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    port_t *enPort = createPort(inJ, DirectionInput, "EN", inModule);

    *outCell = new cellDLatch_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        TypeDLatch,
        inJ["parameters"]["WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["EN_POLARITY"].get<json::number_unsigned_t>(),
        *enPort);

    for (int i = 0; i < (*outCell)->width; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "D", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->d.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionOutput, "Q", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->q.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellDLatchSR_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    port_t *enPort = createPort(inJ, DirectionInput, "EN", inModule);

    *outCell = new cellDLatchSR_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        TypeDLatchSR,
        inJ["parameters"]["WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["EN_POLARITY"].get<json::number_unsigned_t>(),
        *enPort,
        inJ["parameters"]["SET_POLARITY"].get<json::number_unsigned_t>(),
        inJ["parameters"]["CLR_POLARITY"].get<json::number_unsigned_t>());

    for (int i = 0; i < (*outCell)->width; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "D", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->d.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionInput, "SET", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->set.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionInput, "CLR", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->clr.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionOutput, "Q", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->q.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellAdff_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    port_t *clkPort = createPort(inJ, DirectionInput, "CLK", inModule);
    port_t *arstPort = createPort(inJ, DirectionInput, "ARST", inModule);

    *outCell = new cellAdff_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["CLK_POLARITY"].get<json::number_unsigned_t>(),
        inJ["parameters"]["ARST_POLARITY"].get<json::number_unsigned_t>(),
        inJ["parameters"]["ARST_VALUE"].get<json::number_unsigned_t>(),
        *clkPort,
        *arstPort);
    for (int i = 0; i < (*outCell)->width; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "D", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->d.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionOutput, "Q", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->q.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, const cellType_t inCellType, module_t *inModule, cellConstAssign_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    *outCell = new cellConstAssign_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inCellType,
        inJ["parameters"]["WIDTH"].get<json::number_unsigned_t>());

    for (int i = 0; i < (*outCell)->width; i++)
    {
        port_t *newPort = createPort(inJ, DirectionOutput, "Y", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->y.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellAlu_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    port_t *ciPort = createPort(inJ, DirectionInput, "CI", inModule);
    port_t *biPort = createPort(inJ, DirectionInput, "BI", inModule);

    *outCell = new cellAlu_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["A_SIGNED"].get<json::number_unsigned_t>(),
        inJ["parameters"]["B_SIGNED"].get<json::number_unsigned_t>(),
        inJ["parameters"]["A_WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["B_WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["Y_WIDTH"].get<json::number_unsigned_t>(),
        *ciPort,
        *biPort);
    for (int i = 0; i < (*outCell)->aWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "A", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->a.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->bWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "B", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->b.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->yWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionOutput, "Y", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->y.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionOutput, "X", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->x.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionOutput, "CO", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->co.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, const cellType_t inCellType, module_t *inModule, cellAEn_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    port_t *aPort = createPort(inJ, DirectionInput, "A", inModule);
    port_t *enPort = createPort(inJ, DirectionInput, "EN", inModule);
    *outCell = new cellAEn_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inCellType,
        *aPort,
        *enPort);
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellConcat_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    *outCell = new cellConcat_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["A_WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["B_WIDTH"].get<json::number_unsigned_t>());

    for (int i = 0; i < (*outCell)->aWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "A", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->a.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->bWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "B", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->b.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->aWidth + (*outCell)->bWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionOutput, "Y", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->y.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellEquiv_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    port_t *aPort = createPort(inJ, DirectionInput, "A", inModule);
    port_t *bPort = createPort(inJ, DirectionInput, "B", inModule);
    port_t *yPort = createPort(inJ, DirectionInput, "Y", inModule);

    *outCell = new cellEquiv_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        *aPort,
        *bPort,
        *yPort);
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellFa_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    *outCell = new cellFa_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["WIDTH"].get<json::number_unsigned_t>());

    for (int i = 0; i < (*outCell)->width; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "A", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->a.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionInput, "B", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->b.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionInput, "C", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->c.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionOutput, "X", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->x.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionOutput, "Y", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->y.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellFsm_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    port_t *clkPort = createPort(inJ, DirectionInput, "CLK", inModule);
    port_t *arstPort = createPort(inJ, DirectionInput, "ARST", inModule);

    *outCell = new cellFsm_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["CLK_POLARITY"].get<json::number_unsigned_t>(),
        inJ["parameters"]["ARST_POLARITY"].get<json::number_unsigned_t>(),
        inJ["parameters"]["CTRL_IN_WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["CTRL_OUT_WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["STATE_BITS"].get<json::number_unsigned_t>(),
        inJ["parameters"]["STATE_NUM"].get<json::number_unsigned_t>(),
        inJ["parameters"]["STATE_NUM_LOG2"].get<json::number_unsigned_t>(),
        inJ["parameters"]["STATE_RST"].get<json::number_unsigned_t>(),
        inJ["parameters"]["STATE_TABLE"].get<json::number_unsigned_t>(),
        inJ["parameters"]["TRANS_NUM"].get<json::number_unsigned_t>(),
        inJ["parameters"]["TRANS_TABLE"].get<json::number_unsigned_t>(),
        *clkPort,
        *arstPort);

    for (int i = 0; i < (*outCell)->ctrlInWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "CTRL_IN", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->ctrlIn.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->ctrlOutWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionOutput, "CTRL_OUT", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->ctrlOut.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellInitState_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    port_t *yPort = createPort(inJ, DirectionInput, "Y", inModule);
    *outCell = new cellInitState_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        *yPort);
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellLcu_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    port_t *ciPort = createPort(inJ, DirectionInput, "CI", inModule);

    *outCell = new cellLcu_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["WIDTH"].get<json::number_unsigned_t>(),
        *ciPort);
    for (int i = 0; i < (*outCell)->width; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "P", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->p.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionInput, "G", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->g.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionInput, "CO", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->co.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, const cellType_t inCellType, module_t *inModule, cellAY_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    *outCell = new cellAY_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inCellType,
        inJ["parameters"]["A_SIGNED"].get<json::number_unsigned_t>(),
        inJ["parameters"]["A_WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["Y_WIDTH"].get<json::number_unsigned_t>());

    for (int i = 0; i < (*outCell)->aWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "A", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->a.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->yWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionOutput, "Y", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->y.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellLut_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    port_t *yPort = createPort(inJ, DirectionInput, "Y", inModule);

    *outCell = new cellLut_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["LUT"].get<json::number_unsigned_t>(),
        *yPort);

    for (int i = 0; i < (*outCell)->width; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "A", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->a.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellMacc_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    *outCell = new cellMacc_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["A_WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["B_WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["Y_WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["CONFIG"].get<json::number_unsigned_t>(),
        inJ["parameters"]["CONFIG_WIDTH"].get<json::number_unsigned_t>());

    for (int i = 0; i < (*outCell)->aWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "A", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->a.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->bWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "B", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->b.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->yWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionOutput, "Y", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->y.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellMem_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    *outCell = new cellMem_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["MEMID"].get<json::number_unsigned_t>(),
        inJ["parameters"]["SIZE"].get<json::number_integer_t>(),
        inJ["parameters"]["OFFSET"].get<json::number_integer_t>(),
        inJ["parameters"]["ABITS"].get<json::number_integer_t>(),
        inJ["parameters"]["WIDTH"].get<json::number_integer_t>(),
        inJ["parameters"]["INIT"].get<json::number_integer_t>(),
        inJ["parameters"]["RD_PORTS"].get<json::number_integer_t>(),
        inJ["parameters"]["RD_CLK_ENABLE"].get<json::number_unsigned_t>(),
        inJ["parameters"]["RD_CLK_POLARITY"].get<json::number_unsigned_t>(),
        inJ["parameters"]["RD_TRANSPARENT"].get<json::number_unsigned_t>(),
        inJ["parameters"]["WR_PORTS"].get<json::number_integer_t>(),
        inJ["parameters"]["WR_CLK_ENABLE"].get<json::number_unsigned_t>(),
        inJ["parameters"]["WR_CLK_POLARITY"].get<json::number_unsigned_t>());

    for (int i = 0; i < (*outCell)->rdPorts; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "RD_CLK", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->rdClk.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionInput, "RD_EN", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->rdEn.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->rdPorts * (*outCell)->aBits; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "RD_ADDR", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->rdAddr.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->rdPorts * (*outCell)->width; i++)
    {
        port_t *newPort = createPort(inJ, DirectionOutput, "RD_DATA", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->rdData.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->wrPorts; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "WR_CLK", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->wrClk.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->wrPorts * (*outCell)->aBits; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "WR_ADDR", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->wrAddr.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->rdPorts * (*outCell)->width; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "WR_DATA", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->wrData.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionInput, "WR_EN", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->wrEn.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellMemInit_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    *outCell = new cellMemInit_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["MEMID"].get<json::number_unsigned_t>(),
        inJ["parameters"]["ABITS"].get<json::number_unsigned_t>(),
        inJ["parameters"]["WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["WORDS"].get<json::number_unsigned_t>(),
        inJ["parameters"]["PRIORITY"].get<json::number_unsigned_t>());

    for (int i = 0; i < (*outCell)->aBits; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "ADDR", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->addr.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->words * (*outCell)->width; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "DATA", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->data.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellMemRd_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    port_t *clkPort = createPort(inJ, DirectionInput, "CLK", inModule);
    port_t *enPort = createPort(inJ, DirectionInput, "EN", inModule);

    *outCell = new cellMemRd_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["MEMID"].get<json::number_unsigned_t>(),
        inJ["parameters"]["ABITS"].get<json::number_unsigned_t>(),
        inJ["parameters"]["WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["CLK_ENABLE"].get<json::number_unsigned_t>(),
        inJ["parameters"]["CLK_POLARITY"].get<json::number_unsigned_t>(),
        inJ["parameters"]["TRANSPARENT"].get<json::number_unsigned_t>(),
        *clkPort,
        *enPort);

    for (int i = 0; i < (*outCell)->aBits; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "ADDR", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->addr.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->width; i++)
    {
        port_t *newPort = createPort(inJ, DirectionOutput, "DATA", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->data.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellMemWr_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    port_t *clkPort = createPort(inJ, DirectionInput, "CLK", inModule);

    *outCell = new cellMemWr_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["MEMID"].get<json::number_unsigned_t>(),
        inJ["parameters"]["ABITS"].get<json::number_unsigned_t>(),
        inJ["parameters"]["WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["CLK_ENABLE"].get<json::number_unsigned_t>(),
        inJ["parameters"]["CLK_POLARITY"].get<json::number_unsigned_t>(),
        inJ["parameters"]["TRANSPARENT"].get<json::number_unsigned_t>(),
        *clkPort);

    for (int i = 0; i < (*outCell)->aBits; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "ADDR", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->addr.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->width; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "DATA", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->data.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionInput, "EN", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->en.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellMux_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    port_t *sPort = createPort(inJ, DirectionInput, "S", inModule);

    *outCell = new cellMux_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["WIDTH"].get<json::number_unsigned_t>(),
        *sPort);

    for (int i = 0; i < (*outCell)->width; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "A", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->a.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionInput, "B", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->b.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionOutput, "Y", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->y.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellPMux_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    *outCell = new cellPMux_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["S_WIDTH"].get<json::number_unsigned_t>());

    for (int i = 0; i < (*outCell)->width; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "A", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->a.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionOutput, "Y", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->y.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->sWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "S", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->s.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->sWidth * (*outCell)->width; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "B", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->b.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellSlice_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    *outCell = new cellSlice_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["OFFSET"].get<json::number_unsigned_t>(),
        inJ["parameters"]["A_WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["Y_WIDTH"].get<json::number_unsigned_t>());

    for (int i = 0; i < (*outCell)->aWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "A", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->a.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->yWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionOutput, "Y", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->y.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellSop_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    port_t *yPort = createPort(inJ, DirectionInput, "Y", inModule);

    *outCell = new cellSop_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["DEPTH"].get<json::number_unsigned_t>(),
        *yPort);

    int tableSize = (*outCell)->width * (*outCell)->depth;
    (*outCell)->table = new unsigned int[tableSize];

    for (int i = 0; i < tableSize; i++)
    {
        (*outCell)->table[i] = inJ["parameters"]["TABLE"].at(i);
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellSpecify2_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    port_t *enPort = createPort(inJ, DirectionInput, "EN", inModule);

    *outCell = new cellSpecify2_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        TypeSpecify2,
        inJ["parameters"]["FULL"].get<json::number_unsigned_t>(),
        inJ["parameters"]["SRC_WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["DST_WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["SRC_DST_PEN"].get<json::number_unsigned_t>(),
        inJ["parameters"]["SRC_DST_POL"].get<json::number_unsigned_t>(),
        inJ["parameters"]["T_RISE_MIN"].get<json::number_unsigned_t>(),
        inJ["parameters"]["T_RISE_TYP"].get<json::number_unsigned_t>(),
        inJ["parameters"]["T_RISE_MAX"].get<json::number_unsigned_t>(),
        inJ["parameters"]["T_FALL_MIN"].get<json::number_unsigned_t>(),
        inJ["parameters"]["T_FALL_TYP"].get<json::number_unsigned_t>(),
        inJ["parameters"]["T_FALL_MAX"].get<json::number_unsigned_t>(),
        *enPort);

    for (int i = 0; i < (*outCell)->srcWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "SRC", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->src.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->dstWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "DST", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->dst.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellSpecify3_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    port_t *enPort = createPort(inJ, DirectionInput, "EN", inModule);

    *outCell = new cellSpecify3_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        TypeSpecify3,
        inJ["parameters"]["FULL"].get<json::number_unsigned_t>(),
        inJ["parameters"]["SRC_WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["DST_WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["SRC_DST_PEN"].get<json::number_unsigned_t>(),
        inJ["parameters"]["SRC_DST_POL"].get<json::number_unsigned_t>(),
        inJ["parameters"]["T_RISE_MIN"].get<json::number_unsigned_t>(),
        inJ["parameters"]["T_RISE_TYP"].get<json::number_unsigned_t>(),
        inJ["parameters"]["T_RISE_MAX"].get<json::number_unsigned_t>(),
        inJ["parameters"]["T_FALL_MIN"].get<json::number_unsigned_t>(),
        inJ["parameters"]["T_FALL_TYP"].get<json::number_unsigned_t>(),
        inJ["parameters"]["T_FALL_MAX"].get<json::number_unsigned_t>(),
        inJ["parameters"]["EDGE_EN"].get<json::number_unsigned_t>(),
        inJ["parameters"]["EDGE_POL"].get<json::number_unsigned_t>(),
        inJ["parameters"]["DAT_DST_PEN"].get<json::number_unsigned_t>(),
        inJ["parameters"]["DAT_DST_POL"].get<json::number_unsigned_t>(),
        *enPort);

    for (int i = 0; i < (*outCell)->srcWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "SRC", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->src.push_back(*newPort);
        }
    }
    for (int i = 0; i < (*outCell)->dstWidth; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "DST", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->dst.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionInput, "DAT", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->dat.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellTriBuf_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    port_t *enPort = createPort(inJ, DirectionInput, "EN", inModule);

    *outCell = new cellTriBuf_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["WIDTH"].get<json::number_unsigned_t>(),
        *enPort);

    for (int i = 0; i < (*outCell)->width; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "A", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->a.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionOutput, "Y", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->y.push_back(*newPort);
        }
    }
}

void cellFromYosysJson(json &inJ, const std::string inCellName, module_t *inModule, cellSr_t **outCell)
{
    assert(inModule != NULL);
    assert(outCell != NULL);
    assert(*outCell == NULL);

    *outCell = new cellSr_t(
        inCellName,
        inJ["hide_name"].get<json::number_unsigned_t>() == 1 ? true : false,
        inJ["parameters"]["WIDTH"].get<json::number_unsigned_t>(),
        inJ["parameters"]["SET_POLARITY"].get<json::number_unsigned_t>(),
        inJ["parameters"]["CLR_POLARITY"].get<json::number_unsigned_t>());
    for (int i = 0; i < (*outCell)->width; i++)
    {
        port_t *newPort = createPort(inJ, DirectionInput, "SET", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->set.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionInput, "CLR", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->clr.push_back(*newPort);
        }
        newPort = createPort(inJ, DirectionOutput, "Q", inModule, i);
        if (newPort != NULL)
        {
            (*outCell)->q.push_back(*newPort);
        }
    }
}