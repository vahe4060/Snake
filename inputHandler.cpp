#include "inputHandler.h"
#include "Game.h"
#include "GameObject.h"

inputHandler* inputHandler::instance_ = nullptr;

inputHandler* inputHandler::instance()
{
	if (instance_ == nullptr)
		instance_ = new inputHandler();

	return instance_;
}

inputHandler::~inputHandler()
{
	std::cout << "\n\ninput handler went out of scope....\n\n";
}

inputHandler::inputHandler()
{
	clear();
	keystate = const_cast<Uint8*>(SDL_GetKeyboardState(NULL));
}

void inputHandler::clear()
{
	for (int i = 0; i < 3; i++)
		MouseButtons[i] = false;
}

std::pair<int, int> inputHandler::getMousePos()
{
	return MousePosition;
}



bool inputHandler::isMouseButtonDown(int buttonNumber)
{
	return MouseButtons[buttonNumber];
}


bool inputHandler::isKeyDown(SDL_Scancode key)
{
	if (keystate != nullptr)
	{
		if (keystate[key] == 1)
			return true;
		else
		return false;
	}
	return false;
}



void inputHandler::update()
{
	SDL_Event Event;

	while (SDL_PollEvent(&Event))
	{
		switch (Event.type)
		{
		case SDL_MOUSEBUTTONUP:
		{
			onMouseButtonUp(Event);  break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			onMouseButtonDown(Event); break;
		}
		case SDL_MOUSEMOTION:
		{	
			onMouseMotion(Event); break;
		}
		case SDL_KEYDOWN:
		{
			onKeyDown(Event); break;
		}
		case SDL_KEYUP:
		{	
			onKeyUp(Event); break;
		}

		case SDL_QUIT:
		{
			game::instance()->quit(); break;
		}
		default:
			break;
		}
		//SDL_Delay(10);
	}

}

void inputHandler::onMouseMotion(SDL_Event& Event)
{
	MousePosition.first = Event.motion.x;
	MousePosition.second = Event.motion.y;
}

void inputHandler::onMouseButtonDown(SDL_Event& Event)
{
	if (Event.button.button == SDL_BUTTON_LEFT) 
	{
		MouseButtons[0] = true;
		return;
	}

	if (Event.button.button == SDL_BUTTON_MIDDLE)
	{
		MouseButtons[1] = true;
		return;
	}

	if (Event.button.button == SDL_BUTTON_RIGHT)
	{
		MouseButtons[2] = true;
		return;
	}
}

void inputHandler::onMouseButtonUp(SDL_Event& Event)
{
	if (Event.button.button == SDL_BUTTON_LEFT)
	{
		MouseButtons[0] = false;
		return;
	}

	if (Event.button.button == SDL_BUTTON_MIDDLE)
	{
		MouseButtons[1] = false;
		return;
	}

	if (Event.button.button == SDL_BUTTON_RIGHT)
	{
		MouseButtons[2] = false;
		return;
	}
}

void inputHandler::onKeyDown(SDL_Event& Event)
{
	/*if (Event.key.type == SDL_SCANCODE_RIGHT)
	{
		keystate[SDL_SCANCODE_RIGHT] = true;
		return;
	}

	if (Event.key.type == SDL_SCANCODE_LEFT)
	{
		keystate[SDL_SCANCODE_LEFT] = true;
		return;
	}

	if (Event.key.type == SDL_SCANCODE_UP)
	{
		keystate[SDL_SCANCODE_UP] = true;
		return;
	}

	if (Event.key.type == SDL_SCANCODE_DOWN)
	{
		keystate[SDL_SCANCODE_DOWN] = true;
		return;
	}*/
	Uint32 key = Event.key.type;
	keystate[key] = true;
	
}

void inputHandler::onKeyUp(SDL_Event& Event)
{
	/*if (Event.key.type == SDL_SCANCODE_RIGHT)
	{
		keystate[SDL_SCANCODE_RIGHT] = false;
		return;
	}

	if (Event.key.type == SDL_SCANCODE_LEFT)
	{
		keystate[SDL_SCANCODE_LEFT] = false;
		return;
	}

	if (Event.key.type == SDL_SCANCODE_UP)
	{
		keystate[SDL_SCANCODE_UP] = false;
		return;
	}

	if (Event.key.type == SDL_SCANCODE_DOWN)
	{
		keystate[SDL_SCANCODE_DOWN] = false;
		return;
	}*/

	Uint32 key = Event.key.type;
	keystate[key] = false;
}



int inputHandler::Direction()
{
	if (isKeyDown(SDL_SCANCODE_LEFT)) return LEFT;
	if (isKeyDown(SDL_SCANCODE_RIGHT)) return RIGHT;
	if (isKeyDown(SDL_SCANCODE_UP))  return UP;
	if (isKeyDown(SDL_SCANCODE_DOWN)) return DOWN;
	
	return 0;
}