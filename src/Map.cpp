#include "Map.h"
#include "../external/rapidxml-1.13/rapidxml.hpp"
#include <list>
#include <ostream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

// thx stackoverflow ;)
int getChildCount(rapidxml::xml_node<> *n)
{
  int c = 0;
  for (rapidxml::xml_node<> *child = n->first_node(); child != NULL; child = child->next_sibling())
  {
    c++;
  } 
  return c;
} 

void Map::LoadTileMap(){

    //Open the TileSet and parse it as xml
    rapidxml::xml_document<> TilesetXml;
    std::ifstream Tilesetfile;
    Tilesetfile.open(Map::tileSetLocation);
    if (!Tilesetfile.is_open())
    {
        std::cerr << "Can't read xml file" << std::endl;
        return;
    }
    std::stringstream tilesetbuffer;
    tilesetbuffer << Tilesetfile.rdbuf();
    std::string tilesetfileContents = tilesetbuffer.str();
    Tilesetfile.close();
    TilesetXml.parse<0>(&tilesetfileContents[0]);
    
    // List to store texture source paths with the same ID as they do in the .tsx file
    list<string> listOfPaths;
    rapidxml::xml_node<>* tilesetNode = TilesetXml.first_node();
    list<string> paths;
    for (rapidxml::xml_node<> *child = tilesetNode->first_node("tile"); child != NULL; child = child->next_sibling("tile")) /*I got this for loop of stackoverflow i have no idea how it works but it does so we dont mess with it*/
    {
      paths.push_back(child->first_node()->first_attribute("source")->value());
      //cout << child->first_node()->first_attribute("source")->value(); //Makes a mess lol
    } 


    return;// I haven't finished the bit below so its will probably cause some sorta runtime error or somthing

    //////////////////////////////////////////////////////////////////////////////////////////




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
