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
		_projection = M44f({ 0 });
		_projection.m[0][0] = 1/aspect_ratio * 1/tanf(fov_rad);
		_projection.m[1][1] = 1 / tanf(fov_rad / 2);
		_projection.m[2][2] = clipping_far / q;
		_projection.m[3][2] = _projection.m[2][2] * - clipping_near;
		_projection.m[2][3] = 1;
	}

	float Camera::aspect_ratio(void)
	{
		return _aspect_ratio;
	}

	float Camera::fov(void)
	{
		return _fov;
	}

	float Camera::clipping_near(void)
	{
		return _clipping_near;
	}

	float Camera::clipping_far(void)
	{
		return _clipping_far;
	}

	M44f Camera::projection(void)
	{
		return _projection;
	}

	void Camera::set_aspect_ratio(float aspect_ratio)
	{
		_aspect_ratio = aspect_ratio;
		float fov_rad = _fov / 360 * 2 * M_PI;
		_projection.m[0][0] = aspect_ratio * 1 / tanf(fov_rad);
	}

	void Camera::set_fov(float fov)
	{
		_fov = fov;
		float fov_rad = fov / 360 * 2 * M_PI;
		_projection.m[0][0] = _aspect_ratio * 1 / tanf(fov_rad);
		_projection.m[1][1] = 1 / tanf(fov_rad / 2);
	}

	void Camera::set_clipping_near(float clipping_near)
	{
		_clipping_near = clipping_near;
		float q = _clipping_far - _clipping_near;
		_projection.m[2][2] = _clipping_far / q;
		_projection.m[3][2] = _projection.m[2][2] * - _clipping_near;
	}

	void Camera::set_clipping_far(float clipping_far)
	{
		_clipping_far = clipping_far;
		float q = _clipping_far - _clipping_near;
		_projection.m[2][2] = _clipping_far / q;
		_projection.m[3][2] = _projection.m[2][2] * - _clipping_near;
	}
}
