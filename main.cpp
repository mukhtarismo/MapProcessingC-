#include <string>
#include <iostream>
#include "building.h"
#include "osm.h"
#include "node.h"
#include "nodes.h"
#include "tinyxml2.h"
#include "buildings.h"

using namespace std;
using namespace tinyxml2;

int main() {
    string name;
    cout << "Enter OSM filename: ";
    getline(cin, name);
    XMLDocument xmldoc;

    if (osmLoadMapFile(name, xmldoc)==false){
        cout << "error ";
        return 0;
    }

    Nodes nodes;
    nodes.readMapNodes(xmldoc);
    Buildings buildings;
    buildings.readMapBuildings(xmldoc);

    cout << "# of nodes: " << nodes.getNumMapNodes() << endl;
    cout << "# of buidlings: " << buildings.getNumMapBuildings() <<endl;
    

    cout << "** Done **" << endl;
    cout << "# of calls to node's getID(): " << Node::getCallsToGetID()<< endl;
    cout << "# of nodes created: " << Node::getCreated()<< endl;
    cout << "# of nodes copied: " << Node::getCopied()<< endl;
    cout.flush();
    return 0;


}

