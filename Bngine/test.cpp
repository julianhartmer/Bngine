#include "SDL.h"
#undef main

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindow("Bngine", 100, 1337, 2, 2, 0);

	SDL_Delay(1000);

	return 1;
}