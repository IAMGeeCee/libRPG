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

int GetChildCount(rapidxml::xml_node<> *Node) // Count child nodes of an XML node
{
    int Count = 0;
    for (rapidxml::xml_node<> *Child = Node->first_node(); Child != nullptr; Child = Child->next_sibling())
    {
        Count++;
    }
    return Count;
}

std::list<std::string> Split(const std::string &String, char Delimiter) // Split string by delimiter
{
    std::list<std::string> Tokens;
    std::string Token;
    std::istringstream TokenStream(String);
    while (std::getline(TokenStream, Token, Delimiter))
    {
        Tokens.push_back(Token);
    }
    return Tokens;
}

void Map::LoadTileMap()
{
    std::list<TileTextureInfo> TexturePaths = LoadTilesetXml(TileSetLocation); // Load tileset XML and get texture paths
    if (TexturePaths.empty())
    {
        std::cerr << "Failed to load texture paths from tileset XML" << std::endl;
        return;
    }

    if (!AreTexturesLoaded) // Textures are not loaded
    {
        Map::TileTextures = LoadTileTextures(TexturePaths); // Load tile textures
        AreTexturesLoaded = true;
    }

    if (!LoadTileMapAttributes(TileMapLocation)) // Load tilemap XML and get map attributes and report the error to the terminal if it fails
    {
        std::cerr << "Failed to load tile map attributes" << std::endl;
        return;
    }

    ParseAndRenderTiles(); // Parse CSV data and render tiles
}

std::list<TileTextureInfo> Map::LoadTilesetXml(const std::string &FilePath)
{
    rapidxml::xml_document<> TilesetXml;
    std::ifstream File(FilePath);
    if (!File.is_open())
    {
        std::cerr << "Can't read XML file: " << FilePath << std::endl;
        return {};
    }

    std::stringstream Buffer;
    Buffer << File.rdbuf();
    std::string FileContents = Buffer.str();
    File.close();
    TilesetXml.parse<0>(&FileContents[0]);

    std::list<TileTextureInfo> Paths;
    rapidxml::xml_node<> *TilesetNode = TilesetXml.first_node();
    if (!TilesetNode)
    {
        std::cerr << "Invalid Tileset XML format" << std::endl;
        return {};
    }

    for (rapidxml::xml_node<> *Child = TilesetNode->first_node("tile"); Child != nullptr; Child = Child->next_sibling("tile"))
    {
        auto ImageNode = Child->first_node("image");
        if (!ImageNode)
        {
            std::cerr << "Tile node missing image node" << std::endl;
            continue;
        }

        auto SourceAttr = ImageNode->first_attribute("source");
        if (!SourceAttr)
        {
            std::cerr << "Image node missing source attribute" << std::endl;
            continue;
        }

        TileTextureInfo TextureInfo;
        TextureInfo.Path = SourceAttr->value();
        TextureInfo.CanWalk = false; // Default value

        auto PropertiesNode = Child->first_node("properties");
        if (PropertiesNode)
        {
            auto Property = PropertiesNode->first_node("property");
            if (Property)
            {
                auto ValueAttr = Property->first_attribute("value");
                if (ValueAttr)
                {
                    TextureInfo.CanWalk = std::string(ValueAttr->value()) == "true";
                }
                else
                {
                    std::cerr << "Property node missing value attribute" << std::endl;
                }
            }
        }

        Paths.push_back(TextureInfo);
    }

    return Paths;
}

std::vector<TileTextureInfo> Map::LoadTileTextures(const std::list<TileTextureInfo> &Paths)
{
    std::vector<TileTextureInfo> Textures;
    for (const auto &Path : Paths)
    {
        TileTextureInfo Texture;
        Texture.CanWalk = Path.CanWalk;
        Texture.Path = Path.Path;
        Texture.Position.x = Path.Position.x; // Assign the X position
        Texture.Position.y = Path.Position.y; // Assign the Y position
        Texture.TileTexture = LoadTexture(Path.Path.c_str());
        Textures.push_back(Texture);
    }
    return Textures;
}

bool Map::LoadTileMapAttributes(const std::string &FilePath)
{
    rapidxml::xml_document<> TileMapXml;
    std::ifstream File(FilePath);
    if (!File.is_open())
    {
        std::cerr << "Can't read XML file: " << FilePath << std::endl;
        return false;
    }

    std::stringstream Buffer;
    Buffer << File.rdbuf();
    std::string FileContents = Buffer.str();
    File.close();
    TileMapXml.parse<0>(&FileContents[0]);

    rapidxml::xml_node<> *FirstNode = TileMapXml.first_node();
    if (!FirstNode)
    {
        std::cerr << "Invalid TileMap XML format" << std::endl;
        return false;
    }

    auto LayerNode = FirstNode->first_node("layer");
    if (!LayerNode || !LayerNode->first_attribute("width") || !LayerNode->first_attribute("height"))
    {
        std::cerr << "Missing map layer attributes" << std::endl;
        return false;
    }

    MapWidth = std::stoi(LayerNode->first_attribute("width")->value());
    MapHeight = std::stoi(LayerNode->first_attribute("height")->value());

    return true;
}

