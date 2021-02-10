#include "functionalities.h"
#include "nlohmann/json.hpp"
#include "cell.h"
#include <vector>
#include <deque>
#include <fstream>

using json = nlohmann::json;
using namespace std;

struct markedCell_t
{
    markedCell_t() : cell(NULL), checked(false){};
    markedCell_t(cell_t *newCell) : cell(newCell), checked(false){};
    cell_t *cell; //!< The cell this instance belongs to
    bool checked; //!< A flag if this instance was already checked, to avoid multiple checking resulting in multiple insertions
};

struct cfGraphElement_t
{
    cfGraphElement_t(markedCell_t &newCell) : level(0), condition("Always"), markedCell(newCell){};

    /**
    * @brief This function will safely overwrite the cf level (never decrease the level)
    * 
    * @param newLevel The new level that should be written
    */
    void overwriteLevel(unsigned int newLevel) { level = level < newLevel ? newLevel : level; };
    unsigned int getLevel() { return level; };
    markedCell_t markedCell;             //!< The cell this instance belongs to
    vector<cfGraphElement_t> successors; //!< All the cells that follow this graph element
    vector<string> predecessors;
    string condition; //!< The condition under which this cell is reached directly

private:
    unsigned int level; //!< the CF level in terms of how many cf decisions were done before this cell
};

void fillSuccessors(vector<cfGraphElement_t> &nodes, vector<markedCell_t> &cells, module_t &inModule)
{
    vector<cfGraphElement_t>::iterator nodeIt = nodes.begin();
    while (nodes.end() != nodeIt)
    {
        vector<markedCell_t>::iterator cellIt = cells.begin();
        while (cells.end() != cellIt)
        {
            cellIt->checked = false;
            vector<unsigned int>::iterator portIt = nodeIt->markedCell.cell->outputBitIds.begin();
            while (nodeIt->markedCell.cell->outputBitIds.end() != portIt)
            {
                if (!(cellIt->checked) && find(cellIt->cell->inputBitIds.begin(), cellIt->cell->inputBitIds.end(), *portIt) != cellIt->cell->inputBitIds.end())
                {
                    cellIt->checked = true;
                    cfGraphElement_t *newElem = new cfGraphElement_t(*(cellIt));
                    // Add all predeccessors of the current node to the next one as well
                    newElem->predecessors.insert(newElem->predecessors.begin(), nodeIt->predecessors.begin(), nodeIt->predecessors.end());
                    if (TypeMux == nodeIt->markedCell.cell->type)
                    {
                        cellMux_t *tempCell = (cellMux_t *)nodeIt->markedCell.cell;
                        newElem->condition = inModule.getNetWithId(tempCell->s.netId).name + " == 0";
                        vector<port_t>::iterator tempIt = tempCell->a.begin();
                        while (tempCell->a.end() != tempIt)
                        {
                            newElem->condition += " | " + inModule.getNetWithId(tempIt->netId).name;
                            tempIt++;
                        }
                        nodeIt->successors.push_back(*newElem);
                        newElem = new cfGraphElement_t(*(cellIt));
                        // Add all predeccessors of the current node to the next one as well
                        newElem->predecessors.insert(newElem->predecessors.begin(), nodeIt->predecessors.begin(), nodeIt->predecessors.end());
                        tempCell = (cellMux_t *)nodeIt->markedCell.cell;
                        newElem->condition = inModule.getNetWithId(tempCell->s.netId).name + " == 1";
                        tempIt = tempCell->b.begin();
                        while (tempCell->b.end() != tempIt)
                        {
                            newElem->condition += " | " + inModule.getNetWithId(tempIt->netId).name;
                            tempIt++;
                        }
                    }

                    nodeIt->successors.push_back(*newElem);
                }
                else
                {
                    // cout << "No further Connection" << endl;
                }
                portIt++;
            }
            cellIt++;
        }
        if (nodeIt->successors.empty() == false)
        {
            vector<cfGraphElement_t> temp;
            vector<cfGraphElement_t>::iterator tempIt = nodeIt->successors.begin();
            while (nodeIt->successors.end() != tempIt)
            {
                // If the cell is already a predecessor of this cell, don't get it successors to avoid cycles
                if (find(tempIt->predecessors.begin(), tempIt->predecessors.end(), nodeIt->markedCell.cell->name) != tempIt->predecessors.end())
                {
                    temp.push_back(*tempIt);
                    nodeIt->successors.erase(tempIt);
                    tempIt = nodeIt->successors.begin();
                }
                else
                {
                    tempIt->predecessors.push_back(nodeIt->markedCell.cell->name);
                    tempIt++;
                }
            }

            fillSuccessors(nodeIt->successors, cells, inModule);
            //nodeIt->successors.insert(nodeIt->successors.end(), temp.begin(), temp.end());
        }
        nodeIt++;
    }
}

