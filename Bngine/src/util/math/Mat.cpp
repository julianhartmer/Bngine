#include <math.h>
#include "util/math/Mat.h"

namespace Mat {
	/////////
	// V2f //
	////////
	V2f::V2f(float x, float y) {
		this->x = x;
		this->y = y;
	}

	V2f::V2f(float v[2]) {
		memcpy (&this->v, &v, sizeof (v));
	}

	V2f::V2f(void) {
		x = 0;
		y = 0;
	}

	void V2f::operator=(V2f v) {
		x = v.x;
		y = v.y;
	}

	V2f V2f::operator+(V2f v) {
		return V2f(x + v.x, y + v.y);;
	}

	V2f V2f::operator-(V2f v) {
		return V2f(x - v.x, y - v.y);;
	}

	V2f V2f::operator*(float f) {
		return V2f(f * x, f * y);;
	}

	bool V2f::operator==(V2f v) {
		return (x == v.x && y == v.y);
	}

	float V2f::dot(V2f v) {
		return x * v.x + y * v.y;
	}

	float V2f::norm(void) {
		return sqrt(x * x + y * y);
	}

	V2f V2f::normalized(void) {
		// TODO throw exception instead of undefined behavior
		V2f o;
		float n = this->norm();
		if (n) {
			o.x = x / n;
			o.y = y / n;
		}
		return o;
	}

	// printing
	std::ostream &operator<<(std::ostream &os, const V2f &v) {
		return os << "[" << v.x << "; " << std::endl << v.y << "]";
	}

	/////////
	// V3f //
	/////////
	V3f::V3f(void) {
		x = 0;
		y = 0;
		z = 0;
	}

