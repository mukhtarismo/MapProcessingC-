/*nodes.cpp*/

//
// A collection of nodes in the Open Street Map.
// Mukhtar Handulle
// Prof. Joe Hummel
// Northwestern University
// CS 211
// 
// References:
// 
// TinyXML: 
//   files: https://github.com/leethomason/tinyxml2
//   docs:  http://leethomason.github.io/tinyxml2/
// 
// OpenStreetMap: https://www.openstreetmap.org
// OpenStreetMap docs:  
//   https://wiki.openstreetmap.org/wiki/Main_Page
//   https://wiki.openstreetmap.org/wiki/Map_Features
//   https://wiki.openstreetmap.org/wiki/Node
//   https://wiki.openstreetmap.org/wiki/Way
//   https://wiki.openstreetmap.org/wiki/Relation
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;


//
// readMapNodes
//
// Given an XML document, reads through the document and 
// stores all the nodes into the given vector. Each node
// is a point on the map, with a unique id along with 
// (lat, lon) position. Some nodes are entrances to buildings,
// which we capture as well.
//
void Nodes::readMapNodes(XMLDocument& xmldoc)
{
  XMLElement* osm = xmldoc.FirstChildElement("osm");
  assert(osm != nullptr);

  //
  // Parse the XML document node by node: 
  //
  XMLElement* node = osm->FirstChildElement("node");

  while (node != nullptr)
  {
    const XMLAttribute* attrId = node->FindAttribute("id");
    const XMLAttribute* attrLat = node->FindAttribute("lat");
    const XMLAttribute* attrLon = node->FindAttribute("lon");

    assert(attrId != nullptr);
    assert(attrLat != nullptr);
    assert(attrLon != nullptr);

    long long id = attrId->Int64Value();
    double latitude = attrLat->DoubleValue();
    double longitude = attrLon->DoubleValue();

    //
    // is this node an entrance? Check for a 
    // standard entrance, the main entrance, or
    // one-way entrance.
    //
    bool entrance = false;

    if (osmContainsKeyValue(node, "entrance", "yes") ||
      osmContainsKeyValue(node, "entrance", "main") ||
      osmContainsKeyValue(node, "entrance", "entrance"))
    {
      entrance = true;
    }

    //
    // Add node to vector:
    // 
    // This creates an object then pushes copy into vector:
    //
    Node N(id, latitude, longitude, entrance);
    this->MapNodes.push_back(N);

    //
    // next node element in the XML doc:
    //
    node = node->NextSiblingElement("node");
  }
}

//
// find
// 
// Searches the nodes for the one with the matching ID, returning
// true if found and false if not. If found, a copy of the node 
// is returned via the node parameter, which is passed by reference.
//
bool Nodes::find(long long id, double& lat, double& lon, bool& isEntrance) const //finds node by its ID and returns lat, long, and entrance
{

  // binary search:
  //
  int low = 0; //intilizing lower bound
  int high = (int)this->MapNodes.size() - 1; //initiliaze upper bound 

  while (low <= high) //while loop for ocntinuos seraching and range is met
  {
    int mid = low + (high - low) / 2; //calculates middle index
    
    if (this->MapNodes[mid].getID() == id) //checks to see if it maches the search ID
    {
      lat = this->MapNodes[mid].getLat(); //sets the output with found dataand return true at the end if not found
      lon = this->MapNodes[mid].getLon();
      isEntrance = this->MapNodes[mid].getIsEntrance();
      return true;
    }
    if (this->MapNodes[mid].getID() < id) //searches the upper half inf middle element's ID is less 
      low = mid + 1;
    else
      high = mid - 1;
  }
  //  not found:
  return false;
}
// accessors 

int Nodes::getNumMapNodes() const {
  return (int) this->MapNodes.size();
}