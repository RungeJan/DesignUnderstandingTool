#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "design.h"
#include "module.h"
#include "net.h"
#include "cell.h"
#include "processing.h"

using namespace std;
using json = nlohmann::json;

using namespace std;


int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        cerr << "No file provided - Terminating" << endl;
        return -1;
    }

    ifstream file(argv[1]);
    json description;
    json processed;
    file >> description;

    design_t newDesign;

    string name(argv[1]);
    newDesign.name = name.substr(0,name.find(".json"));

    //cout << description["modules"].dump(1) << endl;

    // Go through all the modules individually
    for (int i = 0; i < description["modules"].size(); i++)
    {
        module_t *newModule = new module_t(); //Create a new module
        string moduleDescription = description["modules"].dump();
        newModule->name = moduleDescription.substr(2, moduleDescription.find("\":") - 2);
        cout << newModule->name << endl;
        json &passToFunc = description["modules"][newModule->name];
        // Get the attributes of the module
        if(passToFunc.contains<string>("netnames")){
            processYosysNetsIntoVector(passToFunc["netnames"], newModule);
            passToFunc.erase("netnames");
        }
        if (passToFunc.contains<string>("attributes"))
        {
            processYosysAttributesIntoVector(passToFunc["attributes"], newModule->attributes);
            passToFunc.erase("attributes");
        }
        if (passToFunc.contains<string>("ports"))
        {
            // Add all the ports to the design. They will also be added as nets.
            processYosysPortsIntoVector(passToFunc["ports"], newModule);
            passToFunc.erase("ports");
        }
        if(passToFunc.contains<string>("cells")){
            processYosysCellsIntoVector(passToFunc["cells"], newModule);
            passToFunc.erase("cells");
        }
        description["modules"].erase(newModule->name);
        newDesign.modules.push_back(*newModule);
    }
    
    ofstream checkFile("leftDescription.json");
    checkFile << description.dump(4);

    json myIR = newDesign.storeInJson();
    ofstream newIr("DUT_IR.json");
    newIr << myIR.dump(4);

    return 0;
}