#include "Game.h"
#include "Fruit.h"
#include <cassert>
#include "GameObject.h"
#include <time.h>

fruitManager::fruitManager()
{
	SDL_Surface* tempsurf = IMG_Load("assets/fruit.png");
	if (!tempsurf) {
		std::cerr << "coulnd't load fruit..\n";
		return;
	}
	fruit = SDL_CreateTextureFromSurface(game::instance()->getRenderer(), tempsurf);
	if (!fruit) {
		std::cerr << "could't load the fruit..\n";
		return;
	}

	imgWidth = 29;
	imgHeight = 29;
	SDL_FreeSurface(tempsurf);
}

fruitManager::~fruitManager()
{
}

fruitManager* fruitManager::instance_ = nullptr;

fruitManager* fruitManager::instance()
{
	if (instance_ == nullptr)
		instance_ = new fruitManager();

	assert(instance_ != nullptr);
	return instance_;
}


void fruitManager::drawFruitOnScreen(int xpos, int ypos) 
{
	destRect.x = xpos - imgWidth / 2;

	destRect.y = ypos - imgHeight / 2;

	destRect.w = imgWidth;
	destRect.h = imgHeight;

	SDL_RenderCopy(game::instance()->getRenderer(),fruit, 0, &destRect);
	SDL_RenderPresent(game::instance()->getRenderer());
}


void fruitManager::generateNextPos()
{
	std::srand(time(0));
	destRect.x = (rand() % 20) * 30 + 1;
	destRect.y = (rand() % 20) * 30 + 1;

	while (isInsidePlayer())
	{
		std::srand(time(0));
		destRect.x = (rand() % 20) * 30 + 1;
		destRect.y = (rand() % 20) * 30 + 1;
	} 

	SDL_RenderCopy(game::instance()->getRenderer(),fruit, 0, &destRect);
	SDL_RenderPresent(game::instance()->getRenderer());
}


bool fruitManager::isInsidePlayer()
{
	for (auto i : (game::instance()->getPlayer()->getSnake()))
	{
		if (destRect.x == i->coordinates.x && destRect.y == i->coordinates.y)
			return true;
	}
	return false;
}