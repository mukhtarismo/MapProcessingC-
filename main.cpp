#include <string>
#include <iostream>
#include "building.h"
#include "osm.h"
#include "node.h"
#include "nodes.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

int main() {
    string filename;
    cout << "Enter filename: ";
    getline(cin, filename);
    XMLDocument xmldoc;

    if (osmLoadMapFile(filename, xmldoc)==false){
        cout << "error ";
        return 0;
    }

    Nodes nodes;
    nodes.readMapNodes(xmldoc);

    cout << "# of nodes: " << nodes.getNumMapNodes() << endl;

    return 0;


}