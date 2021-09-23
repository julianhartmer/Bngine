#pragma once
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

		// constructors
		V2f(float x, float y);
		V2f(float v[2]);
		V2f(void);

		// operators
		void operator=(V2f v);
		V2f operator+(V2f v);
		V2f operator-(V2f v);
		V2f operator-(void);
		V2f operator*(float f);
		V2f operator/(float f);
		void operator+=(V2f v);
		void operator-=(V2f v);
		void operator*=(float f);
		void operator/=(float f);
		bool operator==(V2f v);
		explicit operator bool() const;

		// methods
		float dot(V2f v);
		float norm(void);
		V2f normalized(void);
	};

	std::ostream &operator<<(std::ostream &os, const V2f &v);

	struct V4f; // forward declaration to make the add_w method compile
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

		V3f(void);
		V3f(float x, float y, float z);
		V3f(float v[3]);

		void operator=(V3f v);
		V3f operator+(V3f v);
		V3f operator-(V3f v);
		V3f operator-(void);
		V3f operator*(float f);
		V3f operator/(float f);
		void operator+=(V3f v);
		void operator-=(V3f v);
		void operator*=(float f);
		void operator/=(float f);
		bool operator==(V3f v);
		explicit operator bool() const;

		float dot(V3f v);
		V3f cross(V3f v);
		float norm(void);
		V3f normalized(void);
		V4f add_w(float w);
	};

	std::ostream &operator<<(std::ostream &os, const V3f &v);


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

		V4f(void);
		V4f(float x, float y, float z, float w);
		V4f(float v[4]);

		void operator=(V4f v);
		V4f operator+(V4f v);
		V4f operator-(V4f v);
		V4f operator-(void);
		V4f operator*(float f);
		V4f operator/(float f);
		void operator+=(V4f v);
		void operator-=(V4f v);
		void operator*=(float f);
		void operator/=(float f);
		bool operator==(V4f v);
		explicit operator bool() const;

		float dot(V4f v);
		V4f cross(V4f v);
		float norm(void);
		V4f normalized(void);
		V3f drop_w(void);
	};

	std::ostream &operator<<(std::ostream &os, const V4f &v);


	struct M22f
	{
		union {
			struct {
				float _11, _12;
				float _21, _22;
			};
			float m[2][2];
		};

		M22f(void);
		M22f(float e11, float e12, float e21, float e22);
		M22f(float const (&m)[2][2]);
		M22f(float const (&m)[4]);

		void operator=(M22f mat);
		M22f operator+(M22f mat);
		M22f operator-(M22f mat);
		M22f operator*(float f);
		M22f operator/(float f);
		V2f operator*(V2f v);
		M22f operator*(M22f mat);

		void set_column(V2f col, int col_num);
		void set_row(V2f row, int row_num);
		V2f get_column(int col_num);
		V2f get_row(int row_num);

		// == operator not defined for lack of use case (so far)
		float trace(void);
		M22f t(void);
		float det(void);
	};

	std::ostream &operator<<(std::ostream &os, const M22f &m);


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

		M33f(void);
		M33f(float const (&m)[3][3]);
		M33f(float const (&m)[9]);

		void operator=(M33f mat);
		M33f operator+(M33f mat);
		M33f operator-(M33f mat);
		M33f operator*(float f);
		M33f operator/(float f);
		V3f operator*(V3f v);
		M33f operator*(M33f mat);

		void set_column(V3f col, int col_num);
		void set_row(V3f row, int row_num);
		V3f get_column(int col_num);
		V3f get_row(int row_num);

		// == operator not defined for lack of use case (so far)
		float trace(void);
		M33f t(void);
		float det(void);
	};

	std::ostream &operator<<(std::ostream &os, const M33f &m);


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
		M44f(void);
		M44f(float const (&m)[4][4]);
		M44f(float const (&m)[16]);

		M44f operator+(M44f mat);
		M44f operator-(M44f mat);
		M44f operator*(float f);
		M44f operator/(float f);
		V4f operator*(V4f v);
		M44f operator*(M44f mat);

		void set_column(V4f col, int col_num);
		void set_row(V4f row, int row_num);
		V4f get_column(int col_num);
		V4f get_row(int row_num);

		float trace(void);
		M44f t(void);
		float det(void);
		M33f minor(int row, int col);
	};

	std::ostream &operator<<(std::ostream &os, const M44f &m);

	struct M23f
	{
		union {
			struct {
				float _11, _12, _13;
				float _21, _22, _23;
			};
			float m[2][3];
		};
		M23f(void);
		M23f(float const (&m)[2][3]);
		M23f(float const (&m)[6]);

		M23f operator+(M23f mat);
		M23f operator-(M23f mat);
		M23f operator*(float f);
		M23f operator/(float f);
		V2f operator*(V3f v);
		//M23f operator*(M23f mat); // no use case so far

		//float trace(void); // does not exist
		//M32f t(void); // no use case so far
		//float det(void); // does not exist
	};

	std::ostream& operator<<(std::ostream& os, const M23f& m);

	struct M34f
	{
		union {
			struct {
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
			};
			float m[3][4];
		};
		M34f(void);
		M34f(float const (&m)[3][4]);
		M34f(float const (&m)[12]);

		M34f operator+(M34f mat);
		M34f operator-(M34f mat);
		M34f operator*(float f);
		M34f operator/(float f);
		V3f operator*(V4f v);
		//M34f operator*(M34f mat); // no use case so far

		//float trace(void); // does not exist
		//M43f t(void); // no use case so far
		//float det(void); // does not exist
	};

	std::ostream& operator<<(std::ostream& os, const M34f& m);

	M22f id22(void);
	M33f id33(void);
	M44f id44(void);
}