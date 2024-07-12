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
    int x;
    int y;
    Texture2D tiletexture;
};

class Map {
public:
    string tileSetLocation;
    string tileMapLocation;
    void LoadTileMap();
    void UnloadTileTextures();

private:
    void LoadTextures(const list<string>& paths, vector<Texture2D>& tileTextures);
    list<TileTextureInfo> LoadTilesetXml(const string& filePath);
    bool LoadTileMapAttributes(const string& filePath);
    void ParseAndRenderTiles();
    vector<TileTextureInfo> LoadTileTextures(const list<TileTextureInfo>& paths);
    std::vector<TileTextureInfo> tileTextures;

    int mapWidth = 100;
    int mapHeight = 100;
    int tileWidth = 0;
    int tileHeight = 0;

protected:
};
