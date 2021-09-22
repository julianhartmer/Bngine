#include <filesystem>

#include "SDL.h"
#include "include/util/math/Mat.h"
#include "include/util/math/Geom.h"
#include "include/Renderer.h"

#undef main

using namespace Mat;
using namespace Bngine;

int main()
{
	// Gameloop
	SDL_Init(SDL_INIT_EVERYTHING);
	int x = 1500, y = 1000;
	Camera cam = Camera(x, y, V3f(0, 0, 0), 120, 1, 3000);
	Mesh m = Mesh("data/monkey.stl", 10, 10, 10);
	Cube c = Cube(9, 3, 8, 2);
	Pyramid p = Pyramid(-9, 3, 20, 2, 3);
	Icosahedron i = Icosahedron(2, 1, 10, 1);
	Renderer rend = Renderer(cam);
	rend.add_geom(c);
	rend.add_geom(p);
	rend.add_geom(i);
	rend.add_geom(m);

	M44f move_mat = id44();

	for (float j = 0;j < 4000;j += 0.002)
	{
		rend.render();
		
		//cam.set_rotation(V3f(0, j * 2, j));
		c.move(V3f(0, 0, -j), V3f(0, 0, 0.05));
		i.move(V3f(0, 0, 0), V3f(0, 0, 0.15));
		//c.translate(V3f(0, 0, j));
		//i.translate(V3f(0, 0, -j / 10));
		SDL_Delay(10);
		
	}

	

	

	return 1;
}

