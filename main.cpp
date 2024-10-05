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
    if (osmLoadMapFile(name, xmldoc)==false){ // this loads OSM file 
        cout << "error ";
        return 0;
    }
    //This initialized buildings and nodes. buidlings and nodes will then be populated with XML data
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

        if (command == "$") { //this is exist command
            break;
        } else if (command == "*") { //this lists buidlings
            for (const auto& building : buildings.MapBuildings) {
                cout << building.ID << ": " << building.Name 
                     << ", " << building.StreetAddress << endl;
            }
        } else { //uses input to search for requested buidlings
            bool found = false;
            for (const auto& building : buildings.MapBuildings) {
                if (building.Name.find(command) != string::npos) { //checks if building name is the name as the user request
                    found = true;
                    cout << " " << building.Name << endl;
                    cout << "Address: " << building.StreetAddress << endl;
                    cout << "Building ID: " << building.ID << endl;
                    cout << "Nodes:" << endl;
                    for (const auto& nodeID : building.NodeIDs) {//show s information of all the nodes of hte buidlings
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
            if (!found) { //tells user if there is no building found
                cout << "No such building" << endl;
            }
        }
    }

    cout << "** Done **" << endl; //dispalys final results
    cout << "# of calls to node's getID(): " << Node::getCallsToGetID() << endl;
    cout << "# of nodes created: " << Node::getCreated() << endl;
    cout << "# of nodes copied: " << Node::getCopied() << endl;
    cout.flush();
    return 0;
}