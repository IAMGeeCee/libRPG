#include <iostream>
#include "Game.h"
#include <raylib.h>
#include <functional>

int MainLoop()
{
	BeginDrawing();

	DrawFPS(50,50);

	EndDrawing();

	return 0;
}


int main ()
{
	std::cout << " Hello World!";
	Game testgame = Game(&MainLoop);
	return 0;
}
