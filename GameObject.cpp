#include "GameObject.h"
#include "Game.h"
#include "Fruit.h"


Player::Player(const loaderParams* params) :
	x(params->x()),
	y(params->y()),
	width(params->width()),
	height(params->height())
{
	nextPos.x = x;
	nextPos.y = y;
	nextPos.w = width;
	nextPos.h = height;

	//////
	Src.x = 0;
	Src.y = 0;

	Src.w = 20;
	Src.h = 20;

	/////

	//// loading the snake head to the game::renderer
	tempsurface = IMG_Load("assets/snakehead.png");
	playerHeadTexture = SDL_CreateTextureFromSurface(game::instance()->getRenderer(), tempsurface);
	SDL_RenderCopy(game::instance()->getRenderer(), playerHeadTexture, 0, &nextPos);

	snake.emplace_back(new cube(nextPos, playerHeadTexture));

	///// loading the snake body to the game::renderer
	tempsurface = IMG_Load("assets/snakebody.png");
	playerBodyTexture = SDL_CreateTextureFromSurface(game::instance()->getRenderer(), tempsurface);


	SDL_RenderCopy(game::instance()->getRenderer(), playerBodyTexture, 0, &nextPos);
	


	//SDL_SetRenderDrawColor(game::instance()->getRenderer(), 255, 0, 0, 0);


	delete params;
}

Player::~Player()
{
}

void Player::clean()
{
	for (auto i : snake)
	{
		SDL_RenderFillRect(game::instance()->getRenderer(), &(i->coordinates));
		delete i;
	}
	SDL_FreeSurface(tempsurface);
}

void Player::render()
{
	SDL_SetRenderDrawColor(game::instance()->getRenderer(), 0, 0, 0, 0);
	SDL_RenderFillRect(game::instance()->getRenderer(), &previousPos);

	
	for (std::vector<cube*>::reverse_iterator i = snake.rbegin(); i != snake.rend(); ++i)
	{
		SDL_RenderCopy(game::instance()->getRenderer(),(*i)->texture, &Src, &((*i)->coordinates));
	}
	//SDL_RenderCopy(game::instance()->getRenderer(), snake[0]->texture, &Src, &(snake[0]->coordinates));
}

void Player::update()
{
	previousPos = snake.back()->coordinates;
	int nextDirection = inputHandler::instance()->Direction();

	if (nextDirection != 0 && nextDirection != direction && nextDirection != Opposite(direction)) 
		direction = nextDirection;


	for (int i = 1; i < snake.size(); i++)
	{
		if (snake[0]->coordinates.x == snake[i]->coordinates.x
		 && snake[0]->coordinates.y == snake[i]->coordinates.y)
		{
			std::cout << "GAME OVER" << std::endl;
			Src.x = 20;
			
			game::instance()->gameOver();
			break;
		}
	}

	drive();
}


void Player::drive()
{
	SDL_Delay(75);
	switch (direction)
	{
	case UP: {
		nextPos.y -= (height + 1); // size of drawing cube's height
		if (nextPos.y < 0) nextPos.y = AreaSide - height;
		break;
	}
	case DOWN: {
		nextPos.y += (height + 1);
		if (nextPos.y >= AreaSide) nextPos.y = 1;
		break;
	}
	case LEFT: {
		nextPos.x -= (width + 1); // size of drawing cube's width
		if (nextPos.x < 0) nextPos.x = AreaSide - width;
		break; 
	}
	case RIGHT: {
		nextPos.x += (width + 1);
		if (nextPos.x >= AreaSide) nextPos.x = 1;
		break; 
	}
	default:
		break;
	}
	
	//   nextpos.x = UP(x) + DOWN(x) + LEFT(x) + RIGHT(x)    ,where   x = direction

	for (size_t i = snake.size() - 1; i > 0; i--)
	{
		int j = i - 1;
		snake[i]->coordinates = snake[j]->coordinates;
	}

	snake[0]->coordinates = nextPos;


	if (nextPos.x == fruitManager::instance()->fruitPos().x
	 && nextPos.y == fruitManager::instance()->fruitPos().y)
	{
		addFromBack();
		game::instance()->addscore();
		fruitManager::instance()->generateNextPos();
	}

}

void Player::addFromBack()
{
	cube* newcube = new cube(previousPos,playerBodyTexture);

	snake.emplace_back(newcube);
	
	switch (direction)
	{
	case UP: {
		previousPos.y += (height + 1);  // size of drawing cube's height
		if (previousPos.y >= AreaSide) previousPos.y = 1;
		break;
	}
	case DOWN: {
		previousPos.y -= (height + 1);
		if (previousPos.y < 0) previousPos.y = AreaSide - height;
		break;
	}
	case LEFT: {
		previousPos.x += (width + 1);  // size of drawing cube's height
		if (previousPos.x >= AreaSide) previousPos.x = 1;
		break;
	}
	case RIGHT: {
		previousPos.x -= (width + 1);
		if (previousPos.x < 0) previousPos.x = AreaSide - width;
		break;
	}
	default:
		break;
	}



}
