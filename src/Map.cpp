#include "Map.h"
#include "../external/rapidxml-1.13/rapidxml.hpp"
#include <sstream>
#include <iostream>
#include <fstream>

void Map::LoadTileMap(){
    // Open the TileMap and parse it as xml
    rapidxml::xml_document<> TileMapXml;
    std::ifstream file;
    file.open(Map::tileMapLocation);
    if (!file.is_open())
    {
        std::cerr << "Can't read xml file" << std::endl;
        return;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string fileContents = buffer.str();
    file.close();
    TileMapXml.parse<0>(&fileContents[0]);

    rapidxml::xml_node<> *mapNode = TileMapXml.first_node();
    rapidxml::xml_node<> *layerNode = mapNode->first_node()->next_sibling();
    rapidxml::xml_node<> *layerDataNode = layerNode->first_node();
    if (layerDataNode->value() == "")
    {
        std::cout << "Could not read tilemap data";
        return;
    }
    else
    {
        //continue - tileMap data was retrieved succsessfully
        //layerDataNode->value() will return the tileMap data
    }    
}
