# 🎮 libRPG
A game engine for C++ written with Raylib thats lets you manage a full top down game with a single instance of a class (sorta) while still being completly customisable.  

To get started check out the [wiki](https://github.com/IAMGeeCee/libRPG/wiki). 

Also this is a very early version so it doesn't do much yet

# 💡 Features
## 🗺️ Tiled Map loading
libRPG supports loading Tiled tilemaps and tilesets. You can download the Tiled tile map editor software from https://www.mapeditor.org/
### Current Tiled limitations
Currently the engine will only understand tilesets with seperate images and not one single image with all the tiles on (this may come in a later version). We also do not currently support infinate tile maps so please use a fixed size.
## 🧑 Character
In libRPG there's no need to worry about setting up character controllers as this comes pre set up with the library, Its also very customisable with features such as the developer being able to change the keybinds and more to come such as animations.
## ⛏️ Completely customisable
If libRPG can't do what you want to do, you can directly interact with the raylib (the graphics engine this runs on) backend.
## ✨ More coming
Theres a lot more to come, have a look in the projects for a roadmap.
## 🤔 How does it work?
In libRPG you create a function and pass it in the Game class (the class used for interacting with the engine). And then you can just use basic C++ to use the engine like this (this code doesn't actually work, don't try it)
```
  if(score == 100){
      Game.doAThing();
  }
```
but you can also use this to directly interact with raylib like this: (this code doesn't actually work, don't try it)
```
  if(Game.player.IsDead()){
      raylib::DrawRectangle()
  }
```