void printSuccessors(vector<cfGraphElement_t> succs, unsigned int space, ostream &outStream = cout)
{
    if (succs.size() == 0)
    {
        outStream << endl;
        return;
    }
    else
    {
        for (int i = 0; i < succs.size(); i++)
        {
            if (i > 0)
            {
                for (int j = 0; j < space; j++)
                {
                    outStream << " ";
                }
            }
            string output = "->" + succs.at(i).condition + "->" + getCellType(succs.at(i).markedCell.cell->type) + ":" + succs.at(i).markedCell.cell->name;
            outStream << output;

            printSuccessors(succs.at(i).successors, space + output.length(), outStream);
        }
    }
}

void markCFInfluencingNets(module_t &inModule)
{
    // First mark all the nets that are given as inputs for multiplexers
    cout << "Started CF analysis" << endl;
    vector<cell_t *>::iterator cellIt = inModule.cells.begin();
    while (cellIt != inModule.cells.end())
    {
        if (TypePMux == (*cellIt)->type)
        {
            cellPMux_t *tempCell = (cellPMux_t *)(*cellIt);
            vector<port_t>::iterator portIt = tempCell->s.begin();
            while (portIt != tempCell->s.end())
            {
                inModule.getNetWithId(portIt->netId).hasCFInfluence = CFInfluencePrimary;
                portIt++;
            }
        }
        else if (TypeMux == (*cellIt)->type)
        {
            cellMux_t *tempCell = (cellMux_t *)(*cellIt);
            inModule.getNetWithId(tempCell->s.netId).hasCFInfluence = CFInfluencePrimary;
        }

        cellIt++;
    }
    cellIt = inModule.cells.begin();
    bool resetCellIt = false;
    while (cellIt != inModule.cells.end())
    {
        resetCellIt = false;
        vector<unsigned int>::iterator outPortIt = (*cellIt)->outputBitIds.begin();
        while ((*cellIt)->outputBitIds.end() != outPortIt)
        {
            if (inModule.getNetWithId(*outPortIt).hasCFInfluence != CFInfluenceNone)
            {
                vector<unsigned int>::iterator inPortIt = (*cellIt)->inputBitIds.begin();
                while ((*cellIt)->inputBitIds.end() != inPortIt)
                {
                    net_t &currentNet = inModule.getNetWithId(*inPortIt);
                    if (CFInfluenceNone == currentNet.hasCFInfluence)
                    {
                        currentNet.hasCFInfluence = CFInfluenceSecondary;
                        resetCellIt = true;
                    }
                    inPortIt++;
                }
                break;
            }
            outPortIt++;
        }
        if (resetCellIt)
        {
            cellIt = inModule.cells.begin();
        }
        else
        {
            cellIt++;
        }
    }
    cout << "Finished CF analysis" << endl;
}

void createCFGraph(module_t &inModule)
{
    vector<cfGraphElement_t> initGraphNodes;
    vector<markedCell_t> cells;

    cout << "Starting CF Graph generation" << endl;
    vector<cell_t *>::iterator moduleCellIt = inModule.cells.begin();
    while (inModule.cells.end() != moduleCellIt)
    {
        markedCell_t newCell((*moduleCellIt));
        cells.push_back(newCell);
        moduleCellIt++;
    }

    vector<port_t>::iterator portIt = inModule.ports.begin();
    //Find all cells that are directly connected to inputs of a module, these cells have cf level 0
    while (inModule.ports.end() != portIt)
    {
        if (DirectionInput == portIt->direction)
        {
            vector<markedCell_t>::iterator cellIt = cells.begin();
            while (cells.end() != cellIt)
            {
                if (!(cellIt->checked) && find(cellIt->cell->inputBitIds.begin(), cellIt->cell->inputBitIds.end(), portIt->netId) != cellIt->cell->inputBitIds.end())
                {
                    cellIt->checked = true;
                    cfGraphElement_t newElem(*(cellIt));
                    initGraphNodes.push_back(newElem);
                }
                cellIt++;
            }
        }
        portIt++;
    }

    fillSuccessors(initGraphNodes, cells, inModule);

    cout << "Finished CF Graph generation" << endl;
    vector<cfGraphElement_t>::iterator it = initGraphNodes.begin();
    ofstream description("temp.txt");
    while (initGraphNodes.end() != it)
    {
        string output = getCellType(it->markedCell.cell->type) + ":" + it->markedCell.cell->name;
        description << output;
        printSuccessors(it->successors, output.length(), description);
        description << endl
                    << endl;
        it++;
    }
    description.close();
}