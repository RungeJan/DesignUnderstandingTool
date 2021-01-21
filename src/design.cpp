#include "design.h"

using namespace std;

json design_t::storeInJson(){
    json description;
    description["name"] = this->name;
    
    if(this->modules.empty() == false){
       int i = 1;
        vector<module_t>::iterator it = this->modules.begin();
        while(it != this->modules.end()){
            string tempName = "module_" + to_string(i);
            description["modules"][tempName] = it->storeInJson();
            it++;
            i++;
        }
    }

    return description;
}