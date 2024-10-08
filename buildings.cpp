/*buildings.cpp*/
// TThis stores building data and the ability to read building
// Mukhtar Handulle

#include "buildings.h"
#include "osm.h"
#include <cassert>

using namespace std;
using namespace tinyxml2;

void Buildings::readMapBuildings(XMLDocument& xmldoc) //read building data
{
    XMLElement* way = xmldoc.FirstChildElement("osm")->FirstChildElement("way"); //get first way element from root
    while (way != nullptr)
    {
        if (osmContainsKeyValue(way, "building", "university")) //checks if it is university building, then extract building ID, name
        {
            long long id = way->Int64Attribute("id");
            string name = osmGetKeyValue(way, "name");
            string streetAddr = osmGetKeyValue(way, "addr:housenumber") + " " +
                                osmGetKeyValue(way, "addr:street");
            Building building(id, name, streetAddr); //new building with the information we got
            XMLElement* nd = way->FirstChildElement("nd");
            while (nd != nullptr)
            {
                const XMLAttribute* ndref = nd->FindAttribute("ref"); //finds the ref attribute of nd elemnt
                assert(ndref != nullptr);
                long long nodeId = ndref->Int64Value();
                building.add(nodeId);
                nd = nd->NextSiblingElement("nd");
            }
            this->MapBuildings.push_back(building); //update hte vector
        }
        way = way->NextSiblingElement("way"); //moves to the next
    }
}
//function for getting number of buildings in MapBuidlings and returning the siz
int Buildings::getNumMapBuildings() const
{
    return this->MapBuildings.size();
}