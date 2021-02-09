
#include <string>
#include <vector>
#include <iostream>

#include "localExceptions.h"
#include "cell.h"
#include "module.h"
#include "processing.h"
#include "yosysJson.h"

using namespace std;

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

string getCellType(const cellType_t inType)
{
    switch (inType)
    {
    case TypeAdd:
    {
        return "$add";
        break;
    }
    case TypeAdff:
    {
        return "$adff";
        break;
    }
    case TypeAllConst:
    {
        return "$allconst";
        break;
    }
    case TypeAllSeq:
    {
        return "$allseq";
        break;
    }
    case TypeAlu:
    {
        return "$alu";
        break;
    }
    case TypeAnd:
    {
        return "$and";
        break;
    }
    case TypeAnyConst:
    {
        return "$anyconst";
        break;
    }
    case TypeAnySeq:
    {
        return "$anyseq";
        break;
    }
    case TypeAssert:
    {
        return "$assert";
        break;
    }
    case TypeAssume:
    {
        return "$assume";
        break;
    }
    case TypeConcat:
    {
        return "$concat";
        break;
    }
    case TypeCover:
    {
        return "$cover";
        break;
    }
    case TypeDff:
    {
        return "$dff";
        break;
    }
    case TypeDffe:
    {
        return "$dffe";
        break;
    }
    case TypeDffsr:
    {
        return "$dffsr";
        break;
    }
    case TypeDiv:
    {
        return "$div";
        break;
    }
    case TypeDLatch:
    {
        return "$dlatch";
        break;
    }
    case TypeDLatchSR:
    {
        return "$dlatchsr";
        break;
    }
    case TypeEq:
    {
        return "$eq";
        break;
    }
    case TypeEquiv:
    {
        return "$equiv";
        break;
    }
    case TypeEqx:
    {
        return "$eqx";
        break;
    }
    case TypeFa:
    {
        return "$fa";
        break;
    }
    case TypeFair:
    {
        return "$fair";
        break;
    }
    case TypeFf:
    {
        return "$ff";
        break;
    }
    case TypeFsm:
    {
        return "$fsm";
        break;
    }
    case TypeGe:
    {
        return "$ge";
        break;
    }
    case TypeGt:
    {
        return "$gt";
        break;
    }
    case TypeInitState:
    {
        return "$initstate";
        break;
    }
    case TypeLcu:
    {
        return "$lcu";
        break;
    }
    case TypeLe:
    {
        return "$le";
        break;
    }
    case TypeLive:
    {
        return "$live";
        break;
    }
    case TypeLogicAnd:
    {
        return "$logic_and";
        break;
    }
    case TypeLogicNot:
    {
        return "$logic_not";
        break;
    }
    case TypeLogicOr:
    {
        return "$logic_or";
        break;
    }
    case TypeLt:
    {
        return "$lt";
        break;
    }
    case TypeLut:
    {
        return "$lut";
        break;
    }
    case TypeMacc:
    {
        return "$macc";
        break;
    }
    case TypeMem:
    {
        return "$mem";
        break;
    }
    case TypeMemInit:
    {
        return "$meminit";
        break;
    }
    case TypeMemRd:
    {
        return "$memrd";
        break;
    }
    case TypeMemWr:
    {
        return "$memwr";
        break;
    }
    case TypeMod:
    {
        return "$mod";
        break;
    }
    case TypeMul:
    {
        return "$mul";
        break;
    }
    case TypeMux:
    {
        return "$mux";
        break;
    }
    case TypeNe:
    {
        return "$ne";
        break;
    }
    case TypeNeg:
    {
        return "$neg";
        break;
    }
    case TypeNex:
    {
        return "$nex";
        break;
    }
    case TypeNot:
    {
        return "$not";
        break;
    }
    case TypeOr:
    {
        return "$or";
        break;
    }
    case TypePMux:
    {
        return "$pmux";
        break;
    }
    case TypePos:
    {
        return "$pos";
        break;
    }
    case TypePow:
    {
        return "$pow";
        break;
    }
    case TypeReduceAnd:
    {
        return "$reduce_and";
        break;
    }
    case TypeReduceBool:
    {
        return "$reduce_bool";
        break;
    }
    case TypeReduceOr:
    {
        return "$reduce_or";
        break;
    }
    case TypeReduceXnor:
    {
        return "$reduce_xnor";
        break;
    }
    case TypeReduceXor:
    {
        return "$reduce_xor";
        break;
    }
    case TypeShift:
    {
        return "$shift";
        break;
    }
    case TypeShiftX:
    {
        return "$shiftx";
        break;
    }
    case TypeShl:
    {
        return "$shl";
        break;
    }
    case TypeShr:
    {
        return "$shr";
        break;
    }
    case TypeSlice:
    {
        return "$slice";
        break;
    }
    case TypeSop:
    {
        return "$sop";
        break;
    }
    case TypeSpecify2:
    {
        return "$specify2";
        break;
    }
    case TypeSpecify3:
    {
        return "$specify3";
        break;
    }
    case TypeSpecRule:
    {
        return "$specrule";
        break;
    }
    case TypeSr:
    {
        return "$sr";
        break;
    }
    case TypeSshl:
    {
        return "$sshl";
        break;
    }
    case TypeSshr:
    {
        return "$sshr";
        break;
    }
    case TypeSub:
    {
        return "$sub";
        break;
    }
    case TypeTriBuf:
    {
        return "$tribuf";
        break;
    }
    case TypeXnor:
    {
        return "$xnor";
        break;
    }
    case TypeXor:
    {
        return "$xor";
        break;
    }
    default:
    {
        return "unknown";
        break;
    }
    }
}

void createPortsFromJson(json &inPorts, json &inNets, module_t &inModule, int &portNumber, vector<port_t> &inOutPorts)
{
    json::iterator it = inPorts.begin();
    while (it != inPorts.end())
    {
        direction_t dir = (*it)["direction"] == "Output" ? DirectionOutput : (*it)["direction"] == "Input" ? DirectionInput : DirectionInOut;
        string netName = string((*it)["net"]);
        port_t *newPort = NULL;
        if ("net_000" == netName)
        {
            newPort = new port_t(dir, portNumber++, 0);
        }
        else if ("net_001" == netName)
        {
            newPort = new port_t(dir, portNumber++, 1);
        }
        else
        {
            newPort = new port_t(dir, portNumber++, inNets[netName]["bitId"]);
        }
        if (NULL != newPort)
        {
            inOutPorts.push_back(*newPort);
        }
        it++;
    }
}

void createPortFromJson(json &inPort, json &inNets, module_t &inModule, int &portNumber, port_t *outPort)
{
    json::iterator it = inPort.begin();
        direction_t dir = (*it)["direction"] == "Output" ? DirectionOutput : (*it)["direction"] == "Input" ? DirectionInput : DirectionInOut;
        string netName = string((*it)["net"]);
        outPort = NULL;
        if ("net_000" == netName)
        {
            outPort = new port_t(dir, portNumber++, 0);
        }
        else if ("net_001" == netName)
        {
            outPort = new port_t(dir, portNumber++, 1);
        }
        else
        {
            outPort = new port_t(dir, portNumber++, inNets[netName]["bitId"]);
        }
        
}

