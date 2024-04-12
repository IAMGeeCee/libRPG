#include "Map.h"
#include "../external/rapidxml-1.13/rapidxml.hpp"
#include <list>
#include <ostream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <raylib.h>
#include <strstream>
#include <vector>

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

//GPT 3.5 lol
std::list<std::string> split(const std::string& s, char delimiter) {
    std::list<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
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
    Map::tileHeight = atoi(tilesetNode->first_attribute("tileheight")->value());
    Map::tileWidth = atoi(tilesetNode->first_attribute("tilewidth")->value());
    Map::tileHeight = 64;
    Map::tileWidth = 64;
    list<string> paths;
    for (rapidxml::xml_node<> *child = tilesetNode->first_node("tile"); child != NULL; child = child->next_sibling("tile")) /*Stack overflow lol*/
    {
      paths.push_back(child->first_node()->first_attribute("source")->value());
    }
    /////////////////////////////////////////////////////////////////////////////////////////
  


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
    
    //Get the maps attributes
    rapidxml::xml_node<> *firstNode = TileMapXml.first_node();
    Map::mapWidth = atoi(firstNode->first_node("layer")->first_attribute("width")->value());
    Map::mapHeight = atoi(firstNode->first_node("layer")->first_attribute("width")->value());
  

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
      //This section of the code was almost all helped by ai cuz idk what im doing with this


      //Creates list of all the textures
      std::vector<Texture2D> tileTextures;
      for (const auto &path : paths)
      {
          Texture2D texture = LoadTexture(path.c_str());
          tileTextures.push_back(texture);
      }

      //Parse the csv
      std::string csvData = layerDataNode->value();
      std::stringstream ss(csvData);
      std::string token;
      int tileID;
      int x = 0, y = 0;
      while (std::getline(ss, token, ','))
      {
        tileID = std::stoi(token);
        if (tileID != 0) // Assuming 0 means no tile
        {
            // Get the texture for this tile
            Texture2D texture = tileTextures[tileID - 1];

            // Calculate position to draw the tile
            Vector2 position = {static_cast<float>(x * tileWidth), static_cast<float>(y * tileHeight)};
            
            // If tile width or height is greater than the texture's width or height, scale it
            Rectangle sourceRect = {0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)};
            Rectangle destRect = {position.x, position.y, static_cast<float>(tileWidth), static_cast<float>(tileHeight)};
            if (tileWidth > texture.width || tileHeight > texture.height) {
                // Calculate scale factors
                float scaleX = static_cast<float>(tileWidth) / static_cast<float>(texture.width);
                float scaleY = static_cast<float>(tileHeight) / static_cast<float>(texture.height);
                // Stretch the texture
                destRect.width *= scaleX;
                destRect.height *= scaleY;
            }

            // Draw the tile
            DrawTexturePro(texture, sourceRect, destRect, Vector2{0, 0}, 0, WHITE);
        
        }

        // Move to the next tile position
        x++;
        if (x >= mapWidth)
        {
          x = 0;
          y++;
        }
    }
    }    
}
