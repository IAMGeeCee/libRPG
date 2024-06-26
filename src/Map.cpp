#include "Map.h"
#include "../external/rapidxml-1.13/rapidxml.hpp"
#include <list>
#include <ostream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <raylib.h>
#include <vector>

// Count child nodes of an XML node
int getChildCount(rapidxml::xml_node<> *n) {
    int count = 0;
    for (rapidxml::xml_node<> *child = n->first_node(); child != nullptr; child = child->next_sibling()) {
        count++;
    }
    return count;
}

// Split string by delimiter
std::list<std::string> split(const std::string& s, char delimiter) {
    std::list<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void Map::LoadTileMap() {
    // Load tileset XML and get texture paths
    std::list<std::string> texturePaths = LoadTilesetXml(tileSetLocation);
    if (texturePaths.empty()) {
        std::cerr << "Failed to load texture paths from tileset XML" << std::endl;
        return;
    }

    // Load tile textures
    Map::tileTextures = LoadTileTextures(texturePaths);

    // Load tilemap XML and get map attributes
    if (!LoadTileMapAttributes(tileMapLocation)) {
        std::cerr << "Failed to load tile map attributes" << std::endl;
        return;
    }

    // Parse CSV data and render tiles
    ParseAndRenderTiles();
}

std::list<std::string> Map::LoadTilesetXml(const std::string& filePath) {
    rapidxml::xml_document<> TilesetXml;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Can't read XML file: " << filePath << std::endl;
        return {};
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string fileContents = buffer.str();
    file.close();
    TilesetXml.parse<0>(&fileContents[0]);

    std::list<std::string> paths;
    rapidxml::xml_node<>* tilesetNode = TilesetXml.first_node();
    if (!tilesetNode) {
        std::cerr << "Invalid Tileset XML format" << std::endl;
        return {};
    }

    for (rapidxml::xml_node<> *child = tilesetNode->first_node("tile"); child != nullptr; child = child->next_sibling("tile")) {
        if (child->first_node()) {
            auto sourceAttr = child->first_node()->first_attribute("source");
            if (sourceAttr) {
                paths.push_back(sourceAttr->value());
            } else {
                std::cerr << "Tile node missing source attribute" << std::endl;
            }
        }
    }

    return paths;
}

std::vector<Texture2D> Map::LoadTileTextures(const std::list<std::string>& paths) {
    std::vector<Texture2D> textures;
    for (const auto& path : paths) {
        Texture2D texture = LoadTexture(path.c_str());
        textures.push_back(texture);
    }
    return textures;
}

bool Map::LoadTileMapAttributes(const std::string& filePath) {
    rapidxml::xml_document<> TileMapXml;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Can't read XML file: " << filePath << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string fileContents = buffer.str();
    file.close();
    TileMapXml.parse<0>(&fileContents[0]);

    rapidxml::xml_node<> *firstNode = TileMapXml.first_node();
    if (!firstNode) {
        std::cerr << "Invalid TileMap XML format" << std::endl;
        return false;
    }

    auto layerNode = firstNode->first_node("layer");
    if (!layerNode || !layerNode->first_attribute("width") || !layerNode->first_attribute("height")) {
        std::cerr << "Missing map layer attributes" << std::endl;
        return false;
    }

    mapWidth = std::stoi(layerNode->first_attribute("width")->value());
    mapHeight = std::stoi(layerNode->first_attribute("height")->value());

    return true;
}

void Map::ParseAndRenderTiles() {
    rapidxml::xml_document<> TileMapXml;
    std::ifstream file(tileMapLocation);
    if (!file.is_open()) {
        std::cerr << "Can't read XML file: " << tileMapLocation << std::endl;
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string fileContents = buffer.str();
    file.close();
    TileMapXml.parse<0>(&fileContents[0]);

    rapidxml::xml_node<> *firstNode = TileMapXml.first_node("map");
    
    Map::tileHeight = std::stoi(firstNode->first_attribute("tileheight")->value());
    Map::tileWidth = std::stoi(firstNode->first_attribute("tilewidth")->value());

    auto layerNode = firstNode->first_node("layer");
    auto layerDataNode = layerNode->first_node("data");
    if (!layerDataNode || !layerDataNode->value()) {
        std::cerr << "Could not read tilemap data" << std::endl;
        return;
    }

    std::string csvData = layerDataNode->value();
    std::stringstream ss(csvData);
    std::string token;
    int tileID;
    int x = 0, y = 0;

    while (std::getline(ss, token, ',')) {
        tileID = std::stoi(token);
        if (tileID != 0) { // Assuming 0 means no tile
            // Get the texture for this tile
            Texture2D texture = tileTextures[tileID - 1];

            // Calculate position to draw the tile
            Vector2 position = {static_cast<float>(x * tileWidth), static_cast<float>(y * tileHeight)};

            // Define source and destination rectangles
            Rectangle sourceRect = {0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)};
            Rectangle destRect = {position.x, position.y, static_cast<float>(tileWidth), static_cast<float>(tileHeight)};
            
            // If tile width or height is greater than the texture's width or height, scale it
            if (tileWidth > texture.width || tileHeight > texture.height) {
                float scaleX = static_cast<float>(tileWidth) / static_cast<float>(texture.width);
                float scaleY = static_cast<float>(tileHeight) / static_cast<float>(texture.height);
                destRect.width *= scaleX;
                destRect.height *= scaleY;
            }

            // Draw the tile
            DrawTexturePro(texture, sourceRect, destRect, Vector2{0, 0}, 0, WHITE);
        }

        // Move to the next tile position
        x++;
        if (x >= mapWidth) {
            x = 0;
            y++;
        }
    }
}

void Map::UnloadTileTextures() {
    for (auto& texture : tileTextures) {
        UnloadTexture(texture);
    }
    tileTextures.clear(); // Clear the vector after unloading
}
