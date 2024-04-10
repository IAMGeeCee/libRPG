#include "Map.h"
#include "../external/rapidxml-1.13/rapidxml.hpp"
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

struct TilesetTile{
  int id;
  string path;
};

void Map::LoadTileMap(){

    //Open the TileSet and parae it as xml
    rapidxml::xml_document<> TilesetXml;
    std::ifstream TilesetFile;
    TilesetFile.open(Map::tileSetLocation);
    if (!TilesetFile.is_open())
    {
        std::cerr << "Can't read xml file" << std::endl;
        return;
    }
    std::stringstream TilesetBuffer;
    TilesetBuffer << TilesetFile.rdbuf();
    std::string TilesetFileContents = TilesetBuffer.str();
    TilesetFile.close();
    TilesetXml.parse<0>(&TilesetFile[0]);

    //TODO: do somthing with the tileset



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
    
    //Find the actuall map csv data that we need
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
