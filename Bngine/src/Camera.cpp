#define _USE_MATH_DEFINES
#include <cmath>
#include "..\include\Camera.h"

namespace Bngine {
	Camera::Camera(int width, int height, V3f position, float fov, float clipping_near, float clipping_far)
	{
		//set camera attributes
		_camera_width = width;
		_camera_height = height;
		_aspect_ratio = float(height) / float(width);
		_fov = fov;
		_clipping_near = clipping_near;
		_clipping_far = clipping_far;
		_vRotation = V3f(0, 0, 0); // convention: rotation about x(0)-y(1)-z(2)-axis in deg
		_vDirection = V4f(0, 0, 1, 0); // facing in the same direction as the coordinate system at the start

		//set up projection matrix
		float fov_rad = 1 / tanf(fov * 0.5f / 180.0f * M_PI);
		_mProjection = M44f({ 0 });
		_mProjection.m[0][0] = _aspect_ratio * fov_rad;
		_mProjection.m[1][1] = fov_rad;
		_mProjection.m[2][2] = clipping_far / (clipping_far - clipping_near);
		_mProjection.m[3][2] = _mProjection.m[2][2] * -clipping_near;
		_mProjection.m[2][3] = 1;

		//set up position matrix
		_mPosition = id44();
		set_position(position);
		set_rotation(_vRotation);
	}

	int Camera::camera_height(void)
	{
		return _camera_height;
	}

	int Camera::camera_width(void)
	{
		return _camera_width;
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

	M44f Camera::mProjection(void)
	{
		return _mProjection;
	}

	M44f Camera::mPosition(void)
	{
		return _mPosition;
	}

	V4f Camera::vPosition(void)
	{
		V4f o = V4f(_mPosition.m[0][3], _mPosition.m[1][3], _mPosition.m[2][3], 1);
		return o;
	}

	V3f Camera::vRotation(void)
	{
		return _vRotation;
	}

	V4f Camera::vDirection(void)
	{
		return _vDirection;
	}

	void Camera::set_camera_width(int width)
	{
		_camera_width = width;
		_aspect_ratio = float(_camera_height) / float(_camera_width);
		float fov_rad = _fov / 360 * 2 * M_PI;
		_mProjection.m[0][0] = _aspect_ratio * 1 / tanf(fov_rad);
	}

	void Camera::set_camera_height(int height)
	{
		_camera_height = height;
		_aspect_ratio = float(_camera_height) / float(_camera_width);
		float fov_rad = _fov / 360 * 2 * M_PI;
		_mProjection.m[0][0] = _aspect_ratio * 1 / tanf(fov_rad);
	}

	void Camera::set_fov(float fov)
	{
		_fov = fov;
		float fov_rad = fov / 360 * 2 * M_PI;
		_mProjection.m[0][0] = _aspect_ratio * 1 / tanf(fov_rad);
		_mProjection.m[1][1] = 1 / tanf(fov_rad / 2);
	}

	void Camera::set_clipping_near(float clipping_near)
	{
		_clipping_near = clipping_near;
		_mProjection.m[2][2] = _clipping_far / (_clipping_far - _clipping_near);
		_mProjection.m[3][2] = _mProjection.m[2][2] * -_clipping_near;
	}

	void Camera::set_clipping_far(float clipping_far)
	{
		_clipping_far = clipping_far;
		_mProjection.m[2][2] = _clipping_far / (_clipping_far - _clipping_near);
		_mProjection.m[3][2] = _mProjection.m[2][2] * -_clipping_near;
	}
	void Camera::set_position(V3f position)
	{
		//translation
		_mPosition.m[3][3] = 1; //homogenous component
		_mPosition.m[0][3] = position.x;
		_mPosition.m[1][3] = position.y;
		_mPosition.m[2][3] = position.z;
	}

	void Camera::set_rotation(V3f rotation)
	{
		V3f rotation_rad = rotation * (M_PI / 180.f);
		//to avoid unnecessarily calling a lot of sin and cos, check which components changed and only modify those elements of the position matrix necessary

		//always update because every component appears
		_mPosition.m[0][1] = cos(rotation_rad.z) * sin(rotation_rad.y) * sin(rotation_rad.x) - sin(rotation_rad.z) * cos(rotation_rad.x);
		_mPosition.m[0][2] = cos(rotation_rad.z) * sin(rotation_rad.y) * cos(rotation_rad.x) + sin(rotation_rad.z) * cos(rotation_rad.x);
		_mPosition.m[1][1] = sin(rotation_rad.z) * sin(rotation_rad.y) * sin(rotation_rad.x) + cos(rotation_rad.z) * cos(rotation_rad.x);
		_mPosition.m[1][2] = sin(rotation_rad.z) * sin(rotation_rad.y) * cos(rotation_rad.x) - cos(rotation_rad.z) * sin(rotation_rad.x);
		if (rotation.y != _vRotation.y)
		{
			// only needs to change when y changes
			_mPosition.m[2][0] = -sin(rotation_rad.y);
		}
		if (rotation.y != _vRotation.y || rotation.z != _vRotation.z)
		{
			// for y or z change
			_mPosition.m[0][0] = cos(rotation_rad.z) * cos(rotation_rad.y);
			_mPosition.m[1][0] = sin(rotation_rad.z) * cos(rotation_rad.y);
		}
		if (rotation.y != _vRotation.y || rotation.x != _vRotation.x)
		{
			// for x or z change
			_mPosition.m[2][1] = cos(rotation_rad.y) * sin(rotation_rad.x);
			_mPosition.m[2][2] = cos(rotation_rad.y) * cos(rotation_rad.x);
		}

		//set rotation vector to new one and update direction
		_vRotation = rotation;
		_vDirection = _mPosition * V4f(0, 0, 1, 0);
	}

	void Camera::set_direction(V3f direction)
	{
		V3f old_dir_norm = V3f(_vDirection.x, _vDirection.y, _vDirection.z); //assuming at this point that the old stored direction is normalized
		V3f new_dir_norm = direction.normalized();

		V3f v = old_dir_norm.cross(new_dir_norm);
		float s = v.norm();
		float c = old_dir_norm.dot(new_dir_norm);
		M33f v_skew = M33f({ 0, -v.z, v.y, v.z, 0, -v.x, -v.y, v.x, 0 });
		M33f rot33 = id33() + v_skew + v_skew * v_skew * (1.0f / (1.0f + c));
		// TODO: find more elegant way instead of raw copying or maybe put this into a convenience constructor for M44f
		// or maybe allow for M33f * M44f multiplication (add a virtual 0 0 0 1 row and colum to the bottom and right)? seems useful but dangerous
		M44f rot44 = id44();
		rot44._11 = rot33._11;
		rot44._12 = rot33._12;
		rot44._13 = rot33._13;
		rot44._21 = rot33._21;
		rot44._22 = rot33._22;
		rot44._23 = rot33._23;
		rot44._31 = rot33._31;
		rot44._32 = rot33._32;
		rot44._33 = rot33._33;

		//update position matrix
		_mPosition = rot44 * _mPosition;
		//update rotation vector
		_vRotation.x = atan2(_mPosition._32, _mPosition._33) * (180.f / M_PI);
		_vRotation.y = atan2(-_mPosition._31, sqrt(_mPosition._32 * _mPosition._32 + _mPosition._33 * _mPosition._33)) * (180.f / M_PI);
		_vRotation.z = atan2(_mPosition._21, _mPosition._11) * (180.f / M_PI);
		//finally write new direciton into storage
		_vDirection = V4f(new_dir_norm.x, new_dir_norm.y, new_dir_norm.z, 0);
	}
}
