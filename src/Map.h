#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <list>
#include <raylib.h>

class TileTextureInfo
{
public:
    std::string Path = "";
    bool CanWalk = true;
    Vector2 Position = {0, 0};
    Texture2D TileTexture;
};

class Map
{
public:
    std::string TileSetLocation;
    std::string TileMapLocation;
    void LoadTileMap();
    void UnloadTileTextures();
    bool IsTileWalkable(int x, int y);
    void Map::DrawMapToConsole();
    int TileWidth = 0;
    int TileHeight = 0;

private:
    void LoadTextures(const std::list<std::string> &paths, std::vector<Texture2D> &tileTextures);
    std::list<TileTextureInfo> LoadTilesetXml(const std::string &filePath);
    bool LoadTileMapAttributes(const std::string &filePath);
    bool AreTexturesLoaded = false;
    void ParseAndRenderTiles();
    std::vector<TileTextureInfo> LoadTileTextures(const std::list<TileTextureInfo> &paths);
    std::vector<TileTextureInfo> TileTextures;
    std::vector<std::vector<TileTextureInfo>> Tiles;

    int MapWidth = 100;
    int MapHeight = 100;

protected:
};

#endif