#pragma once
#include "util/math/Mat.h"

using namespace Mat;

// TODO: world space is camera space atm. Later on, make it possible to position cameras in world space.
namespace Bngine {

	class Camera {
	public:
		Camera(void);
		Camera(int width, int height, V3f position, float fov, float clipping_near, float clipping_far);

		float aspect_ratio(void);
		int camera_height(void);
		int camera_width(void);
		float fov(void);
		float clipping_near(void);
		float clipping_far(void);
		M44f mProjection(void);
		M44f mPosition(void);
		V4f vPosition(void);
		V3f vRotation(void);
		V4f vDirection(void);

		void set_camera_width(int width);
		void set_camera_height(int height);
		void set_fov(float fov);
		void set_clipping_near(float clipping_near);
		void set_clipping_far(float clipping_far);
		void set_position(V3f position);
		void set_rotation(V3f rotation);
		void set_direction(V3f direction);

	private:
		int _camera_height;
		int _camera_width;
		float _aspect_ratio;
		float _fov;
		float _clipping_near;
		float _clipping_far;
		M44f _mProjection;
		M44f _mPosition;
		V3f _vRotation;
		V4f _vDirection;
	};

}