void fillPortIntoJson(json &inJson, port_t &port)
{
    string tempId = port.portRefId < 10 ? "00" + to_string(port.portRefId) : port.portRefId < 100 ? "0" + to_string(port.portRefId) : to_string(port.portRefId);
    string tempName = "cellPort_" + tempId;
    inJson[tempName] = port.storeInJson();
}

void fillPortsIntoJson(json &inJson, vector<port_t> &ports)
{
    if (ports.empty() == false)
    {
        vector<port_t>::iterator it = ports.begin();
        while (it != ports.end())
        {
            string tempId = it->portRefId < 10 ? "00" + to_string(it->portRefId) : it->portRefId < 100 ? "0" + to_string(it->portRefId) : to_string(it->portRefId);
            string tempName = "cellPort_" + tempId;
            inJson[tempName] = it->storeInJson();
            it++;
        }
    }
}

json cell_t::storeInJson()
{
    json description;
    switch (this->type)
    {
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
        description = ((cellArithmetic_t *)this)->storeAdditionalInJson();
    }
    case TypeDff:
    {
        description = ((cellDFlipFlop_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeDffe:
    {
        description = ((cellDFlipFlopEnable_t *)this)->storeAdditionalInJson();
        break;
    }
    // Cells with port (CLK, SET, CLR, D, Q)
    case TypeDffsr:
    {
        description = ((cellDFlipFlopSetReset_t *)this)->storeAdditionalInJson();
        break;
    }
    // Cells for flipflops with global clock
    case TypeFf:
    {
        description = ((cellFlipFlop_t *)this)->storeAdditionalInJson();
        break;
    }
    // Cells with port (EN, D, Q)
    case TypeDLatch:
    {
        description = ((cellDLatch_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeDLatchSR:
    {
        description = ((cellDLatchSR_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeAdff:
    {
        description = ((cellAdff_t *)this)->storeAdditionalInJson();
        break;
    }
    // Cells for constant expressions
    case TypeAllConst:
    case TypeAllSeq:
    case TypeAnyConst:
    case TypeAnySeq:
    {
        description = ((cellConstAssign_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeAlu:
    {
        description = ((cellAlu_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeAssert:
    case TypeAssume:
    case TypeCover:
    case TypeFair:
    case TypeLive:
    {
        description = ((cellAEn_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeConcat:
    {
        description = ((cellConcat_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeEquiv:
    {
        description = ((cellEquiv_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeFsm:
    {
        description = ((cellFsm_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeInitState:
    {
        description = ((cellInitState_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeLcu:
    {
        description = ((cellLcu_t *)this)->storeAdditionalInJson();
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
        description = ((cellAY_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeLut:
    {
        description = ((cellLut_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeMacc:
    {
        description = ((cellMacc_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeMem:
    {
        description = ((cellMem_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeMemInit:
    {
        description = ((cellMemInit_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeMemRd:
    {
        description = ((cellMemRd_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeMemWr:
    {
        description = ((cellMemWr_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeMux:
    {
        description = ((cellMux_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypePMux:
    {
        description = ((cellPMux_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeSlice:
    {
        description = ((cellSlice_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeSop:
    {
        description = ((cellSop_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeSpecify2:
    {
        description = ((cellSpecify2_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeSpecify3:
    {
        description = ((cellSpecify3_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeTriBuf:
    {
        description = ((cellTriBuf_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeSr:
    {
        description = ((cellSr_t *)this)->storeAdditionalInJson();
        break;
    }
    case TypeUnknown:
    default:
    {
        break;
    }
    }
    description["name"] = this->name;
    description["type"] = getCellType(this->type);
    description["hide_name"] = this->hideName;
    description["attributes"] = json(this->attributes);
    return description;
}

cell_t *cell_t::createFromJson(json &inJ, json &inNets, module_t &inModule)
{
    cell_t *newCell = NULL;
    cellType_t type = getCellType(inJ["type"].dump());
    cout << "Type: " << inJ["type"].dump() << " Val " << type << endl;
    switch (type)
    {
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
        newCell = cellArithmetic_t::createAdditionalFromJson(inJ, inNets, inModule, type);
        break;
    }
    case TypeDff:
    {
        newCell = cellDFlipFlop_t::createAdditionalFromJson(inJ, inNets, inModule, type);
        break;
    }
    /*case TypeDffe:
    {
        description = ((cellDFlipFlopEnable_t*)this)->storeAdditionalInJson();
        break;
    }
    // Cells with port (CLK, SET, CLR, D, Q)
    case TypeDffsr:
    {
       description = ((cellDFlipFlopSetReset_t*)this)->storeAdditionalInJson();
       break;
    }
    // Cells for flipflops with global clock
    case TypeFf:
    {
        description = ((cellFlipFlop_t*)this)->storeAdditionalInJson();
        break;
    }
    // Cells with port (EN, D, Q)
    case TypeDLatch:
    {
        description = ((cellDLatch_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeDLatchSR:
    {
        description = ((cellDLatchSR_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeAdff:
    {
        description = ((cellAdff_t*)this)->storeAdditionalInJson();
        break;
    }
    // Cells for constant expressions
    case TypeAllConst:
    case TypeAllSeq:
    case TypeAnyConst:
    case TypeAnySeq:
    {
        description = ((cellConstAssign_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeAlu:
    {
        description = ((cellAlu_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeAssert:
    case TypeAssume:
    case TypeCover:
    case TypeFair:
    case TypeLive:
    {
        description = ((cellAEn_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeConcat:
    {
        description = ((cellConcat_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeEquiv:
    {
        description = ((cellEquiv_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeFsm:
    {
        description = ((cellFsm_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeInitState:
    {
        description = ((cellInitState_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeLcu:
    {
        description = ((cellLcu_t*)this)->storeAdditionalInJson();
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
        description = ((cellAY_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeLut:
    {
        description = ((cellLut_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeMacc:
    {
        description = ((cellMacc_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeMem:
    {
        description = ((cellMem_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeMemInit:
    {
        description = ((cellMemInit_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeMemRd:
    {
        description = ((cellMemRd_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeMemWr:
    {
        description = ((cellMemWr_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeMux:
    {
        description = ((cellMux_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypePMux:
    {
        description = ((cellPMux_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeSlice:
    {
        description = ((cellSlice_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeSop:
    {
        description = ((cellSop_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeSpecify2:
    {
        description = ((cellSpecify2_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeSpecify3:
    {
        description = ((cellSpecify3_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeTriBuf:
    {
        description = ((cellTriBuf_t*)this)->storeAdditionalInJson();
        break;
    }
    case TypeSr:
    {
        description = ((cellSr_t*)this)->storeAdditionalInJson();
        break;
    }*/
    case TypeUnknown:
    default:
    {
        return NULL;
        break;
    }
    }

    json::iterator it = inJ["attributes"].begin();
    while (it != inJ["attributes"].end())
    {
        newCell->attributes.push_back(make_pair(string(it->at(0)), string(it->at(1))));
        it++;
    }
    return newCell;
}

json cellArithmetic_t::storeAdditionalInJson()
{
    json description;
    description["parameters"]["A_SIGNED"] = this->aSigned;
    description["parameters"]["B_SIGNED"] = this->bSigned;
    description["parameters"]["A_WIDTH"] = this->aWidth;
    description["parameters"]["B_WIDTH"] = this->bWidth;
    description["parameters"]["Y_WIDTH"] = this->yWidth;
    fillPortsIntoJson(description["ports"]["A"], this->a);
    fillPortsIntoJson(description["ports"]["B"], this->b);
    fillPortsIntoJson(description["ports"]["Y"], this->y);

    return description;
}

cell_t *cellArithmetic_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule, const cellType_t type)
{
    cellArithmetic_t *newCell = new cellArithmetic_t(
        inJ["name"],
        inJ["hide_name"],
        type,
        inJ["parameters"]["A_SIGNED"],
        inJ["parameters"]["B_SIGNED"],
        inJ["parameters"]["A_WIDTH"],
        inJ["parameters"]["B_WIDTH"],
        inJ["parameters"]["Y_WIDTH"]);
    int numberOfPorts = 1;
    createPortsFromJson(inJ["ports"]["A"], inNets, inModule, numberOfPorts, newCell->a);
    createPortsFromJson(inJ["ports"]["B"], inNets, inModule, numberOfPorts, newCell->b);
    createPortsFromJson(inJ["ports"]["Y"], inNets, inModule, numberOfPorts, newCell->y);

    return (cell_t *)newCell;
}

json cellDFlipFlop_t::storeAdditionalInJson()
{

    json description;
    description["parameters"]["WIDTH"] = this->width;
    description["parameters"]["CLK_POLARITY"] = this->clkPolarity;
    fillPortIntoJson(description["ports"]["CLK"], this->clk);
    fillPortsIntoJson(description["ports"]["D"], this->d);
    fillPortsIntoJson(description["ports"]["Q"], this->q);

    return description;
}

cell_t * cellDFlipFlop_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule, const cellType_t type){

    int numberOfPorts = 1;
    port_t *clkPort;
    createPortFromJson(inJ["ports"]["CLK"], inNets, inModule, numberOfPorts, clkPort);
    cellDFlipFlop_t *newCell = new cellDFlipFlop_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["WIDTH"],
        inJ["parameters"]["CLK_POLARITY"],
        type,
        *clkPort 
    );
    createPortsFromJson(inJ["ports"]["Q"], inNets, inModule, numberOfPorts, newCell->q);
    createPortsFromJson(inJ["ports"]["D"], inNets, inModule, numberOfPorts, newCell->d);

    return (cell_t*) newCell;
}

json cellDFlipFlopEnable_t::storeAdditionalInJson()
{

    json description;
    description = ((cellDFlipFlop_t *)this)->storeAdditionalInJson();
    description["parameters"]["EN_POLARITY"] = this->enPolarity;
    fillPortIntoJson(description["ports"]["EN"], this->en);

    return description;
}

cell_t * cellDFlipFlopEnable_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule, const cellType_t type){
    int numberOfPorts = 1;
    port_t *clkPort;
    createPortFromJson(inJ["ports"]["CLK"], inNets, inModule, numberOfPorts, clkPort);
    port_t *enPort;
    createPortFromJson(inJ["ports"]["EN"], inNets, inModule, numberOfPorts, enPort);
    cellDFlipFlopEnable_t *newCell = new cellDFlipFlopEnable_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["WIDTH"],
        inJ["parameters"]["CLK_POLARITY"],
        inJ["parameters"]["EN_POLARITY"],
        type,
        *clkPort,
        *enPort
    );
    createPortsFromJson(inJ["ports"]["Q"], inNets, inModule, numberOfPorts, newCell->q);
    createPortsFromJson(inJ["ports"]["D"], inNets, inModule, numberOfPorts, newCell->d);

    return (cell_t*) newCell;
}

json cellDFlipFlopSetReset_t::storeAdditionalInJson()
{

    json description;
    description = ((cellDFlipFlop_t *)this)->storeAdditionalInJson();
    description["parameters"]["SET_POLARITY"] = this->setPolarity;
    description["parameters"]["CLR_POLARITY"] = this->clrPolarity;
    fillPortsIntoJson(description["ports"]["SET"], this->set);
    fillPortsIntoJson(description["ports"]["CLR"], this->clr);

    return description;
}

cell_t * cellDFlipFlopSetReset_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule, const cellType_t type){

    int numberOfPorts = 1;
    port_t *clkPort;
    createPortFromJson(inJ["ports"]["CLK"], inNets, inModule, numberOfPorts, clkPort);

    cellDFlipFlopSetReset_t *newCell = new cellDFlipFlopSetReset_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["WIDTH"],
        inJ["parameters"]["CLK_POLARITY"],
        inJ["parameters"]["SET_POLARITY"],
        inJ["parameters"]["CLR_POLARITY"],
        type,
        *clkPort 
    );

    createPortsFromJson(inJ["ports"]["Q"], inNets, inModule, numberOfPorts, newCell->q);
    createPortsFromJson(inJ["ports"]["D"], inNets, inModule, numberOfPorts, newCell->d);
    createPortsFromJson(inJ["ports"]["SET"], inNets, inModule, numberOfPorts, newCell->set);
    createPortsFromJson(inJ["ports"]["CLR"], inNets, inModule, numberOfPorts, newCell->clr);

    return (cell_t*) newCell;
}

json cellAdff_t::storeAdditionalInJson()
{
    json description;
    description = ((cellDFlipFlop_t *)this)->storeAdditionalInJson();
    description["parameters"]["ARST_POLARITY"] = this->arstPolarity;
    description["parameters"]["ARST_VALUE"] = this->arstValue;
    fillPortIntoJson(description["ports"]["ARST"], this->arst);

    return description;
}

cell_t * cellAdff_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule){

    int numberOfPorts = 1;
    port_t *clkPort;
    createPortFromJson(inJ["ports"]["CLK"], inNets, inModule, numberOfPorts, clkPort);
    port_t *arstPort;
    createPortFromJson(inJ["ports"]["ARST"], inNets, inModule, numberOfPorts, arstPort);
    cellAdff_t *newCell = new cellAdff_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["WIDTH"],
        inJ["parameters"]["CLK_POLARITY"],
        inJ["parameters"]["ARST_POLARITY"],
        inJ["parameters"]["ARST_VALUE"],
        *clkPort,
        *arstPort
    );
    createPortsFromJson(inJ["ports"]["Q"], inNets, inModule, numberOfPorts, newCell->q);
    createPortsFromJson(inJ["ports"]["D"], inNets, inModule, numberOfPorts, newCell->d);

    return (cell_t*) newCell;
}

json cellFlipFlop_t::storeAdditionalInJson()
{

    json description;
    description["parameters"]["WIDTH"] = this->width;
    fillPortsIntoJson(description["ports"]["D"], this->d);
    fillPortsIntoJson(description["ports"]["Q"], this->q);

    return description;
}

cell_t * cellFlipFlop_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule){

    int numberOfPorts = 1;
    cellFlipFlop_t *newCell = new cellFlipFlop_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["WIDTH"]
    );
    createPortsFromJson(inJ["ports"]["Q"], inNets, inModule, numberOfPorts, newCell->q);
    createPortsFromJson(inJ["ports"]["D"], inNets, inModule, numberOfPorts, newCell->d);

    return (cell_t*) newCell;
}

json cellDLatch_t::storeAdditionalInJson()
{

    json description;
    description["parameters"]["WIDTH"] = this->width;
    description["parameters"]["EN_POLARITY"] = this->enPolarity;
    fillPortIntoJson(description["ports"]["EN"], this->en);
    fillPortsIntoJson(description["ports"]["D"], this->d);
    fillPortsIntoJson(description["ports"]["Q"], this->q);

    return description;
}

cell_t * cellDLatch_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule, const cellType_t type){

    int numberOfPorts = 1;
    port_t *enPort;
    createPortFromJson(inJ["ports"]["EN"], inNets, inModule, numberOfPorts, enPort);

    cellDLatch_t *newCell = new cellDLatch_t(
        inJ["name"],
        inJ["hide_name"],
        type,
        inJ["parameters"]["WIDTH"],
        inJ["parameters"]["EN_POLARITY"],
        *enPort
    );

    createPortsFromJson(inJ["ports"]["Q"], inNets, inModule, numberOfPorts, newCell->q);
    createPortsFromJson(inJ["ports"]["D"], inNets, inModule, numberOfPorts, newCell->d);

    return (cell_t*) newCell;
}

json cellDLatchSR_t::storeAdditionalInJson()
{

    json description;
    description = ((cellDLatch_t*) this)->storeAdditionalInJson();
    description["parameters"]["SET_POLARITY"] = this->setPolarity;
    description["parameters"]["CLR_POLARITY"] = this->clrPolarity;
    fillPortsIntoJson(description["ports"]["SET"], this->set);
    fillPortsIntoJson(description["ports"]["CLR"], this->clr);

    return description;
}

cell_t * cellDLatchSR_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule, const cellType_t type){

    int numberOfPorts = 1;
    port_t *enPort;
    createPortFromJson(inJ["ports"]["EN"], inNets, inModule, numberOfPorts, enPort);

    cellDLatchSR_t *newCell = new cellDLatchSR_t(
        inJ["name"],
        inJ["hide_name"],
        type,
        inJ["parameters"]["WIDTH"],
        inJ["parameters"]["EN_POLARITY"],
        inJ["parameters"]["SET_POLARITY"],
        inJ["parameters"]["CLR_POLARITY"],
        *enPort
    );

    createPortsFromJson(inJ["ports"]["Q"], inNets, inModule, numberOfPorts, newCell->q);
    createPortsFromJson(inJ["ports"]["D"], inNets, inModule, numberOfPorts, newCell->d);
    createPortsFromJson(inJ["ports"]["SET"], inNets, inModule, numberOfPorts, newCell->set);
    createPortsFromJson(inJ["ports"]["CLR"], inNets, inModule, numberOfPorts, newCell->clr);

    return (cell_t*) newCell;
}

json cellConstAssign_t::storeAdditionalInJson()
{

    json description;
    description["parameters"]["WIDTH"] = this->width;
    fillPortsIntoJson(description["ports"]["Y"], this->y);

    return description;
}

cell_t * cellConstAssign_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule, const cellType_t type){

    int numberOfPorts = 1;

    cellConstAssign_t *newCell = new cellConstAssign_t(
        inJ["name"],
        inJ["hide_name"],
        type,
        inJ["parameters"]["WIDTH"]
    );
    createPortsFromJson(inJ["ports"]["Y"], inNets, inModule, numberOfPorts, newCell->y);

    return (cell_t*) newCell;
}

json cellAlu_t::storeAdditionalInJson()
{

    json description;
    description = ((cellArithmetic_t*) this)->storeAdditionalInJson();
    fillPortIntoJson(description["ports"]["CI"], this->ci);
    fillPortIntoJson(description["ports"]["BI"], this->bi);
    fillPortsIntoJson(description["ports"]["X"], this->x);
    fillPortsIntoJson(description["ports"]["CO"], this->co);

    return description;
}

cell_t * cellAlu_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule){

    int numberOfPorts = 1;
    port_t *ciPort;
    createPortFromJson(inJ["ports"]["CI"], inNets, inModule, numberOfPorts, ciPort);
    port_t *biPort;
    createPortFromJson(inJ["ports"]["BI"], inNets, inModule, numberOfPorts, biPort);

    cellAlu_t *newCell = new cellAlu_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["A_SIGNED"],
        inJ["parameters"]["B_SIGNED"],
        inJ["parameters"]["A_WIDTH"],
        inJ["parameters"]["B_WIDTH"],
        inJ["parameters"]["Y_WIDTH"],
        *ciPort,
        *biPort
    );

    createPortsFromJson(inJ["ports"]["A"], inNets, inModule, numberOfPorts, newCell->a);
    createPortsFromJson(inJ["ports"]["B"], inNets, inModule, numberOfPorts, newCell->b);
    createPortsFromJson(inJ["ports"]["Y"], inNets, inModule, numberOfPorts, newCell->y);
    createPortsFromJson(inJ["ports"]["X"], inNets, inModule, numberOfPorts, newCell->x);
    createPortsFromJson(inJ["ports"]["CO"], inNets, inModule, numberOfPorts, newCell->co);
    
    return (cell_t*) newCell;
}

json cellAEn_t::storeAdditionalInJson()
{

    json description;
    fillPortIntoJson(description["ports"]["A"], this->a);
    fillPortIntoJson(description["ports"]["EN"], this->en);

    return description;
}

cell_t * cellAEn_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule, const cellType_t type){
    
    int numberOfPorts = 1;
    port_t *aPort;
    createPortFromJson(inJ["ports"]["A"], inNets, inModule, numberOfPorts, aPort);
    port_t *enPort;
    createPortFromJson(inJ["ports"]["A"], inNets, inModule, numberOfPorts, enPort);

    cellAEn_t *newCell = new cellAEn_t(
        inJ["name"],
        inJ["hide_name"],
        type,
        *aPort,
        *enPort
    );

    return (cell_t*) newCell;
}

json cellConcat_t::storeAdditionalInJson()
{
    json description;
    description["parameters"]["A_WIDTH"] = this->aWidth;
    description["parameters"]["B_WIDTH"] = this->bWidth;
    fillPortsIntoJson(description["ports"]["A"], this->a);
    fillPortsIntoJson(description["ports"]["B"], this->b);
    fillPortsIntoJson(description["ports"]["Y"], this->y);

    return description;
}

cell_t * cellConcat_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule){

    int numberOfPorts = 1;

    cellConcat_t *newCell = new cellConcat_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["A_WIDTH"],
        inJ["parameters"]["B_WIDTH"]
    );

    createPortsFromJson(inJ["ports"]["A"], inNets, inModule, numberOfPorts, newCell->a);
    createPortsFromJson(inJ["ports"]["B"], inNets, inModule, numberOfPorts, newCell->b);
    createPortsFromJson(inJ["ports"]["Y"], inNets, inModule, numberOfPorts, newCell->y);

    return (cell_t*) newCell;
}

json cellEquiv_t::storeAdditionalInJson()
{
    json description;
    fillPortIntoJson(description["ports"]["A"], this->a);
    fillPortIntoJson(description["ports"]["B"], this->b);
    fillPortIntoJson(description["ports"]["Y"], this->y);

    return description;
}

cell_t * cellEquiv_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule){

    int numberOfPorts = 1;
    port_t *aPort;
    createPortFromJson(inJ["ports"]["A"], inNets, inModule, numberOfPorts, aPort);
    port_t *bPort;
    createPortFromJson(inJ["ports"]["B"], inNets, inModule, numberOfPorts, bPort);
    port_t *yPort;
    createPortFromJson(inJ["ports"]["Y"], inNets, inModule, numberOfPorts, yPort);

    cellEquiv_t *newCell = new cellEquiv_t(
        inJ["name"],
        inJ["hide_name"],
        *aPort,
        *bPort,
        *yPort
    );

    return (cell_t*) newCell;
}

json cellFa_t::storeAdditionalInJson()
{
    json description;
    description["parameters"]["WIDTH"] = this->width;
    fillPortsIntoJson(description["ports"]["A"], this->a);
    fillPortsIntoJson(description["ports"]["B"], this->b);
    fillPortsIntoJson(description["ports"]["C"], this->c);
    fillPortsIntoJson(description["ports"]["X"], this->x);
    fillPortsIntoJson(description["ports"]["Y"], this->y);

    return description;
}

cell_t * cellFa_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule){

    int numberOfPorts = 1;

    cellFa_t *newCell = new cellFa_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["WIDTH"]
    );

    createPortsFromJson(inJ["ports"]["A"], inNets, inModule, numberOfPorts, newCell->a);
    createPortsFromJson(inJ["ports"]["B"], inNets, inModule, numberOfPorts, newCell->b);
    createPortsFromJson(inJ["ports"]["C"], inNets, inModule, numberOfPorts, newCell->c);
    createPortsFromJson(inJ["ports"]["X"], inNets, inModule, numberOfPorts, newCell->x);
    createPortsFromJson(inJ["ports"]["Y"], inNets, inModule, numberOfPorts, newCell->y);

    return (cell_t*) newCell;
}

json cellFsm_t::storeAdditionalInJson()
{
    json description;
    description["parameters"]["CLK_POLARITY"] = this->clkPolarity;
    description["parameters"]["ARST_POLARITY"] = this->arstPolarity;
    description["parameters"]["CTRL_IN_WIDTH"] = this->ctrlInWidth;
    description["parameters"]["CTRL_OUT_WIDTH"] = this->ctrlOutWidth;
    description["parameters"]["STATE_BITS"] = this->stateBits;
    description["parameters"]["STATE_NUM"] = this->stateNum;
    description["parameters"]["STATE_NUM_LOG_2"] = this->stateNumLog2;
    description["parameters"]["STATE_RST"] = this->stateRst;
    description["parameters"]["STATE_TABLE"] = this->stateTable;
    description["parameters"]["TRANS_NUM"] = this->transNum;
    description["parameters"]["TRANS_TABLE"] = this->transTable;
    fillPortIntoJson(description["ports"]["CLK"], this->clk);
    fillPortIntoJson(description["ports"]["ARST"], this->arst);
    fillPortsIntoJson(description["ports"]["CTRL_IN"], this->ctrlIn);
    fillPortsIntoJson(description["ports"]["CTRL_OUT"], this->ctrlOut);

    return description;
}

cell_t * cellFsm_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule){

    int numberOfPorts = 1;
    port_t *clkPort;
    createPortFromJson(inJ["ports"]["CLK"], inNets, inModule, numberOfPorts, clkPort);
    port_t *arstPort;
    createPortFromJson(inJ["ports"]["CLK"], inNets, inModule, numberOfPorts, arstPort);

    cellFsm_t *newCell = new cellFsm_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["CLK_POLARITY"],
        inJ["parameters"]["ARST_POLARITY"],
        inJ["parameters"]["CTRL_IN_WIDTH"],
        inJ["parameters"]["CTRL_OUT_WIDTH"],
        inJ["parameters"]["STATE_BITS"],
        inJ["parameters"]["STATE_NUM"],
        inJ["parameters"]["STATE_NUM_LOG_2"],
        inJ["parameters"]["STATE_RST"],
        inJ["parameters"]["STATE_TABLE"],
        inJ["parameters"]["TRANS_NUM"],
        inJ["parameters"]["TRANS_TABLE"],
        *clkPort,
        *arstPort
    );

    createPortsFromJson(inJ["ports"]["CTRL_IN"], inNets, inModule, numberOfPorts, newCell->ctrlIn);
    createPortsFromJson(inJ["ports"]["CTRL_OUT"], inNets, inModule, numberOfPorts, newCell->ctrlOut);

    return (cell_t*) newCell;
}

json cellInitState_t::storeAdditionalInJson()
{

    json description;
    fillPortIntoJson(description["ports"]["Y"], this->y);

    return description;
}

cell_t * cellInitState_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule){

    int numberOfPorts = 1;
    port_t *yPort;
    createPortFromJson(inJ["ports"]["Y"], inNets, inModule, numberOfPorts, yPort);

    cellInitState_t *newCell = new cellInitState_t(
        inJ["name"],
        inJ["hide_name"],
        *yPort
    );

    return (cell_t*) newCell;
}

json cellLcu_t::storeAdditionalInJson()
{
    json description;
    description["parameters"]["WIDTH"] = this->width;
    fillPortIntoJson(description["ports"]["CI"], this->ci);
    fillPortsIntoJson(description["ports"]["P"], this->p);
    fillPortsIntoJson(description["ports"]["G"], this->g);
    fillPortsIntoJson(description["ports"]["CO"], this->co);

    return description;
}

cell_t * cellLcu_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule){

    int numberOfPorts = 1;
    port_t *ciPort;
    createPortFromJson(inJ["ports"]["CI"], inNets, inModule, numberOfPorts, ciPort);

    cellLcu_t *newCell = new cellLcu_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["WIDTH"],
        *ciPort
    );
    createPortsFromJson(inJ["ports"]["P"], inNets, inModule, numberOfPorts, newCell->p);
    createPortsFromJson(inJ["ports"]["G"], inNets, inModule, numberOfPorts, newCell->g);
    createPortsFromJson(inJ["ports"]["CO"], inNets, inModule, numberOfPorts, newCell->co);

    return (cell_t*) newCell;
}

json cellAY_t::storeAdditionalInJson()
{
    json description;
    description["parameters"]["A_SIGNED"] = this->aSigned;
    description["parameters"]["A_WIDTH"] = this->aWidth;
    description["parameters"]["Y_WIDTH"] = this->yWidth;
    fillPortsIntoJson(description["ports"]["A"], this->a);
    fillPortsIntoJson(description["ports"]["Y"], this->y);

    return description;
}

cell_t * cellAY_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule, const cellType_t type){

    int numberOfPorts = 1;

    cellAY_t *newCell = new cellAY_t(
        inJ["name"],
        inJ["hide_name"],
        type,
        inJ["parameters"]["A_SIGNED"],
        inJ["parameters"]["A_WIDTH"],
        inJ["parameters"]["Y_WIDTH"]
    );

    createPortsFromJson(inJ["ports"]["A"], inNets, inModule, numberOfPorts, newCell->a);
    createPortsFromJson(inJ["ports"]["Y"], inNets, inModule, numberOfPorts, newCell->y);

    return (cell_t*) newCell;
}

json cellLut_t::storeAdditionalInJson()
{
    json description;
    description["parameters"]["WIDTH"] = this->width;
    description["parameters"]["LUT"] = this->lut;
    fillPortIntoJson(description["ports"]["Y"], this->y);
    fillPortsIntoJson(description["ports"]["A"], this->a);

    return description;
}

cell_t * cellLut_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule){
    
    int numberOfPorts = 1;
    port_t *yPort;
    createPortFromJson(inJ["ports"]["Y"], inNets, inModule, numberOfPorts, yPort);
    
    cellLut_t * newCell = new cellLut_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["WIDTH"],
        inJ["parameters"]["LUT"],
        *yPort
    );

    createPortsFromJson(inJ["ports"]["A"], inNets, inModule, numberOfPorts, newCell->a);

    return (cell_t*) newCell;
}

json cellMacc_t::storeAdditionalInJson()
{
    json description;
    description["parameters"]["A_WIDTH"] = this->aWidth;
    description["parameters"]["B_WIDTH"] = this->bWidth;
    description["parameters"]["Y_WIDTH"] = this->yWidth;
    description["parameters"]["CONFIG"] = this->config;
    description["parameters"]["CONFIG_WIDTH"] = this->configWidth;
    fillPortsIntoJson(description["ports"]["A"], this->a);
    fillPortsIntoJson(description["ports"]["B"], this->b);
    fillPortsIntoJson(description["ports"]["Y"], this->y);

    return description;
}

cell_t * cellMacc_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule){

    int numberOfPorts = 1;

    cellMacc_t *newCell = new cellMacc_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["A_WIDTH"],
        inJ["parameters"]["B_WIDTH"],
        inJ["parameters"]["Y_WIDTH"],
        inJ["parameters"]["CONFIG"],
        inJ["parameters"]["CONFIG_WIDTH"]
    );

    createPortsFromJson(inJ["ports"]["A"], inNets, inModule, numberOfPorts, newCell->a);
    createPortsFromJson(inJ["ports"]["B"], inNets, inModule, numberOfPorts, newCell->b);
    createPortsFromJson(inJ["ports"]["Y"], inNets, inModule, numberOfPorts, newCell->y);

    return (cell_t*) newCell;
}

json cellMem_t::storeAdditionalInJson()
{
    json description;
    description["parameters"]["MEM_ID"] = this->memId;
    description["parameters"]["SIZE"] = this->size;
    description["parameters"]["OFFSET"] = this->offset;
    description["parameters"]["A_BITS"] = this->aBits;
    description["parameters"]["WIDTH"] = this->width;
    description["parameters"]["INIT"] = this->init;
    description["parameters"]["RD_PORTS"] = this->rdPorts;
    description["parameters"]["RD_CLK_ENABLE"] = this->rdClkEnable;
    description["parameters"]["RD_CLK_POLARITY"] = this->rdClkPolarity;
    description["parameters"]["RD_TRANSPARENT"] = this->rdTransparent;
    description["parameters"]["WR_PORTS"] = this->wrPorts;
    description["parameters"]["WR_CLK_ENABLE"] = this->wrClkEnable;
    description["parameters"]["WR_CLK_POLARITY"] = this->wrClkPolarity;
    fillPortsIntoJson(description["ports"]["RD_CLK"], this->rdClk);
    fillPortsIntoJson(description["ports"]["RD_EN"], this->rdEn);
    fillPortsIntoJson(description["ports"]["RD_ADDR"], this->rdAddr);
    fillPortsIntoJson(description["ports"]["RD_DATA"], this->rdData);
    fillPortsIntoJson(description["ports"]["WR_CLK"], this->wrClk);
    fillPortsIntoJson(description["ports"]["WR_EN"], this->wrEn);
    fillPortsIntoJson(description["ports"]["WR_ADDR"], this->wrAddr);
    fillPortsIntoJson(description["ports"]["WR_DATA"], this->wrData);

    return description;
}

cell_t * cellMem_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule){
    
    int numberOfPorts = 1;
    cellMem_t *newCell = new cellMem_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["MEM_ID"],
        inJ["parameters"]["SIZE"],
        inJ["parameters"]["OFFSET"],
        inJ["parameters"]["ABITS"],
        inJ["parameters"]["WIDTH"],
        inJ["parameters"]["INIT"],
        inJ["parameters"]["RD_PORTS"],
        inJ["parameters"]["RD_CLK_ENABLE"],
        inJ["parameters"]["RD_CLK_POLARITY"],
        inJ["parameters"]["RD_TRANSPARENT"],
        inJ["parameters"]["WR_PORTS"],
        inJ["parameters"]["WR_CLK_ENABLE"],
        inJ["parameters"]["WR_CLK_POLARITY"]
    );

    createPortsFromJson(inJ["ports"]["RD_CLK"], inNets, inModule, numberOfPorts, newCell->rdClk);
    createPortsFromJson(inJ["ports"]["RD_EN"], inNets, inModule, numberOfPorts, newCell->rdEn);
    createPortsFromJson(inJ["ports"]["RD_ADDR"], inNets, inModule, numberOfPorts, newCell->rdAddr);
    createPortsFromJson(inJ["ports"]["RD_DATA"], inNets, inModule, numberOfPorts, newCell->rdData);
    createPortsFromJson(inJ["ports"]["WR_CLK"], inNets, inModule, numberOfPorts, newCell->wrClk);
    createPortsFromJson(inJ["ports"]["WR_EN"], inNets, inModule, numberOfPorts, newCell->wrEn);
    createPortsFromJson(inJ["ports"]["WR_ADDR"], inNets, inModule, numberOfPorts, newCell->wrAddr);
    createPortsFromJson(inJ["ports"]["WR_DATA"], inNets, inModule, numberOfPorts, newCell->wrData);

    return (cell_t*) newCell;
}

json cellMemInit_t::storeAdditionalInJson()
{
    json description;
    description["parameters"]["MEM_ID"] = this->memId;
    description["parameters"]["A_BITS"] = this->aBits;
    description["parameters"]["WIDTH"] = this->width;
    description["parameters"]["WORDS"] = this->words;
    description["parameters"]["PRIORITY"] = this->priority;
    fillPortsIntoJson(description["ports"]["ADDR"], this->addr);
    fillPortsIntoJson(description["ports"]["DATA"], this->data);

    return description;
}

cell_t* cellMemInit_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule){

    int numberOfPorts = 1;

    cellMemInit_t *newCell = new cellMemInit_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["MEM_ID"],
        inJ["parameters"]["A_BITS"],
        inJ["parameters"]["WIDTH"],
        inJ["parameters"]["WORDS"],
        inJ["parameters"]["PRIORITY"]
    );

    createPortsFromJson(inJ["ports"]["ADDR"], inNets, inModule, numberOfPorts, newCell->addr);
    createPortsFromJson(inJ["ports"]["DATA"], inNets, inModule, numberOfPorts, newCell->data);

    return (cell_t*) newCell;
}

json cellMemRd_t::storeAdditionalInJson()
{
    json description;
    description["parameters"]["MEM_ID"] = this->memId;
    description["parameters"]["A_BITS"] = this->aBits;
    description["parameters"]["WIDTH"] = this->width;
    description["parameters"]["CLK_ENABLE"] = this->clkEnable;
    description["parameters"]["CLK_POLARITY"] = this->clkPolarity;
    description["parameters"]["TRANSPARENT"] = this->transparent;
    fillPortIntoJson(description["ports"]["CLK"], this->clk);
    fillPortIntoJson(description["ports"]["EN"], this->en);
    fillPortsIntoJson(description["ports"]["ADDR"], this->addr);
    fillPortsIntoJson(description["ports"]["DATA"], this->data);

    return description;
}

cell_t * cellMemRd_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule){

    int numberOfPorts = 1;
    port_t *clkPort;
    createPortFromJson(inJ["ports"]["CLK"], inNets, inModule, numberOfPorts, clkPort);
    port_t *enPort;
    createPortFromJson(inJ["ports"]["EN"], inNets, inModule, numberOfPorts, enPort);

    cellMemRd_t *newCell = new cellMemRd_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["MEM_ID"],
        inJ["parameters"]["A_BITS"],
        inJ["parameters"]["WIDTH"],
        inJ["parameters"]["CLK_ENABLE"],
        inJ["parameters"]["CLK_POLARITY"],
        inJ["parameters"]["TRANSPARENT"],
        *clkPort,
        *enPort
    );

    createPortsFromJson(inJ["ports"]["ADDR"], inNets, inModule, numberOfPorts, newCell->addr);
    createPortsFromJson(inJ["ports"]["DATA"], inNets, inModule, numberOfPorts, newCell->data);

    return (cell_t*) newCell;
}

json cellMemWr_t::storeAdditionalInJson()
{
    json description;
    description["parameters"]["MEM_ID"] = this->memId;
    description["parameters"]["A_BITS"] = this->aBits;
    description["parameters"]["WIDTH"] = this->width;
    description["parameters"]["CLK_ENABLE"] = this->clkEnable;
    description["parameters"]["CLK_POLARITY"] = this->clkPolarity;
    description["parameters"]["TRANSPERENT"] = this->transparent;
    fillPortIntoJson(description["ports"]["CLK"], this->clk);
    fillPortsIntoJson(description["ports"]["EN"], this->en);
    fillPortsIntoJson(description["ports"]["ADDR"], this->addr);
    fillPortsIntoJson(description["ports"]["DATA"], this->data);

    return description;
}

cell_t * cellMemWr_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule){

    int numberOfPorts = 1;
    port_t *clkPort;
    createPortFromJson(inJ["ports"]["CLK"], inNets, inModule, numberOfPorts, clkPort);

    cellMemWr_t *newCell = new cellMemWr_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["MEM_ID"],
        inJ["parameters"]["A_BITS"],
        inJ["parameters"]["WIDTH"],
        inJ["parameters"]["CLK_ENABLE"],
        inJ["parameters"]["CLK_POLARITY"],
        inJ["parameters"]["TRANSPARENT"],
        *clkPort
    );

    createPortsFromJson(inJ["ports"]["ADDR"], inNets, inModule, numberOfPorts, newCell->addr);
    createPortsFromJson(inJ["ports"]["DATA"], inNets, inModule, numberOfPorts, newCell->data);
    createPortsFromJson(inJ["ports"]["EN"], inNets, inModule, numberOfPorts, newCell->en);

    return (cell_t*) newCell;
}

json cellMux_t::storeAdditionalInJson()
{
    json description;
    description["parameters"]["WIDTH"] = this->width;
    fillPortIntoJson(description["ports"]["S"], this->s);
    fillPortsIntoJson(description["ports"]["A"], this->a);
    fillPortsIntoJson(description["ports"]["B"], this->b);
    fillPortsIntoJson(description["ports"]["Y"], this->y);

    return description;
}

cell_t * cellMux_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule){

    int numberOfPorts = 1;
    port_t *sPort;
    createPortFromJson(inJ["ports"]["S"], inNets, inModule, numberOfPorts, sPort);

    cellMux_t *newCell = new cellMux_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["WIDTH"],
        *sPort
    );

    createPortsFromJson(inJ["ports"]["A"], inNets, inModule, numberOfPorts, newCell->a);
    createPortsFromJson(inJ["ports"]["B"], inNets, inModule, numberOfPorts, newCell->b);
    createPortsFromJson(inJ["ports"]["Y"], inNets, inModule, numberOfPorts, newCell->y);

    return (cell_t*) newCell;

}

json cellPMux_t::storeAdditionalInJson()
{
    json description;
    description["parameters"]["WIDTH"] = this->width;
    description["parameters"]["S_WIDTH"] = this->sWidth;
    fillPortsIntoJson(description["ports"]["S"], this->s);
    fillPortsIntoJson(description["ports"]["A"], this->a);
    fillPortsIntoJson(description["ports"]["B"], this->b);
    fillPortsIntoJson(description["ports"]["Y"], this->y);

    return description;
}

cell_t * cellPMux_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule){

    int numberOfPorts = 1;

    cellPMux_t *newCell = new cellPMux_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["WIDTH"],
        inJ["parameters"]["S_WIDTH"]
    );

    createPortsFromJson(inJ["ports"]["A"], inNets, inModule, numberOfPorts, newCell->a);
    createPortsFromJson(inJ["ports"]["B"], inNets, inModule, numberOfPorts, newCell->b);
    createPortsFromJson(inJ["ports"]["Y"], inNets, inModule, numberOfPorts, newCell->y);
    createPortsFromJson(inJ["ports"]["S"], inNets, inModule, numberOfPorts, newCell->s);

    return (cell_t*) newCell;
}

json cellSlice_t::storeAdditionalInJson()
{
    json description;
    description["parameters"]["OFFSET"] = this->offset;
    description["parameters"]["A_WIDTH"] = this->aWidth;
    description["parameters"]["Y_WIDTH"] = this->yWidth;
    fillPortsIntoJson(description["ports"]["A"], this->a);
    fillPortsIntoJson(description["ports"]["Y"], this->y);

    return description;
}

cell_t * cellSlice_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule){

    int numberOfPorts = 1;

    cellSlice_t *newCell = new cellSlice_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["OFFSET"],
        inJ["parameters"]["A_WIDTH"],
        inJ["parameters"]["Y_WIDTH"]
    );

    createPortsFromJson(inJ["ports"]["A"], inNets, inModule, numberOfPorts, newCell->a);
    createPortsFromJson(inJ["ports"]["Y"], inNets, inModule, numberOfPorts, newCell->y);

    return (cell_t*) newCell;
}

json cellSop_t::storeAdditionalInJson()
{
    json description;
    description["parameters"]["WIDTH"] = this->width;
    description["parameters"]["DEPTH"] = this->depth;

    int tableSize = (this->width) * (this->depth);
    for (int i = 0; i < tableSize; i++)
    {
        description["parameters"]["TABLE"].at(i) = this->table[i];
    }
    fillPortIntoJson(description["ports"]["Y"], this->y);
    fillPortsIntoJson(description["ports"]["A"], this->a);

    return description;
}

cell_t * cellSop_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule){

    int numberOfPorts = 1;
    port_t *yPort;
    createPortFromJson(inJ["ports"]["Y"], inNets, inModule, numberOfPorts, yPort);

    cellSop_t *newCell = new cellSop_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["WIDTH"],
        inJ["parameters"]["DEPTH"],
        *yPort
    );

    int tableSize = newCell->width * newCell->depth;
    newCell->table = new unsigned int[tableSize];

    for (int i = 0; i < tableSize; i++)
    {
        newCell->table[i] = inJ["parameters"]["TABLE"].at(i);
    }

    return (cell_t*) newCell;

}

json cellSpecify2_t::storeAdditionalInJson()
{
    json description;
    description["parameters"]["FULL"] = this->full;
    description["parameters"]["SRC_WIDTH"] = this->srcWidth;
    description["parameters"]["DST_WIDTH"] = this->dstWidth;
    description["parameters"]["SRC_DST_PEN"] = this->srcDstPen;
    description["parameters"]["SRC_DST_POL"] = this->srcDstPol;
    description["parameters"]["T_RISE_MIN"] = this->tRiseMin;
    description["parameters"]["T_RISE_TYP"] = this->tRiseTyp;
    description["parameters"]["T_RISE_MAX"] = this->tRiseMax;
    description["parameters"]["T_FALL_MIN"] = this->tFallMin;
    description["parameters"]["T_FALL_TYP"] = this->tFallTyp;
    description["parameters"]["T_FALL_MAX"] = this->tFallMax;
    fillPortIntoJson(description["ports"]["EN"], this->en);
    fillPortsIntoJson(description["ports"]["SRC"], this->src);
    fillPortsIntoJson(description["ports"]["DST"], this->dst);

    return description;
}

cell_t * cellSpecify2_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule, const cellType_t type){

    int numberOfPorts = 1;
    port_t *enPort;
    createPortFromJson(inJ["ports"]["EN"], inNets, inModule, numberOfPorts, enPort);
    
    cellSpecify2_t *newCell = new cellSpecify2_t(
        inJ["name"],
        inJ["hide_name"],
        type,
        inJ["parameters"]["FULL"],
        inJ["parameters"]["SRC_WIDTH"],
        inJ["parameters"]["DST_WIDTH"],
        inJ["parameters"]["SRC_DST_PEN"],
        inJ["parameters"]["SRD_DST_POL"],
        inJ["parameters"]["T_RISE_MIN"],
        inJ["parameters"]["T_RISE_TYP"],
        inJ["parameters"]["T_RISE_MAX"],
        inJ["parameters"]["T_FALL_MIN"],
        inJ["parameters"]["T_FALL_TYP"],
        inJ["parameters"]["T_FALL_MAX"],
        *enPort
    );

    createPortsFromJson(inJ["ports"]["SRC"], inNets, inModule, numberOfPorts, newCell->src);
    createPortsFromJson(inJ["ports"]["DST"], inNets, inModule, numberOfPorts, newCell->dst);

    return (cell_t*) newCell;
}

json cellSpecify3_t::storeAdditionalInJson()
{
    json description;
    description = ((cellSpecify2_t *)this)->storeAdditionalInJson();
    description["parameters"]["EDGE_EN"] = this->edgeEn;
    description["parameters"]["EDGE_POL"] = this->edgePol;
    description["parameters"]["DAT_DST_PEN"] = this->datDstPen;
    description["parameters"]["DAT_DST_POL"] = this->datDstPen;
    fillPortsIntoJson(description["ports"]["DAT"], this->dat);

    return description;
}

cell_t * cellSpecify3_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule, const cellType_t type){
    int numberOfPorts = 1;
    port_t *enPort;
    createPortFromJson(inJ["ports"]["EN"], inNets, inModule, numberOfPorts, enPort);
    
    cellSpecify3_t *newCell = new cellSpecify3_t(
        inJ["name"],
        inJ["hide_name"],
        type,
        inJ["parameters"]["FULL"],
        inJ["parameters"]["SRC_WIDTH"],
        inJ["parameters"]["DST_WIDTH"],
        inJ["parameters"]["SRC_DST_PEN"],
        inJ["parameters"]["SRD_DST_POL"],
        inJ["parameters"]["T_RISE_MIN"],
        inJ["parameters"]["T_RISE_TYP"],
        inJ["parameters"]["T_RISE_MAX"],
        inJ["parameters"]["T_FALL_MIN"],
        inJ["parameters"]["T_FALL_TYP"],
        inJ["parameters"]["T_FALL_MAX"],
        inJ["parameters"]["EDGE_EN"],
        inJ["parameters"]["EDGE_POL"],
        inJ["parameters"]["DAT_DST_PEN"],
        inJ["parameters"]["DAT_DST_POL"],
        *enPort
    );

    createPortsFromJson(inJ["ports"]["SRC"], inNets, inModule, numberOfPorts, newCell->src);
    createPortsFromJson(inJ["ports"]["DST"], inNets, inModule, numberOfPorts, newCell->dst);
    createPortsFromJson(inJ["ports"]["DAT"], inNets, inModule, numberOfPorts, newCell->dat);

    return (cell_t*) newCell;
}

json cellTriBuf_t::storeAdditionalInJson()
{
    json description;
    description["parameters"]["WIDTH"] = this->width;
    fillPortIntoJson(description["ports"]["EN"], this->en);
    fillPortsIntoJson(description["ports"]["A"], this->a);
    fillPortsIntoJson(description["ports"]["Y"], this->y);

    return description;
}

cell_t * cellTriBuf_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule){

    int numberOfPorts = 1;
    port_t *enPort;
    createPortFromJson(inJ["ports"]["EN"], inNets, inModule, numberOfPorts, enPort);

    cellTriBuf_t *newCell = new cellTriBuf_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["WIDTH"],
        *enPort
    );

    createPortsFromJson(inJ["ports"]["A"], inNets, inModule, numberOfPorts, newCell->a);
    createPortsFromJson(inJ["ports"]["Y"], inNets, inModule, numberOfPorts, newCell->y);

    return (cell_t*) newCell;
}

json cellSr_t::storeAdditionalInJson()
{
    json description;
    description["parameters"]["WIDTH"] = this->width;
    description["parameters"]["SET_POLARITY"] = this->setPolarity;
    description["parameters"]["CLR_POLARITY"] = this->clrPolarity;
    fillPortsIntoJson(description["ports"]["SET"], this->set);
    fillPortsIntoJson(description["ports"]["CLR"], this->clr);
    fillPortsIntoJson(description["ports"]["Q"], this->q);

    return description;
}

cell_t * cellSr_t::createAdditionalFromJson(json &inJ, json &inNets, module_t &inModule){

    int numberOfPorts = 1;

    cellSr_t *newCell = new cellSr_t(
        inJ["name"],
        inJ["hide_name"],
        inJ["parameters"]["WIDTH"],
        inJ["parameters"]["SET_POLARITY"],
        inJ["parameters"]["CLR_POLARITY"]
    );

    createPortsFromJson(inJ["ports"]["SET"], inNets, inModule, numberOfPorts, newCell->set);
    createPortsFromJson(inJ["ports"]["CLR"], inNets, inModule, numberOfPorts, newCell->clr);
    createPortsFromJson(inJ["ports"]["Q"], inNets, inModule, numberOfPorts, newCell->q);

    return (cell_t*) newCell;
}