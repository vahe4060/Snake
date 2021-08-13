#pragma once
#include <iostream>
#include <map>
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"

class textureManager
{
private:
	textureManager();
	~textureManager();
	static textureManager* instance_;


	textureManager& operator=(const textureManager&) = delete;
	textureManager(const textureManager&) = delete;
public:
	static textureManager* instance();

	bool load(const char* filename, const char* id, SDL_Renderer* renderer);
	void draw(const char* id, int x, int y, int w, int h, SDL_Renderer* ren, SDL_RendererFlip flip);
	void drawFrame(const char* id, float x, float y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* ren, SDL_RendererFlip flip);
	void clearTextureFromMap(const char* id);

private:
	std::map<const char*, SDL_Texture*> texturesMap;
};

