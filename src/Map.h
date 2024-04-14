#include <string>

using namespace std;  

class Map {
public:
  string tileSetLocation;
  string tileMapLocation;
  void LoadTileMap();
private:
  void LoadTextures();
  void DrawTileMap();
  int mapWidth = 100;
  int mapHeight = 100;
  int tileWidth = 64;
  int tileHeight = 64;
};
