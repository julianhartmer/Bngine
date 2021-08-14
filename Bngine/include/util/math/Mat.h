//#pragma once
#include <iostream>


namespace Mat
{
	struct V2f
	{

		// struct definition
		union {
			struct {
				float x;
				float y;
			};
			float v[2];
		};
		
		// operators
		inline void operator=(V2f v) {
			x = v.x;
			y = v.y;
		} 

		inline V2f operator+(V2f v) {
			V2f o;
			o.x = x + v.x;
			o.y = y + v.y;
			return o;
		}


		inline V2f operator-(V2f v) {
			V2f o;
			o.x = x - v.x;
			o.y = y - v.y;
			return o;
		}

		inline V2f operator*(float f) {
			V2f o;
			o.x = f * x;
			o.y = f * y;
			return o;
		}

		inline bool operator==(V2f v) {
			return (x == v.x && y == v.y);
		}

		// methods
		V2f dot(V2f v);
		float norm(void);
		float normalize(void);
	};

	// printing
	std::ostream& operator<<(std::ostream& os, const V2f& v) {
		return os << "[" << v.x << "; " << std::endl << v.y << "]";
	}

	struct V3f
	{
		union {
			struct {
				float x;
				float y;
				float z;
			};
			float v[3];
		};

		inline void operator=(V3f v) {
			x = v.x;
			y = v.y;
			z = v.z;
		}

		inline V3f operator+(V3f v) {
			V3f o;
			o.x = x + v.x;
			o.y = y + v.y;
			o.z = z + v.z;
			return o;
		}

		inline V3f operator-(V3f v) {
			V3f o;
			o.x = x - v.x;
			o.y = y - v.y;
			o.z = z - v.z;
			return o;
		}

		inline V3f operator*(float f) {
			V3f o;
			o.x = f * x;
			o.y = f * y;
			o.z = f * z;
			return o;
		}

		inline bool operator==(V3f v) {
			return (x == v.x && y == v.y && z == v.z);
		}

		V3f dot(V3f v);
		V3f cross(V3f v);
		float norm(void);
		float normalize(void);
	};

	std::ostream& operator<<(std::ostream& os, const V3f& v) {
		return os << "[" << v.x << "; " << std::endl << v.y << "; " << std::endl << v.z << "]";
	}

	struct V4f
	{
		union {
			struct {
				float x;
				float y;
				float z;
				float w;
			};
			float v[4];
		};

		//TODO: schauen wie w hier funktioniert
		// betrifft alle Methoden hier


		inline void operator=(V4f v) {
			x = v.x;
			y = v.y;
			z = v.z;
		}

		inline V4f operator+(V4f v) {
			V4f o;
			o.x = x + v.x;
			o.y = y + v.y;
			o.z = z + v.z;
			return o;
		}

		inline V4f operator-(V4f v) {
			V4f o;
			o.x = x - v.x;
			o.y = y - v.y;
			o.z = z - v.z;
			return o;
		}

		inline V4f operator*(float f) {
			V4f o;
			o.x = f * x;
			o.y = f * y;
			o.z = f * z;
			return o;
		}

		inline bool operator==(V3f v) {
			return (x == v.x && y == v.y && z == v.z);
		}

		V4f dot(V4f v);
		V4f cross(V4f v);
		float norm(void);
		float normalize(void);
	};

	std::ostream& operator<<(std::ostream& os, const V4f& v) {
		return os << "[" << v.x << "; " << std::endl << v.y << "; " << std::endl << v.z << "; " << std::endl << v.w << "]";
	}

	struct M22f
	{
		union {
			struct {
				float _11, _12;
				float _21, _22;
			};
			float m[2][2];
		};

		inline void operator=(M22f mat) {
			for (int y = 0; y < 2; y++)
			{
				for (int x = 0; x < 2; x++)
				{
					m[y][x] = mat.m[y][x];
				}
			}
		}

		inline M22f operator+(M22f mat) {
			M22f o;
			for (int y=0; y<2; y++)
			{
				for (int x = 0; x < 2; x++)
				{
					o.m[y][x] = m[y][x] + mat.m[y][x];
				}
			}
			return o;
		}

		inline M22f operator-(M22f mat) {
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

		inline M22f operator*(float f) {
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

		inline V2f operator*(V2f v) {
			V2f o;
			for (int y = 0; y < 2; y++)
			{
				o.v[y] = 0;
				for (int x = 0; x < 2; x++)
				{
					o.v[y] += v.v[x]*m[y][x];
				}
			}
			return o;
		}

		inline M22f operator*(M22f mat) {
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

		// == operator not defined for lack of use case (so far)

		float trace(void);
		M22f t(void);
		//float det(void);
	};

	std::ostream& operator<<(std::ostream& os, const M22f& m) {
		return os << "[" << m._11 << ", " << m._12 << "; " << std::endl << m._21 << ", " << m._22 << "]";
	}

	struct M33f
	{
		union {
			struct {
				float _11, _12, _13;
				float _21, _22, _23;
				float _31, _32, _33;
			};
			float m[3][3];
		};

		inline void operator=(M33f mat) {
			for (int y = 0; y < 3; y++)
			{
				for (int x = 0; x < 3; x++)
				{
					m[y][x] = mat.m[y][x];
				}
			}
		}

		inline M33f operator+(M33f mat) {
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

		inline M33f operator-(M33f mat) {
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

		inline M33f operator*(float f) {
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

		inline V3f operator*(V3f v) {
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

		inline M33f operator*(M33f mat) {
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

		// == operator not defined for lack of use case (so far)

		float trace(void);
		M33f t(void);
		//float det(void);
	};

	std::ostream& operator<<(std::ostream& os, const M33f& m) {
		return os << "[" << m._11 << ", " << m._12 << ", " << m._13 << "; " << std::endl << m._21 << ", " << m._22 << ", " << m._23 << ";" << std::endl << m._31 << ", " << m._32 << ", " << m._33 << "]";
	}

	struct M44f
	{
		union {
			struct {
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			float m[4][4];
		};

		inline M44f operator+(M44f mat) {
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

		inline M44f operator-(M44f mat) {
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

		inline M44f operator*(float f) {
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

		inline V4f operator*(V4f v) {
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

		inline M44f operator*(M44f mat) {
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

		float trace(void);
		M44f t(void);
		//float det(void);
	};

	std::ostream& operator<<(std::ostream& os, const M44f& m) {
		return os << "[" << m._11 << ", " << m._12 << ", " << m._13 << ", " << m._14 << "; " << std::endl << m._21 << ", " << m._22 << ", " << m._23 << ", " << m._24 << ";" << std::endl << m._31 << ", " << m._32 << ", " << m._33 << ", " << m._34 << "; " << std::endl << m._41 << ", " << m._42 << ", " << m._43 << ", " << m._44 << "]";
	}
}