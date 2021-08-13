#pragma once
#include "LoaderParams.h"
#include "inputHandler.h"
#include <vector>

#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4

#define Opposite(direction) ( direction == UP ? DOWN: (direction == LEFT ? RIGHT: (direction == RIGHT ? LEFT: UP))  )


class Player
{
	struct cube
	{
		SDL_Rect coordinates;
		SDL_Texture* texture = nullptr;
		cube(SDL_Rect Coordinates, SDL_Texture* Texture) : coordinates(Coordinates), texture(Texture) {}
	};


public:
	Player(const loaderParams*);
	virtual ~Player();

	SDL_Rect playerPos() { return nextPos; }

	void update();
	void render();
	void clean();
	std::vector<cube*> getSnake() 
	{
		return snake;
	}

private:
	int x, y;
	int width, height;
	SDL_Rect nextPos;
	SDL_Rect previousPos;

	SDL_Rect Src;

	SDL_Surface* tempsurface = nullptr;
	SDL_Texture* playerHeadTexture = nullptr;
	SDL_Texture* playerBodyTexture = nullptr;

	int direction = RIGHT;
	
	void drive();
	void addFromBack();

	std::vector<cube*> snake;
};

