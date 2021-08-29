#pragma once
#include "util/math/Mat.h"

using namespace Mat;

// TODO: world space is camera space atm. Later on, make it possible to position cameras in world space.
namespace Bngine {

	class Camera {
	public:
		Camera(void);
		Camera(float aspect_ratio, float fov, float clipping_near, float clipping_far);

	private:
		float _aspect_ratio;
		float _fov;
		float _clipping_near;
		float _clipping_far;
		M44f projection;
	};

}