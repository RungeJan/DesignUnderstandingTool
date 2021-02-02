#include "functionalities.h"
#include "nlohmann/json.hpp"
#include "cell.h"
#include <vector>

using json = nlohmann::json;
using namespace std;


void markCFInfluencingNets(module_t &inModule){
    // First mark all the nets that are given as inputs for multiplexers
    vector<cell_t*>::iterator cellIt = inModule.cells.begin();
    while(cellIt != inModule.cells.end()){
        if(TypePMux == (*cellIt)->type){
            cellPMux_t *tempCell = (cellPMux_t*)(*cellIt);
            vector<port_t>::iterator netIt = tempCell->s.begin();
            while(netIt != tempCell->s.end()){
                netIt->net.hasCFInfluence = true;
                netIt++;
            }
        }
        else if(TypeMux == (*cellIt)->type){
            cellMux_t *tempCell = (cellMux_t*)(*cellIt);
            tempCell->s.net.hasCFInfluence = true;
        }

        cellIt++;
    }
}