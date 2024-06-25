#include <string>
#include <vector>
#include <list>
#include <raylib.h>

using namespace std;

class Map {
public:
    string tileSetLocation;
    string tileMapLocation;
    void LoadTileMap();
    void UnloadTileTextures();

private:
    void LoadTextures(const list<string>& paths, vector<Texture2D>& tileTextures);
    list<string> LoadTilesetXml(const string& filePath);
    bool LoadTileMapAttributes(const string& filePath);
    void ParseAndRenderTiles();
    vector<Texture2D> LoadTileTextures(const list<string>& paths);
    std::vector<Texture2D> tileTextures;

    int mapWidth = 100;
    int mapHeight = 100;
    int tileWidth = 0;
    int tileHeight = 0;

protected:
};
