#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>

#include "design.h"
#include "module.h"
#include "net.h"
#include "cell.h"
#include "processing.h"
#include "functionalities.h"

using namespace std;
using json = nlohmann::json;

using namespace std;

char *filename = NULL;
bool isYosysFile = false;
string designName = "Unknown";
string outFileName = "./json/DUT_IR.json";
void parseOptions(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Too less arguments, type main.exe -help for more information" << endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "-help")
        {
            cout << "******************************************" << endl
                 << "* Help for the Design Understanding Tool *" << endl
                 << "******************************************" << endl
                 << "The following has to be added to the" << endl
                 << "function call:" << endl
                 << "main.exe <file_name>  Where <file_name> is" << endl
                 << "the name of the file holding the design " << endl
                 << "description." << endl;
        }
        else if (string(argv[i]) == "-yosys")
        {
            isYosysFile = true;
        }
        else if ((string(argv[i])) == "-name")
        {
            designName = string(argv[i + 1]);
            i++;
        }
        else if (((string(argv[i])) == "-outName") || ((string(argv[i])) == "-o"))
        {
            outFileName = "./json/" + string(argv[i + 1]);
            i++;
        }
        else
        {
            filename = argv[i];
        }
    }
}

int main(int argc, char *argv[])
{
    parseOptions(argc, argv);

    ifstream file(filename);
    json description;
    json processed;
    file >> description;

    design_t newDesign;

    //cout << description["modules"].dump(1) << endl;
    if (isYosysFile)
    {
        if (designName == "Unknown")
        {
            designName = string(filename);
            designName = designName.substr(0, designName.find(".json"));
        }
        newDesign.name = designName;
        processYosysDescription(description, newDesign);
    }
    else
    {
        if (designName == "Unknown")
        {
            designName = description["name"];
        }
        newDesign.name = designName;
        if (description.contains("modules"))
        {
            json::iterator it = description["modules"].begin();
            while (it != description["modules"].end())
            {
                module_t *newModule = module_t::createFromJson(*it);
                newDesign.modules.push_back(*newModule);
                it++;
            }
        }
    }
     cout << "Description read in completely" << endl;

    vector<module_t>::iterator it = newDesign.modules.begin();
    while(it != newDesign.modules.end()){
        //markCFInfluencingNets(*it);
        createCFGraph(*it);
        it++;
    }
   

    ofstream checkFile("leftDescription.json");
    checkFile << description.dump(4);

    json myIR = newDesign.storeInJson();
    ofstream newIr(outFileName);
    newIr << myIR.dump(4);

    return 0;
}