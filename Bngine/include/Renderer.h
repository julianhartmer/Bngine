#pragma once

#include <vector>

#include "SDL.h"
#include "Camera.h"
#include "util/math/Geom.h"

namespace Bngine {
	class Renderer {
	public:
		Renderer(Camera& c);

		// may be changed later
		void add_geom(Geom& g);
		void remove_geom(Geom& g);

		void render();

	private:
		SDL_Renderer *_r;
		SDL_Window *_w;
		Camera &_c;
		std::vector<std::reference_wrapper<Geom>> _geoms;
	};

}


