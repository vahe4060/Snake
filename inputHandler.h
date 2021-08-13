#pragma once
#include <iostream>
#include <SDL.h>

class inputHandler
{
private:
	static inputHandler* instance_;
	inputHandler();
	~inputHandler();
public:
	static inputHandler* instance();

	void update();
	void clear();
	int Direction();

	bool isKeyDown(SDL_Scancode key);
	bool isMouseButtonDown(int buttonNumber);
	std::pair<int, int> getMousePos();

private:

	bool MouseButtons[3];
	Uint8* keystate = nullptr;
	std::pair<int, int> MousePosition;


	void onKeyDown(SDL_Event& );
	void onKeyUp(SDL_Event& );
	void onMouseButtonDown(SDL_Event& );
	void onMouseButtonUp(SDL_Event& );
	void onMouseMotion(SDL_Event& );
};

