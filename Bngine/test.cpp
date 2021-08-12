#include "SDL.h"
#undef main

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindow("Bngine", 200, 200, 200, 200, 0);

	SDL_Delay(10000);

	return 1;
}