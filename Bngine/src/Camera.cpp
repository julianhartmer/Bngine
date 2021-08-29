#define _USE_MATH_DEFINES
#include <cmath>
#include "..\include\Camera.h"

namespace Bngine {
	Camera::Camera(float aspect_ratio, float fov, float clipping_near, float clipping_far)
	{
		float fov_rad = fov / 360 * 2 * M_PI;
		float q = clipping_far - clipping_near;
		_aspect_ratio = aspect_ratio;
		_fov = fov;
		_clipping_near = clipping_near;
		_clipping_far = clipping_far;
		projection = M44f({ 0 });
		projection.m[0][0] = aspect_ratio * 1/tanf(fov_rad);
		projection.m[1][1] = 1 / tanf(fov_rad / 2);
		projection.m[2][2] = clipping_far / q;
		projection.m[3][2] = projection.m[2][2] * -clipping_near;
		projection.m[2][3] = 1;
	}
}
