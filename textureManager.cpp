#include "textureManager.h"
#include <cassert>

textureManager::textureManager()
{
}
textureManager::~textureManager()
{
}

textureManager* textureManager::instance_ = nullptr;

textureManager* textureManager::instance()
{
	if (instance_ == nullptr)
		instance_ = new textureManager();

	assert(instance_);
	return instance_;
}


bool textureManager::load(const char* filename, const char* id, SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = IMG_Load(filename);
	if (!tempSurface) return false;

	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	if (tempTexture)
	{
		texturesMap[id] = tempTexture;
		return true;
	}
	return false;
}


void textureManager::draw(const char* id, int x, int y, int w, int h, SDL_Renderer* ren, SDL_RendererFlip flip)
{
	SDL_Rect srcRect, destRect;
	srcRect.x = srcRect.y = 0;
	destRect.x = x;
	destRect.y = y;

	srcRect.w = destRect.w = w;
	srcRect.h = destRect.h = h;

	SDL_RenderCopyEx(ren, texturesMap[id], &srcRect, &destRect, 0, 0, flip);
}

void textureManager::drawFrame(const char* id, float x, float y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* ren, SDL_RendererFlip flip)
{
	SDL_Rect srcRect, destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	destRect.x = x;
	destRect.y = y;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	SDL_RenderCopyEx(ren, texturesMap[id], &srcRect, &destRect, 0, 0, flip);
}


void textureManager::clearTextureFromMap(const char* id)
{
	texturesMap.erase(id);
}