#include "SDL.h"
#include "include/util/math/Mat.h"
#include "include/util/math/Geom.h"

#undef main

using namespace Mat;
using namespace Geom;

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	int x = 1500, y = 1000;
	SDL_Window* w;
	SDL_Renderer* r;
	SDL_CreateWindowAndRenderer(x, y, 0, &w, &r);
	if (!w) {
		std::cout << SDL_GetError();
	}
	Camera cam = Camera(x/y, 60, 0.3, 1000);
	Cube c = Cube(V3f(8.49, 0, 9.96), 1);
	std::vector<Tri2D> projected = c.project(cam);

	SDL_SetRenderDrawColor(r, 0, 0, 0, 0xFF);
	SDL_RenderClear(r);
	SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);

	for (Tri2D t : projected) {
		SDL_RenderDrawLine(r, (t.tris[0].x + 1) * x / 2, (t.tris[0].y + 1) * y / 2, (t.tris[1].x * x + 1)* x / 2, (t.tris[1].y + 1)* y / 2);
		SDL_RenderDrawLine(r, (t.tris[0].x + 1) * x / 2, (t.tris[0].y + 1) * y / 2, (t.tris[2].x * x + 1)* x / 2, (t.tris[2].y + 1)* y / 2);
		SDL_RenderDrawLine(r, (t.tris[1].x + 1) * x / 2, (t.tris[1].y + 1) * y / 2, (t.tris[2].x * x + 1)* x / 2, (t.tris[2].y + 1)* y / 2);
	}

	SDL_RenderPresent(r);

	SDL_Delay(10000);

	return 1;
}

