#include "functionalities.h"
#include "nlohmann/json.hpp"
#include "cell.h"
#include <vector>

using json = nlohmann::json;
using namespace std;

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