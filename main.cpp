/*main.cpp*/
// The main program for map building.
// Mukhtar Handulle
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
/**
THis is main function. takes file input and returns 0 if program is correct or false or 1 if there is an erro
*/
int main() {
    string name;
    cout << "Enter OSM filename: ";
    getline(cin, name);
    XMLDocument xmldoc;
    if (osmLoadMapFile(name, xmldoc)==false){
        cout << "error ";
        return 0;
    }
    //This initialized buildings and nodes
    Nodes nodes;
    nodes.readMapNodes(xmldoc);
    Buildings buildings;
    buildings.readMapBuildings(xmldoc);

    cout << "# of nodes: " << nodes.getNumMapNodes() << endl;
    cout << "# of buildings: " << buildings.getNumMapBuildings() << endl;

    string command;
    while (true) {
        cout << "Enter partial or complete building name on campus, or * to list, or $ to end: ";
        getline(cin, command);

        if (command == "$") {
            break;
        } else if (command == "*") {
            for (const auto& building : buildings.MapBuildings) {
                cout << building.ID << ": " << building.Name 
                     << ", " << building.StreetAddress << endl;
            }
        } else {
            bool found = false;
            for (const auto& building : buildings.MapBuildings) {
                if (building.Name.find(command) != string::npos) {
                    found = true;
                    cout << " " << building.Name << endl;
                    cout << "Address: " << building.StreetAddress << endl;
                    cout << "Building ID: " << building.ID << endl;
                    cout << "Nodes:" << endl;
                    for (const auto& nodeID : building.NodeIDs) {
                        double lat, lon;
                        bool isEntrance;
                        if (nodes.find(nodeID, lat, lon, isEntrance)) {
                            cout << "  " << nodeID << ": (" << lat << ", " << lon << ")";
                            if (isEntrance) cout << " ENTRANCE";
                            cout << endl;
                        } else {
                            cout << "  " << nodeID << ": ** NOT FOUND **" << endl;
                        }
                    }
                    cout << endl;
                }
            }
            if (!found) {
                cout << "No such building" << endl;
            }
        }
    }

    cout << "** Done **" << endl;
    cout << "# of calls to node's getID(): " << Node::getCallsToGetID() << endl;
    cout << "# of nodes created: " << Node::getCreated() << endl;
    cout << "# of nodes copied: " << Node::getCopied() << endl;
    cout.flush();
    return 0;
}