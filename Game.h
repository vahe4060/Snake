#pragma once
#include "GameObject.h"
#include "SDL.h"
#include "inputHandler.h"
#include "Fruit.h"

/// window is 600 x 800
#define WinHeight  600
#define WinWidth   800
/// the playing area side
#define AreaSide 600

class game
{
private:
	static game* instance_ ;
	game();
	

	game& operator=(game&) = delete;
	game(game&) = delete;

public:
	static game* instance();
	~game();
	bool init(const char* windowName, int xpos, int ypos, Uint32 flags);

	SDL_Renderer* getRenderer() { return renderer; }
	Player* getPlayer() { return player; }

	void update();
	void render();
	void addscore();
	void handleEvents();
	void gameOver();
	void quit();
	void clean();

	void restart();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Player* player=nullptr;
	int score = 0;

	SDL_Rect ButtonSrcRect, ButtonDestRect;
	SDL_Texture* texture= nullptr;
	bool released = true;
public:
	bool isRunning;
	bool isPaused;
	bool isGameOver;
	
};

