#pragma once
#include "util/math/Mat.h"

using namespace Mat;

// TODO: world space is camera space atm. Later on, make it possible to position cameras in world space.
namespace Bngine {

	class Camera {
	public:
		Camera(void);
		Camera(int width, int height, float fov, float clipping_near, float clipping_far);

		float aspect_ratio(void);
		int camera_height(void);
		int camera_width(void);
		float fov(void);
		float clipping_near(void);
		float clipping_far(void);
		M44f projection(void);

		void set_camera_width(int width);
		void set_camera_height(int height);
		void set_fov(float fov);
		void set_clipping_near(float clipping_near);
		void set_clipping_far(float clipping_far);

	private:
		int _camera_height;
		int _camera_width;
		float _aspect_ratio;
		float _fov;
		float _clipping_near;
		float _clipping_far;
		M44f _projection;
	};

}