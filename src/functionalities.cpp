#include "functionalities.h"
#include "nlohmann/json.hpp"
#include "cell.h"
#include <vector>

using json = nlohmann::json;
using namespace std;


void markCFInfluencingNets(module_t &inModule){
    // First mark all the nets that are given as inputs for multiplexers
    cout << "Started CF analysis" << endl;
    vector<cell_t*>::iterator cellIt = inModule.cells.begin();
    while(cellIt != inModule.cells.end()){
        if(TypePMux == (*cellIt)->type){
            cellPMux_t *tempCell = (cellPMux_t*)(*cellIt);
            vector<port_t>::iterator portIt = tempCell->s.begin();
            while(portIt != tempCell->s.end()){
                cout << portIt->netId << endl;
                inModule.getNetWithId(portIt->netId).hasCFInfluence = true;
                portIt++;
            }
        }
        else if(TypeMux == (*cellIt)->type){
            cellMux_t *tempCell = (cellMux_t*)(*cellIt);
            cout << tempCell->s.netId << endl;
            inModule.getNetWithId(tempCell->s.netId).hasCFInfluence = true;
        }

        cellIt++;
    }
    cout << "Finished CF analysis" << endl;
}