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
	Camera cam = Camera(x, y, V3f(0, 0, 0), 120, 1, 3000);
	Cube c = Cube(9, 3, 8, 2);
	Pyramid p = Pyramid(-9, 3, 20, 2, 3);
	Icosahedron i = Icosahedron(2, 1, 10, 1);
	

	SDL_SetRenderDrawColor(r, 0, 0, 0, 0xFF);
	SDL_RenderClear(r);
	
	SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);

	M44f move_mat = id44();

	for (float j = 0;j < 4000;j += 0.002)
	{
		SDL_SetRenderDrawColor(r, 0, 0, 0, 0xFF);
		SDL_RenderClear(r);
		SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
		std::vector<Tri2D> projected = c.project(cam);
		for (Tri2D t : projected) {
			SDL_RenderDrawLine(r, t.tris[0].x, t.tris[0].y, t.tris[1].x, t.tris[1].y);
			SDL_RenderDrawLine(r, t.tris[0].x, t.tris[0].y, t.tris[2].x, t.tris[2].y);
			SDL_RenderDrawLine(r, t.tris[1].x, t.tris[1].y, t.tris[2].x, t.tris[2].y);
		}
		projected = p.project(cam);
		for (Tri2D t : projected) {
			SDL_RenderDrawLine(r, t.tris[0].x, t.tris[0].y, t.tris[1].x, t.tris[1].y);
			SDL_RenderDrawLine(r, t.tris[0].x, t.tris[0].y, t.tris[2].x, t.tris[2].y);
			SDL_RenderDrawLine(r, t.tris[1].x, t.tris[1].y, t.tris[2].x, t.tris[2].y);
		}
		projected = i.project(cam);
		for (Tri2D t : projected) {
			SDL_RenderDrawLine(r, t.tris[0].x, t.tris[0].y, t.tris[1].x, t.tris[1].y);
			SDL_RenderDrawLine(r, t.tris[0].x, t.tris[0].y, t.tris[2].x, t.tris[2].y);
			SDL_RenderDrawLine(r, t.tris[1].x, t.tris[1].y, t.tris[2].x, t.tris[2].y);
		}
		
		SDL_RenderPresent(r);
		//cam.set_rotation(V3f(0, j * 2, j));
		c.move(V3f(0, 0, -j), V3f(0, 0, 0.05));
		i.move(V3f(0, 0, 0), V3f(0, 0, 0.15));
		//c.translate(V3f(0, 0, j));
		//i.translate(V3f(0, 0, -j / 10));
		SDL_Delay(10);
		
	}

	

	

	return 1;
}

