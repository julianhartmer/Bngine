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

	V2f& V2f::operator=(V2f v) {
		x = v.x;
		y = v.y;
		return *this;
	}

	V2f V2f::operator+(V2f v) {
		return V2f(x + v.x, y + v.y);
	}

	V2f V2f::operator-(V2f v) {
		return V2f(x - v.x, y - v.y);
	}

	V2f V2f::operator-(void)
	{
		return V2f(-x, -y);
	}

	V2f V2f::operator*(float f) {
		return V2f(f * x, f * y);
	}

	V2f V2f::operator/(float f) {
		return V2f(x / f, y / f);
	}

	V2f& V2f::operator+=(V2f v) {
		*this = (*this + v);
		return *this;
	}

	V2f& V2f::operator-=(V2f v) {
		*this = (*this - v);
		return *this;
	}

	V2f& V2f::operator*=(float f) {
		*this = (*this * f);
		return *this;
	}

	V2f& V2f::operator/=(float f) {
		*this = (*this / f);
		return *this;
	}

	bool V2f::operator==(V2f v) {
		return (x == v.x && y == v.y);
	}

	bool V2f::operator!=(V2f v)
	{
		return (x != v.x || y != v.y);
	}

	V2f::operator bool() const
	{
		if (x == 0 && y == 0)
			return false;
		return true;
	}

	float V2f::dot(V2f v) {
		return x * v.x + y * v.y;
	}

	float V2f::norm(void) {
		return sqrt(x * x + y * y);
	}

	/**
	* 
	*	Calculates norm, then divides the vector components with it. Will return the zero vector if norm is 0.
	* 
	*	\return Normalized Vector (V2f)
	**/
	V2f V2f::normalized(void) {
		V2f o;
		float n = norm();
		if (n) {
			o = *this / n;
		}
		else
		{
			o = V2f(0, 0); // norm == 0 only happens when input is also the zero vector
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

	V3f& V3f::operator=(V3f v) {
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	V3f V3f::operator+(V3f v) {
		return V3f(x + v.x, y + v.y, z + v.z);
	}

	V3f V3f::operator-(V3f v) {
		return V3f(x - v.x, y - v.y, z - v.z);
	}

	V3f V3f::operator-(void)
	{
		return V3f(-x,-y,-z);
	}

	V3f V3f::operator*(float f) {
		return V3f(x * f, y * f, z * f);
	}

	V3f V3f::operator/(float f) {
		return V3f(x / f, y / f, z / f);
	}

	V3f& V3f::operator+=(V3f v) {
		*this = (*this + v);
		return *this;
	}

	V3f& V3f::operator-=(V3f v) {
		*this = (*this - v);
		return *this;
	}

	V3f& V3f::operator*=(float f) {
		*this = (*this * f);
		return *this;
	}

	V3f& V3f::operator/=(float f) {
		*this = (*this / f);
		return *this;
	}

	bool V3f::operator==(V3f v) {
		return (x == v.x && y == v.y && z == v.z);
	}

	bool V3f::operator!=(V3f v)
	{
		return (x != v.x || y != v.y || z != v.z);
	}

	V3f::operator bool() const
	{
		if (x == 0 && y == 0 && z == 0)
			return false;
		return true;
	}

	float V3f::dot(V3f v) {
		return x * v.x + y * v.y + z * v.z;
	}

	V3f V3f::cross(V3f v) {
		return V3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	float V3f::norm(void) {
		return sqrt(x * x + y * y + z * z);
	}

	/**
	*
	*	Calculates norm, then divides the vector components with it. Will return the zero vector if norm is 0.
	*
	*	\return Normalized Vector (V3f)
	**/
	V3f V3f::normalized(void) {
		V3f o;
		float n = norm();
		if (n) {
			o = *this / n;
		}
		else
		{
			o = V3f(0, 0, 0); // norm == 0 only happens when input is also the zero vector
		}
		return o;
	}

	V4f V3f::add_w(float w)
	{
		return V4f(x, y, z, w);
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

	V4f& V4f::operator=(V4f v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}

	V4f V4f::operator+(V4f v) {
		V4f o(x + v.x, y + v.y, z + v.z, w + v.w);
		if (o.w > 1)
		{
			o = o * (1.0 / o.w);
			o.w = 1;
		}
		return o;
	}

	V4f V4f::operator-(V4f v) {
		V4f o(x - v.x, y - v.y, z - v.z, w - v.w);
		// maybe usage like this should cause an exception (v.w == 1 and this.w ==0), would also need to remove the test for this in that case
		if (o.w == -1)
		{
			o.w = 1;
		}
		return o;
	}

	V4f V4f::operator-(void)
	{
		return V4f(-x, -y, -z, w);
	}

	V4f V4f::operator*(float f) {
		// maybe disallow this if w==1? (positions ought to be changed by displacements, not by scaling them)
		return V4f(f * x, f * y, f * z, w);
	}

	V4f V4f::operator/(float f) {
		// maybe disallow this if w==1? (positions ought to be changed by displacements, not by scaling them)
		return V4f(x / f, y / f, z / f, w);
	}

	V4f& V4f::operator+=(V4f v) {
		*this = (*this + v);
		return *this;
	}

	V4f& V4f::operator-=(V4f v) {
		*this = (*this - v);
		return *this;
	}

	V4f& V4f::operator*=(float f) {
		*this = (*this * f);
		return *this;
	}

	V4f& V4f::operator/=(float f) {
		*this = (*this / f);
		return *this;
	}

	bool V4f::operator==(V4f v) {
		return (x == v.x && y == v.y && z == v.z && w == v.w);
	}

	bool V4f::operator!=(V4f v)
	{
		return (x != v.x || y != v.y || z != v.z || w != v.w);
	}

	V4f::operator bool() const
	{
		if (x == 0 && y == 0 && z == 0 && w == 0)
			return false;
		return true;
	}

	float V4f::dot(V4f v) {
		// maybe throw exception when w==1?
		return x * v.x + y * v.y + z * v.z;
	}

	V4f V4f::cross(V4f v) {
		// maybe throw exception when w==1?
		return V4f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x, 0);
	}

	float V4f::norm(void) {
		return sqrt(x * x + y * y + z * z);
	}

	/**
	*
	*	Calculates norm, then divides the vector components with it. Will return the zero vector if norm is 0.
	*	w component will always be returned as 0, i.e. the output will be a displacement.
	*
	*	\return Normalized Vector (V4f)
	**/
	V4f V4f::normalized(void) {
		// maybe throw exception when w==1?
		V4f o;
		float n = norm();
		if (n) {
			o = *this / n;
			o.w = 0;
		}
		else
		{
			o = V4f(0, 0, 0, 0); // norm == 0 only happens when input is also the zero vector
		}
		return o;
	}

	V3f V4f::drop_w(void)
	{
		return V3f(x, y, z);
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

	M22f::M22f(float const (&m)[2][2]) {
		memcpy(&this->m, m, sizeof(m));
	}

	M22f::M22f(float const (&m)[4]) {
		memcpy(&this->m, m, sizeof(m));
	}

	M22f& M22f::operator=(M22f mat) {
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 2; x++)
			{
				m[y][x] = mat.m[y][x];
			}
		}
		return *this;
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

	M22f M22f::operator/(float f) {
		M22f o;
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 2; x++)
			{
				o.m[y][x] = m[y][x] / f;
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

	void M22f::set_column(V2f col, int col_num)
	{
		m[0][col_num - 1] = col.x;
		m[1][col_num - 1] = col.y;
	}

	void M22f::set_row(V2f row, int row_num)
	{
		m[row_num - 1][0] = row.x;
		m[row_num - 1][0] = row.y;
	}

	V2f M22f::get_column(int col_num)
	{
		return V2f(m[0][col_num - 1], m[1][col_num - 1]);
	}

	V2f M22f::get_row(int row_num)
	{
		return V2f(m[row_num - 1][0], m[row_num - 1][1]);
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

	M33f::M33f(float const (&m)[3][3]) {
		memcpy(&this->m, m, sizeof(m));
	}

	M33f::M33f(float const (&m)[9]) {
		memcpy(&this->m, m, sizeof(m));
	}

	M33f& M33f::operator=(M33f mat) {
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				m[y][x] = mat.m[y][x];
			}
		}
		return *this;
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

	M33f M33f::operator/(float f) {
		M33f o;
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				o.m[y][x] = m[y][x] / f;
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

	void M33f::set_column(V3f col, int col_num)
	{
		m[0][col_num - 1] = col.x;
		m[1][col_num - 1] = col.y;
		m[2][col_num - 1] = col.z;
	}

	void M33f::set_row(V3f row, int row_num)
	{
		m[row_num - 1][0] = row.x;
		m[row_num - 1][1] = row.y;
		m[row_num - 1][2] = row.z;
	}

	V3f M33f::get_column(int col_num)
	{
		return V3f(m[0][col_num - 1], m[1][col_num - 1], m[2][col_num - 1]);
	}

	V3f M33f::get_row(int row_num)
	{
		return V3f(m[row_num - 1][0], m[row_num - 1][1], m[row_num - 1][2]);
	}

	float M33f::trace(void) {
		return (this->_11 + this->_22 + this->_33);
	}

	float M33f::det(void) {
		return (this->_11 * (this->_22 * this->_33 - this->_23 * this->_32) - this->_12 * (this->_21 * this->_33 - this->_23 * this->_31) + this->_13 * (this->_21 * this->_32 - this->_22 * this->_31));
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

	std::ostream& operator<<(std::ostream& os, const M33f& m) {
		return os << "[" << m._11 << ", " << m._12 << ", " << m._13 << "; " << std::endl << m._21 << ", " << m._22 << ", " << m._23 << ";" << std::endl << m._31 << ", " << m._32 << ", " << m._33 << "]";
	}

	//////////
	// M44f //
	//////////
	M44f::M44f(void) {
		float m[4][4] = {0};
		memcpy(&this->m, m, sizeof(m));
	}

	M44f::M44f(float const (&m)[4][4]) {
		memcpy(&this->m, m, sizeof(m));
	}

	M44f::M44f(float const (&m)[16]) {
		memcpy(&this->m, m, sizeof(m));
	}

	M44f& M44f::operator=(M44f mat) {
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				m[y][x] = mat.m[y][x];
			}
		}
		return *this;
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

	M44f M44f::operator/(float f) {
		M44f o;
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				o.m[y][x] = m[y][x] / f;
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
		if (o.w != 0)
		{
			o /= o.w;
			o.w = 1;
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

	void M44f::set_column(V4f col, int col_num)
	{
		m[0][col_num - 1] = col.x;
		m[1][col_num - 1] = col.y;
		m[2][col_num - 1] = col.z;
		m[3][col_num - 1] = col.w;
	}

	void M44f::set_row(V4f row, int row_num)
	{
		m[row_num - 1][0] = row.x;
		m[row_num - 1][1] = row.y;
		m[row_num - 1][2] = row.z;
		m[row_num - 1][3] = row.w;
	}

	V4f M44f::get_column(int col_num)
	{
		return V4f(m[0][col_num - 1], m[1][col_num - 1], m[2][col_num - 1], m[3][col_num - 1]);
	}

	V4f M44f::get_row(int row_num)
	{
		return V4f(m[row_num - 1][0], m[row_num - 1][1], m[row_num - 1][2], m[row_num - 1][3]);
	}

	float M44f::trace(void) {
		return (this->_11 + this->_22 + this->_33 + this->_44);
	}

	float M44f::det(void) {
		return (this->_11 * this->minor(1, 1).det() - this->_12 * this->minor(1, 2).det() + this->_13 * this->minor(1, 3).det() - this->_14 * this->minor(1, 4).det());
	}

	/**
	*
	*	Returns the row-col-minor of the 4x4 matrix, i.e. the 3x3 submatrix that does not contain row and col.
	*   Throws out_of_range exception if index invalid.
	*
	*	\return row-col-minor of calling matrix (M33f)
	**/
	M33f M44f::minor(int row, int col) {
		if (1 > row || row > 4 || 1 > col || col > 4)
			throw std::out_of_range ("Index out of range");
		M33f o;
		// skip the minor row and col via offsets that are added to the array access
		int offset_x = 0;
		int offset_y = 0;
		for (int y = 0;y < 3;y++)
		{
			if (y == row-1)
				offset_y = 1;
			offset_x = 0;
			for (int x = 0;x < 3;x++)
			{
				if (x == col-1)
					offset_x = 1;
				o.m[y][x] = m[y + offset_y][x + offset_x];
			}
		}
		return o;
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

	std::ostream& operator<<(std::ostream& os, const M44f& m) {
		return os << "[" << m._11 << ", " << m._12 << ", " << m._13 << ", " << m._14 << "; " << std::endl << m._21 << ", " << m._22 << ", " << m._23 << ", " << m._24 << ";" << std::endl << m._31 << ", " << m._32 << ", " << m._33 << ", " << m._34 << "; " << std::endl << m._41 << ", " << m._42 << ", " << m._43 << ", " << m._44 << "]";
	}

	//////////
	// M23f //
	//////////
	M23f::M23f(void) {
		float m[2][3] = { 0 };
		memcpy(&this->m, m, sizeof(m));
	}

	M23f::M23f(float const (&m)[2][3]) {
		memcpy(&this->m, m, sizeof(m));
	}

	M23f::M23f(float const (&m)[6]) {
		memcpy(&this->m, m, sizeof(m));
	}

	M23f& M23f::operator=(M23f mat) {
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				m[y][x] = mat.m[y][x];
			}
		}
		return *this;
	}

	M23f M23f::operator+(M23f mat) {
		M23f o;
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				o.m[y][x] = m[y][x] + mat.m[y][x];
			}
		}
		return o;
	}

	M23f M23f::operator-(M23f mat) {
		M23f o;
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				o.m[y][x] = m[y][x] - mat.m[y][x];
			}
		}
		return o;
	}

	M23f M23f::operator*(float f) {
		M23f o;
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				o.m[y][x] = m[y][x] * f;
			}
		}
		return o;
	}

	M23f M23f::operator/(float f) {
		M23f o;
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				o.m[y][x] = m[y][x] / f;
			}
		}
		return o;
	}

	V2f M23f::operator*(V3f v) {
		V2f o;
		for (int y = 0; y < 2; y++)
		{
			o.v[y] = 0;
			for (int x = 0; x < 3; x++)
			{
				o.v[y] += v.v[x] * m[y][x];
			}
		}
		return o;
	}

	std::ostream& operator<<(std::ostream& os, const M23f& m) {
		return os << "[" << m._11 << ", " << m._12 << ", " << m._13 << "; " << std::endl << m._21 << ", " << m._22 << ", " << m._23 << "]";
	}

	//////////
	// M34f //
	//////////
	M34f::M34f(void) {
		float m[3][4] = { 0 };
		memcpy(&this->m, m, sizeof(m));
	}

	M34f::M34f(float const (&m)[3][4]) {
		memcpy(&this->m, m, sizeof(m));
	}

	M34f::M34f(float const (&m)[12]) {
		memcpy(&this->m, m, sizeof(m));
	}

	M34f& M34f::operator=(M34f mat) {
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				m[y][x] = mat.m[y][x];
			}
		}
		return *this;
	}

	M34f M34f::operator+(M34f mat) {
		M34f o;
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				o.m[y][x] = m[y][x] + mat.m[y][x];
			}
		}
		return o;
	}

	M34f M34f::operator-(M34f mat) {
		M34f o;
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				o.m[y][x] = m[y][x] - mat.m[y][x];
			}
		}
		return o;
	}

	M34f M34f::operator*(float f) {
		M34f o;
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				o.m[y][x] = m[y][x] * f;
			}
		}
		return o;
	}

	M34f M34f::operator/(float f) {
		M34f o;
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				o.m[y][x] = m[y][x] / f;
			}
		}
		return o;
	}

	V3f M34f::operator*(V4f v) {
		V3f o;
		for (int y = 0; y < 3; y++)
		{
			o.v[y] = 0;
			for (int x = 0; x < 4; x++)
			{
				o.v[y] += v.v[x] * m[y][x];
			}
		}
		return o;
	}

	std::ostream& operator<<(std::ostream& os, const M34f& m) {
		return os << "[" << m._11 << ", " << m._12 << ", " << m._13 << ", " << m._14 << "; " << std::endl << m._21 << ", " << m._22 << ", " << m._23 << ", " << m._24 << ";" << std::endl << m._31 << ", " << m._32 << ", " << m._33 << ", " << m._34 << "]";
	}

	///////////////////
	// Identity Util //
	///////////////////

	M22f id22(void)
	{
		return M22f(1, 0, 0, 1);
	}
	M33f id33(void)
	{
		return M33f({1, 0, 0, 0, 1, 0, 0, 0, 1});
	}
	M44f id44(void)
	{
		return M44f({ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 });
	}
}