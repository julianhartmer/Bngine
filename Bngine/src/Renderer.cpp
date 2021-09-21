#include "Renderer.h"
namespace Bngine {
	Renderer::Renderer(Camera& c)
		: _c(c)
	{
		SDL_CreateWindowAndRenderer(c.projection_width(), c.projection_height(), 0, &_w, &_r);
		if (!_r || !_w)
			std::cout << SDL_GetError();
	}

	void Renderer::add_geom(Geom& g)
	{
		_geoms.push_back(g);
	}

	void Renderer::remove_geom(Geom& g)
	{
		//_geoms.erase(std::remove(_geoms.begin(), _geoms.end(), g), _geoms.end());
	}

	void Renderer::render()
	{
		SDL_SetRenderDrawColor(_r, 0, 0, 0, 0xFF);
		SDL_RenderClear(_r);
		SDL_SetRenderDrawColor(_r, 0xFF, 0xFF, 0xFF, 0xFF);
		for (Geom &g : _geoms)
		{
			for (Tri2D t : g.project(_c)) {
				SDL_RenderDrawLine(_r, t.vertices[0].x, t.vertices[0].y, t.vertices[1].x, t.vertices[1].y);
				SDL_RenderDrawLine(_r, t.vertices[0].x, t.vertices[0].y, t.vertices[2].x, t.vertices[2].y);
				SDL_RenderDrawLine(_r, t.vertices[1].x, t.vertices[1].y, t.vertices[2].x, t.vertices[2].y);
			}
		}
		SDL_RenderPresent(_r);
	}
}