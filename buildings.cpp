#include "buildings.h"
#include "osm.h"
#include <cassert>

using namespace std;
using namespace tinyxml2;

void Buildings::readMapBuildings(XMLDocument& xmldoc)
{
    XMLElement* way = xmldoc.FirstChildElement("osm")->FirstChildElement("way");
    
    while (way != nullptr)
    {
        if (osmContainsKeyValue(way, "building", "university"))
        {
            long long id = way->Int64Attribute("id");
            string name = osmGetKeyValue(way, "name");
            string streetAddr = osmGetKeyValue(way, "addr:housenumber") + " " +
                                osmGetKeyValue(way, "addr:street");
            Building B(id, name, streetAddr);
            XMLElement* nd = way->FirstChildElement("nd");
            while (nd != nullptr)
            {
                const XMLAttribute* ndref = nd->FindAttribute("ref");
                assert(ndref != nullptr);
                long long nodeId = ndref->Int64Value();
                B.add(nodeId);
                nd = nd->NextSiblingElement("nd");
            }
            this->MapBuildings.push_back(B);
        }

        way = way->NextSiblingElement("way");
    }
}

int Buildings::getNumMapBuildings() const
{
    return this->MapBuildings.size();
}