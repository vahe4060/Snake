// snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> /* printf and fprintf */
#include "Game.h"
#include <SDL.h> /* Windows-specific SDL2 library */

struct A
{
    int a, b;
    A(int aa, int bb) :a(aa), b(bb) {}
};
int main(int argc, char** argv)
{
    const int FPS = 60;
    int frameStart, frameEnd, FrameDuration;
    
    if (!game::instance()->init("snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,0))
    {
        std::cerr << "not cool..\n";
       // return 1;
    }
    
    
    
    while ( game::instance()->isRunning )
    {
        frameStart = SDL_GetTicks();
    
    
        game::instance()->update();
        game::instance()->render();
        game::instance()->handleEvents();
    
        frameEnd = SDL_GetTicks();
        FrameDuration = frameEnd - frameStart;
        //std::cout << "FPS: " << 1000 / FrameDuration << std::endl;
        if (1000 / FPS > FrameDuration) SDL_Delay(1000 / FPS - FrameDuration);
    }
    
    game::instance()->clean();

    return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