void Map::ParseAndRenderTiles()
{
    rapidxml::xml_document<> TileMapXml;
    std::ifstream File(TileMapLocation);
    if (!File.is_open())
    {
        std::cerr << "Can't read XML file: " << TileMapLocation << std::endl;
        return;
    }

    std::stringstream Buffer;
    Buffer << File.rdbuf();
    std::string FileContents = Buffer.str();
    File.close();
    TileMapXml.parse<0>(&FileContents[0]);

    rapidxml::xml_node<> *FirstNode = TileMapXml.first_node("map");

    MapHeight = std::stoi(FirstNode->first_attribute("height")->value());
    MapWidth = std::stoi(FirstNode->first_attribute("width")->value());
    TileHeight = std::stoi(FirstNode->first_attribute("tileheight")->value());
    TileWidth = std::stoi(FirstNode->first_attribute("tilewidth")->value());

    auto LayerNode = FirstNode->first_node("layer");
    auto LayerDataNode = LayerNode->first_node("data");
    if (!LayerDataNode || !LayerDataNode->value())
    {
        std::cerr << "Could not read tilemap data" << std::endl;
        return;
    }

    std::string CsvData = LayerDataNode->value();
    std::stringstream Ss(CsvData);
    std::string Token;
    int X = 0, Y = 0;
    int TileID;

    Tiles.resize(MapHeight);
    for (int I = 0; I < MapHeight; ++I)
    {
        Tiles[I].resize(MapWidth);
    }

    while (std::getline(Ss, Token, ','))
    {
        TileID = std::stoi(Token);
        if (TileID != 0)
        { // Assuming 0 means no tile
            // Get the texture for this tile
            Texture2D Texture = TileTextures[TileID - 1].TileTexture;

            // TODO: Get the X an Y to actually be right.
            TileTextures[TileID - 1].Position.x = X;
            TileTextures[TileID - 1].Position.y = Y;

            // Calculate position to draw the tile
            Vector2 Position = {static_cast<float>(X * TileWidth), static_cast<float>(Y * TileHeight)};

            // Define source and destination rectangles
            Rectangle SourceRect = {0, 0, static_cast<float>(Texture.width), static_cast<float>(Texture.height)};
            Rectangle DestRect = {Position.x, Position.y, static_cast<float>(TileWidth), static_cast<float>(TileHeight)};

            // If tile width or height is greater than the texture's width or height, scale it
            if (TileWidth > Texture.width || TileHeight > Texture.height)
            {
                float ScaleX = static_cast<float>(TileWidth) / static_cast<float>(Texture.width);
                float ScaleY = static_cast<float>(TileHeight) / static_cast<float>(Texture.height);
                DestRect.width *= ScaleX;
                DestRect.height *= ScaleY;
            }

            // Draw the tile
            DrawTexturePro(Texture, SourceRect, DestRect, Vector2{0, 0}, 0, WHITE);
        }

        // Move to the next tile position

        X++;
        if (X >= MapWidth)
        {
            X = 0;
            Y++;
        }
    }
}

void Map::UnloadTileTextures()
{
    for (auto &Texture : TileTextures)
    {
        UnloadTexture(Texture.TileTexture);
    }

    TileTextures.clear(); // Clear the vector after unloading

    AreTexturesLoaded = false;
}

bool Map::IsTileWalkable(int X, int Y)
{
    if (X < 0 || X >= MapWidth || Y < 0 || Y >= MapHeight)
    {
        // Out of bounds
        return false;
    }

    return Tiles[Y][X].CanWalk;
}

void Map::DrawMapToConsole()
{
    for (int Y = 0; Y < MapHeight; ++Y)
    {
        for (int X = 0; X < MapWidth; ++X)
        {
            if (Tiles[Y][X].TileTexture.id < 10)
            {
                std::cout << Tiles[Y][X].TileTexture.id << "" << ",";
            }
            else
            {
                std::cout << Tiles[Y][X].TileTexture.id << ",";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl
              << "DEBUG INFO" << std::endl;
    std::cout << std::endl
              << "Map Width: " << Map::MapWidth << std::endl;
    std::cout << "Map Height: " << Map::MapHeight << std::endl;
    std::cout << "Tile Height: " << Map::TileHeight << std::endl;
    std::cout << "Tile Width: " << Map::TileWidth << std::endl;
    std::cout << "Map Location: " << Map::TileMapLocation << std::endl;
    std::cout << "Set Location: " << Map::TileSetLocation << std::endl;
    std::cout << "Number of Tiles: " << Map::Tiles.size() * Map::Tiles[1].size() << std::endl;
    std::cout << "Number of Textures: " << Map::TileTextures.size() << std::endl;
}