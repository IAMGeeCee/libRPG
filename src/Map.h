#include <raylib.h>
#include <raymath.h>
#include <string>

using namespace std;  

class Map {
public:
  int tileHeight;
  int tileWidth;
  int tileMapHeight;
  int tileMapWidth;
  string tileSetLocation;
  string tileMapLocation;
  void LoadTileMap();

}
