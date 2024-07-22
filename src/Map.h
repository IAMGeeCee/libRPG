#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <list>
#include <raylib.h>

using namespace std;

class TileTextureInfo
{
    public:
    string path = "";
    bool canWalk = true;
    Vector2 position = {0,0};
    Texture2D tiletexture;
};

class Map {
public:
    string tileSetLocation;
    string tileMapLocation;
    void LoadTileMap();
    void UnloadTileTextures();
    bool IsTileWalkable(int x, int y);
    void Map::DrawMapToConsole();
    int tileWidth = 0;
    int tileHeight = 0;

private:
    void LoadTextures(const list<string>& paths, vector<Texture2D>& tileTextures);
    list<TileTextureInfo> LoadTilesetXml(const string& filePath);
    bool LoadTileMapAttributes(const string& filePath);
    bool areTexturesLoaded = false;
    void ParseAndRenderTiles();
    vector<TileTextureInfo> LoadTileTextures(const list<TileTextureInfo>& paths);
    std::vector<TileTextureInfo> tileTextures;
    std::vector<std::vector<TileTextureInfo>> tiles;

    int mapWidth = 100;
    int mapHeight = 100;

protected:
};

#endif 