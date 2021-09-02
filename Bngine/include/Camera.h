#pragma once
#include "util/math/Mat.h"

using namespace Mat;

// TODO: world space is camera space atm. Later on, make it possible to position cameras in world space.
namespace Bngine {

	class Camera {
	public:
		Camera(void);
		Camera(float aspect_ratio, float fov, float clipping_near, float clipping_far);

		float aspect_ratio(void);
		float fov(void);
		float clipping_near(void);
		float clipping_far(void);
		M44f projection(void);

		void set_aspect_ratio(float aspect_ratio);
		void set_fov(float fov);
		void set_clipping_near(float clipping_near);
		void set_clipping_far(float clipping_far);

	private:
		float _aspect_ratio;
		float _fov;
		float _clipping_near;
		float _clipping_far;
		M44f _projection;
	};

}