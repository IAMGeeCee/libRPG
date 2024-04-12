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
  int tileHeight;
  int tileWidth;
  int mapWidth;
  int mapHeight;

};
