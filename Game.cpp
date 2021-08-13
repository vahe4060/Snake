#include "Game.h"


game* game::instance_ = nullptr;

game* game::instance()
{
	if (instance_ == nullptr)
		instance_ = new game();

	return instance_;
}

game::game() 
	: isRunning(false),
	  isGameOver(false),
	  window(nullptr),
   	  renderer(nullptr)
{
}

game::~game()
{
	std::cout << "game deleted\n";
}

bool game::init(const char* windowName, int xpos, int ypos, Uint32 flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		if (flags == 0) flags = SDL_WINDOW_SHOWN;

		window = SDL_CreateWindow(windowName, xpos, ypos, WinWidth, WinHeight, flags);
		if (!window) return false;

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (!renderer) return false;
	
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		
		///// draw the board
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		for (int i = 0; i <= 20; i++)
		{
			SDL_RenderDrawLine(renderer, 0, i * AreaSide / 20,	AreaSide, i * AreaSide / 20	);
			SDL_RenderDrawLine(renderer, i * AreaSide / 20, 0,	i * AreaSide / 20, AreaSide	);
		}
		/////////////////


		fruitManager::instance()->drawFruitOnScreen(15, 15);

		player = new Player(new loaderParams(241,241,29,29,"player"));

		


		////// Create play/pause button
		SDL_Surface* tempsurf = IMG_Load("assets/buttons.png");
		if (!tempsurf) return false;
		texture = SDL_CreateTextureFromSurface(renderer, tempsurf);
		if (!texture) return false;

		ButtonSrcRect.x = ButtonSrcRect.y = 0;
		ButtonSrcRect.w = 50;
		ButtonSrcRect.h = 100;

		ButtonDestRect.x = 650;
		ButtonDestRect.y = 0;
		ButtonDestRect.w = 100;
		ButtonDestRect.h = 200;

		SDL_FreeSurface(tempsurf);
		////////////////////
		
		isPaused = true;
		isRunning = true;
		return true;
	}
	else 
		return false;
}

void game::update()
{

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	
	if (!isGameOver)
	{
		if (!isPaused) {
			player->update();
			ButtonSrcRect.x = 50;
		}
		else {
			ButtonSrcRect.x = 0;
		}
	}
}

void game::render()
{
	SDL_RenderCopy(renderer, texture, &ButtonSrcRect, &ButtonDestRect);

		player->render();
	
	SDL_RenderPresent(renderer);
}



void game::handleEvents()
{
	inputHandler::instance()->update();



	if (inputHandler::instance()->isKeyDown(SDL_SCANCODE_RETURN)) {
		isPaused = false;
	}
	if (inputHandler::instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
			isPaused = true;
	}
	if (inputHandler::instance()->isKeyDown(SDL_SCANCODE_R)) {
		restart();
	}


	if (inputHandler::instance()->isMouseButtonDown(0))
	{
		if (inputHandler::instance()->getMousePos().first < (ButtonDestRect.x + 100) && inputHandler::instance()->getMousePos().first > ButtonDestRect.x
			&& inputHandler::instance()->getMousePos().second < (ButtonDestRect.y + 100) && inputHandler::instance()->getMousePos().second > ButtonDestRect.y)
		{
			bool nextState = (isPaused == true) ? false : true;
			isPaused = nextState;
			SDL_Delay(150); // just to be able to receive the click
		}

		if (inputHandler::instance()->getMousePos().first < (ButtonDestRect.x + 100) && inputHandler::instance()->getMousePos().first > ButtonDestRect.x
			&& inputHandler::instance()->getMousePos().second < (ButtonDestRect.y + 200) && inputHandler::instance()->getMousePos().second >(ButtonDestRect.y + 100))
		{	
			std::cout << "restart\n";
			restart();
		}
	}
	
}


void game::addscore()
{
	score++;
	std::cout << "score:  " << score << std::endl;
}


void game::gameOver()
{
	isPaused = true;
	isGameOver = true;
	std::cout << "Game Over\n";
}

void game::quit()
{
	isRunning = false;

}

void game::clean()
{
	if (player) {
		player->clean();
		delete player;
	}
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}


void game::restart()
{
	isGameOver = false;
	isPaused = false;
	score = 0;
	SDL_Delay(100);

	if (player) {
		player->clean();
		delete player;
		//SDL_RenderClear(renderer);
	}
	player = new Player(new loaderParams(241, 241, 29, 29, "player"));

}