	V3f::V3f(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	V3f::V3f(float v[3]) {
		memcpy (&this->v, &v, sizeof (v));
	}

	void V3f::operator=(V3f v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	V3f V3f::operator+(V3f v) {
		return V3f(x + v.x, y + v.y, z + v.z);
	}

	V3f V3f::operator-(V3f v) {
		return V3f(x - v.x, y - v.y, z - v.z);
	}

	V3f V3f::operator*(float f) {
		return V3f(x * f, y * f, z * f);
	}

	bool V3f::operator==(V3f v) {
		return (x == v.x && y == v.y && z == v.z);
	}

	std::ostream &operator<<(std::ostream &os, const V3f &v) {
		return os << "[" << v.x << "; " << std::endl << v.y << "; " << std::endl << v.z << "]";
	}


	/////////
	// V4f //
	/////////
	V4f::V4f(void) {
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	V4f::V4f(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	V4f::V4f(float v[4]) {
		memcpy (&this->v, &v, sizeof (v));
	}

	void V4f::operator=(V4f v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	V4f V4f::operator+(V4f v) {
		return V4f(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	V4f V4f::operator*(float f) {
		return V4f(f * x, f * y, f * z, f * w);
	}

	bool V4f::operator==(V3f v) {
		return (x == v.x && y == v.y && z == v.z);
	}

	std::ostream &operator<<(std::ostream &os, const V4f &v) {
		return os << "[" << v.x << "; " << std::endl << v.y << "; " << std::endl << v.z << "; " << std::endl << v.w << "]";
	}


	//////////
	// M22f //
	//////////
	M22f::M22f(void) {
		float m[2][2] = {0};
		memcpy(&this->m, m, sizeof(m));
	}

	M22f::M22f(float e11, float e12, float e21, float e22) {
		_11 = e11;
		_12 = e12;
		_21 = e21;
		_22 = e22;
	}

	M22f::M22f(float m[2][2]) {
		memcpy(&this->m, m, sizeof(m));
	}

	void M22f::operator=(M22f mat) {
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 2; x++)
			{
				m[y][x] = mat.m[y][x];
			}
		}
	}

	M22f M22f::operator+(M22f mat) {
		M22f o;
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 2; x++)
			{
				o.m[y][x] = m[y][x] + mat.m[y][x];
			}
		}
		return o;
	}

	M22f M22f::operator-(M22f mat) {
		M22f o;
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 2; x++)
			{
				o.m[y][x] = m[y][x] - mat.m[y][x];
			}
		}
		return o;
	}

	M22f M22f::operator*(float f) {
		M22f o;
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 2; x++)
			{
				o.m[y][x] = m[y][x] * f;
			}
		}
		return o;
	}

	V2f M22f::operator*(V2f v) {
		V2f o;
		for (int y = 0; y < 2; y++)
		{
			o.v[y] = 0;
			for (int x = 0; x < 2; x++)
			{
				o.v[y] += v.v[x] * m[y][x];
			}
		}
		return o;
	}

	M22f M22f::operator*(M22f mat) {
		M22f o;
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 2; x++)
			{
				o.m[y][x] = 0;
				for (int it = 0; it < 2; it++)
				{
					o.m[y][x] += m[y][it] * mat.m[it][x];
				}
			}
		}
		return o;
	}

	float M22f::trace(void) {
		return (this->_11 + this->_22);
	}

	float M22f::det(void) {
		return (this->_11 * this->_22 - this->_21 * this->_12);
	}

	M22f M22f::t(void) {
		return M22f(_11, _21, _12, _22);
	}

	std::ostream &operator<<(std::ostream &os, const M22f &m) {
		return os << "[" << m._11 << ", " << m._12 << "; " << std::endl << m._21 << ", " << m._22 << "]";
	}


	//////////
	// M33f //
	//////////
	M33f::M33f(void) {
		float m[3][3] = {0};
		memcpy(&this->m, m, sizeof(m));
	}

	M33f::M33f(float m[3][3]) {
		memcpy(&this->m, m, sizeof(m));
	}

	void M33f::operator=(M33f mat) {
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				m[y][x] = mat.m[y][x];
			}
		}
	}

	M33f M33f::operator+(M33f mat) {
		M33f o;
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				o.m[y][x] = m[y][x] + mat.m[y][x];
			}
		}
		return o;
	}

	M33f M33f::operator-(M33f mat) {
		M33f o;
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				o.m[y][x] = m[y][x] - mat.m[y][x];
			}
		}
		return o;
	}

	M33f M33f::operator*(float f) {
		M33f o;
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				o.m[y][x] = m[y][x] * f;
			}
		}
		return o;
	}

	V3f M33f::operator*(V3f v) {
		V3f o;
		for (int y = 0; y < 3; y++)
		{
			o.v[y] = 0;
			for (int x = 0; x < 3; x++)
			{
				o.v[y] += v.v[x] * m[y][x];
			}
		}
		return o;
	}

	M33f M33f::operator*(M33f mat) {
		M33f o;
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				o.m[y][x] = 0;
				for (int it = 0; it < 3; it++)
				{
					o.m[y][x] += m[y][it] * mat.m[it][x];
				}
			}
		}
		return o;
	}

	float M33f::trace(void) {
		return (this->_11 + this->_22 + this->_33);
	}

	float M33f::det(void) {
		return (this->_11 * this->_22 * this->_33 + this->_12 * this->_23 * this->_31 + this->_13 * this->_21 * this->_32 - this->_31 * this->_22 * this->_13 - this->_32 * this->_23 * this->_11 - this->_33 * this->_21 * this->_21);
	}

	M33f M33f::t(void) {
		M33f o;
		o._11 = this->_11;
		o._22 = this->_22;
		o._33 = this->_33;
		o._12 = this->_21;
		o._21 = this->_12;
		o._13 = this->_31;
		o._23 = this->_32;
		o._31 = this->_13;
		o._32 = this->_23;
		return o;
	}

	std::ostream &operator<<(std::ostream &os, const M44f &m) {
		return os << "[" << m._11 << ", " << m._12 << ", " << m._13 << ", " << m._14 << "; " << std::endl << m._21 << ", " << m._22 << ", " << m._23 << ", " << m._24 << ";" << std::endl << m._31 << ", " << m._32 << ", " << m._33 << ", " << m._34 << "; " << std::endl << m._41 << ", " << m._42 << ", " << m._43 << ", " << m._44 << "]";
	}


	//////////
	// M44f //
	//////////
	M44f::M44f(void) {
		float m[4][4] = {0};
		memcpy(&this->m, m, sizeof(m));
	}

	M44f::M44f(float m[4][4]) {
		memcpy(&this->m, m, sizeof(m));
	}

	M44f M44f::operator+(M44f mat) {
		M44f o;
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				o.m[y][x] = m[y][x] + mat.m[y][x];
			}
		}
		return o;
	}

	M44f M44f::operator-(M44f mat) {
		M44f o;
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				o.m[y][x] = m[y][x] - mat.m[y][x];
			}
		}
		return o;
	}

	M44f M44f::operator*(float f) {
		M44f o;
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				o.m[y][x] = m[y][x] * f;
			}
		}
		return o;
	}

	V4f M44f::operator*(V4f v) {
		V4f o;
		for (int y = 0; y < 4; y++)
		{
			o.v[y] = 0;
			for (int x = 0; x < 4; x++)
			{
				o.v[y] += v.v[x] * m[y][x];
			}
		}
		return o;
	}

	M44f M44f::operator*(M44f mat) {
		M44f o;
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				o.m[y][x] = 0;
				for (int it = 0; it < 4; it++)
				{
					o.m[y][x] += m[y][it] * mat.m[it][x];
				}
			}
		}
		return o;
	}

	float M44f::trace(void) {
		return (this->_11 + this->_22 + this->_33 + this->_44);
	}

	float M44f::det(void) {
		// TODO: 3x3 implementation as placeholder here, 4x4 determinant involves determinants of submatrices
		return (this->_11 * this->_22 * this->_33 + this->_12 * this->_23 * this->_31 + this->_13 * this->_21 * this->_32 - this->_31 * this->_22 * this->_13 - this->_32 * this->_23 * this->_11 - this->_33 * this->_21 * this->_21);
	}

	M44f M44f::t(void) {
		M44f o;
		o._11 = this->_11;
		o._22 = this->_22;
		o._33 = this->_33;
		o._44 = this->_44;
		o._12 = this->_21;
		o._21 = this->_12;
		o._13 = this->_31;
		o._14 = this->_41;
		o._24 = this->_42;
		o._23 = this->_32;
		o._24 = this->_42;
		o._31 = this->_13;
		o._32 = this->_23;
		o._34 = this->_43;
		o._41 = this->_14;
		o._42 = this->_24;
		o._43 = this->_34;
		return o;
	}

	std::ostream &operator<<(std::ostream &os, const M33f &m) {
		return os << "[" << m._11 << ", " << m._12 << ", " << m._13 << "; " << std::endl << m._21 << ", " << m._22 << ", " << m._23 << ";" << std::endl << m._31 << ", " << m._32 << ", " << m._33 << "]";
	}
}