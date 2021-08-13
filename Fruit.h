#pragma once
#include "SDL.h"
#include "SDL_image.h"

class fruitManager
{
public:
	
	/*xpos- xposition of the cubic's center
	ypos- yposition of the cubic's center*/
	void drawFruitOnScreen(int xpos, int ypos);
	SDL_Rect fruitPos() { return destRect; }
	void generateNextPos();
	static fruitManager* instance();
private:
	
	static fruitManager* instance_;
	fruitManager();
	~fruitManager();
	SDL_Texture* fruit = nullptr;
	SDL_Rect destRect;
	int imgWidth, imgHeight;

	bool isInsidePlayer();
};

