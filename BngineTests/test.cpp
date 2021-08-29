#include "pch.h"
#include "../Bngine/include/util/math/Mat.h"

using namespace Mat;
#define EXPECT_VF_EQ(A,B)\
	do {\
		for (int i = 0; i < sizeof(A.v)/sizeof(A.v[0]); ++i) {\
			EXPECT_FLOAT_EQ(A.v[i], B.v[i]);\
		}\
	} while (false)


#define EXPECT_MF_EQ(A,B)\
	do {\
		for (int y = 0; y < sizeof(A.m)/sizeof(A.m[0]); ++y) {\
			for (int x = 0; x < sizeof(A.m[0])/sizeof(A.m[0][0]); ++x) {\
				EXPECT_FLOAT_EQ(A.m[y][x], B.m[y][x]);\
			}\
		}\
	} while (false)
	

TEST(Mat, V2foperators) {
	V2f v1(1, 2), v2(3, 4), res;

	EXPECT_VF_EQ((v2 - v1), V2f({ 2.0f, 2.0f }));
	EXPECT_VF_EQ((v2 * 2), V2f({ 6.0f, 8.0f }));
	EXPECT_VF_EQ((v2 / 2), V2f({ 1.5f, 2.0f }));
	EXPECT_VF_EQ((v1 + v2), V2f({ 4.0f, 6.0f }));

	EXPECT_FALSE(v1 == v2);
	res = v1;
	EXPECT_TRUE(v1 == res);
	res += v1;
	EXPECT_VF_EQ((v1 * 2), res);
	res -= v1;
	EXPECT_VF_EQ(res, v1);
	res *= 2;
	EXPECT_VF_EQ((v1 * 2), res);
	res /= 2;
	EXPECT_VF_EQ(v1, res);
	EXPECT_TRUE(isinf((v1 / 0).x));
	EXPECT_TRUE(isinf((v1 / 0).y));
}

TEST(Mat, V2fmethods) {
	V2f v1(3, 4), v2(20, 21), v3(19.542f, 4.21f), res;
	EXPECT_FLOAT_EQ(v1.norm(), 5.0f);
	EXPECT_FLOAT_EQ(v2.norm(), 29.0f);

	res = v3.normalized();
	EXPECT_FLOAT_EQ(res.norm(), 1.0f);
	res = v1.normalized();
	EXPECT_FLOAT_EQ(res.x, 0.6f);
	EXPECT_FLOAT_EQ(res.y, 0.8f);

	EXPECT_FLOAT_EQ(v1.dot(v2), 144.0f);
	EXPECT_FLOAT_EQ(v2.dot(v1), 144.0f);
	EXPECT_FLOAT_EQ(v1.dot(v3), 75.466f);
}

TEST(Mat, V3foperators) {
	V3f v1(1, 2, 3), v2(4, 5, 6), res;

	EXPECT_VF_EQ((v2 - v1), V3f({ 3.0f, 3.0f, 3.0f }));
	EXPECT_VF_EQ((v2 * 2), V3f({ 8.0f, 10.0f, 12.0f }));
	EXPECT_VF_EQ((v2 / 2), V3f({ 2.0f, 2.5f, 3.0f }));
	EXPECT_VF_EQ((v2 + v1), V3f({ 5.0f, 7.0f, 9.0f }));

	EXPECT_FALSE(v1 == v2);

	res = v1;
	EXPECT_TRUE(v1 == res);
	res += v1;
	EXPECT_VF_EQ((v1 * 2), res);
	res -= v1;
	EXPECT_VF_EQ(res, v1);
	res *= 2;
	EXPECT_VF_EQ((v1 * 2), res);
	res /= 2;
	EXPECT_VF_EQ(v1, res);
	EXPECT_TRUE(isinf((v1 / 0).x));
	EXPECT_TRUE(isinf((v1 / 0).y));
	EXPECT_TRUE(isinf((v1 / 0).z));
}

TEST(Mat, V3fmethods) {
	V3f v1(1, 12, 12), v2(4, 5, 20), v3(19.542f, 4.21f, 12.5943f), res;
	EXPECT_FLOAT_EQ(v1.norm(), 17.0f);
	EXPECT_FLOAT_EQ(v2.norm(), 21.0f);

	res = v3.normalized();
	EXPECT_FLOAT_EQ(res.norm(), 1.0f);
	res = v1.normalized();
	EXPECT_VF_EQ((res), V3f({ 0.05882352941f, 0.70588235294f, 0.70588235294f }));

	res = V3f(180, 28, -43);
	EXPECT_TRUE(v1.cross(v2) == res);
	EXPECT_FALSE(v2.cross(v1) == res);
	res = res * (-1);
	EXPECT_FALSE(v1.cross(v2) == res);
	EXPECT_TRUE(v2.cross(v1) == res);

	EXPECT_FLOAT_EQ(v1.dot(v2), 304.0f);
	EXPECT_FLOAT_EQ(v2.dot(v1), 304.0f);
	EXPECT_FLOAT_EQ(v1.dot(v3), 221.1936f);
}

TEST(Mat, V4foperators) {
	// v1, v4 positions, v2,v3 displacements
	V4f v1({ 3.0f, 4.2f, 3.3f, 1.0f }), v2({ 10, 5, 20, 0 }), v3({ 19.542f, 4.21f, 12.5943f, 0 }), v4({ 2.15f, 1.71f, 27.444f, 1 }), res;

	// position + displacement = position
	EXPECT_VF_EQ((v1 + v2), V4f({ 13.0f, 9.2f, 23.3f, 1.0f }));
	// displacement - position = -(position) + displacement = position (w component should be 1 even if the nominal operation should result in -1)
	EXPECT_VF_EQ((v2 - v1), V4f({ 7.0f, 0.8f, 16.7f, 1.0f }));
	// position + position = average position
	EXPECT_VF_EQ((v1 + v4), V4f({2.575f, 2.955f, 15.372f, 1.0f}));
	// position - position = displacement
	EXPECT_VF_EQ((v1 - v4), V4f({ 0.85f, 2.49f, -24.144f, 0.0f }));
	// displacement - displacement = displacement
	EXPECT_VF_EQ((v2 - v3), V4f({ -9.542f, 0.79f, 7.4057f, 0.0f }));
	// displacement + displacement = displacement
	EXPECT_VF_EQ((v2 + v3), V4f({ 29.542f, 9.21f, 32.5943f, 0.0f }));

	// scaling position = position
	EXPECT_VF_EQ((v1 * 2), V4f({ 6.0f, 8.4f, 6.6f, 1.0f }));
	EXPECT_VF_EQ((v1 / 2), V4f({ 1.5f, 2.1f, 1.65f, 1.0f }));
	// scaling displacement = displacement
	EXPECT_VF_EQ((v2 * 2), V4f({ 20.0f, 10.0f, 40.0f, 0.0f }));
	EXPECT_VF_EQ((v2 / 2), V4f({ 5.0f, 2.5f, 10.0f, 0.0f }));

	EXPECT_TRUE(isinf((v1 / 0).x));
	EXPECT_TRUE(isinf((v1 / 0).y));
	EXPECT_TRUE(isinf((v1 / 0).z));

	EXPECT_FALSE(v1 == v2);
	res = v1;
	EXPECT_TRUE(v1 == res);
	res += v1;
	EXPECT_VF_EQ(v1, res);
	res -= v1;
	EXPECT_VF_EQ(res, V4f(0,0,0,0));
	res += v1;
	res *= 2;
	EXPECT_VF_EQ((v1 * 2), res);
	res /= 2;
	EXPECT_VF_EQ(v1, res);
}

TEST(Mat, V4fmethods) {
	V4f v1(1, 12, 12, 0), v2(4, 5, 20, 0), v3(1, 12, 12, 1), v4(4, 5, 20, 1), v5(17.23, 8.1832, 92.123, 1), res;
	EXPECT_FLOAT_EQ(v1.norm(), 17.0f);
	EXPECT_FLOAT_EQ(v2.norm(), 21.0f);
	EXPECT_FLOAT_EQ(v3.norm(), 17.0f);
	EXPECT_FLOAT_EQ(v4.norm(), 21.0f);

	res = v5.normalized();
	EXPECT_FLOAT_EQ(res.norm(), 1.0f);
	res = v1.normalized();
	EXPECT_VF_EQ((res), V4f({ 0.05882352941f, 0.70588235294f, 0.70588235294f, 0.0f }));
	res = v3.normalized(); // normalized verison of position also produces displacement
	EXPECT_VF_EQ((res), V4f({ 0.05882352941f, 0.70588235294f, 0.70588235294f, 0.0f }));

	res = V4f(180, 28, -43, 0);
	EXPECT_TRUE(v1.cross(v2) == res);
	EXPECT_FALSE(v2.cross(v1) == res);
	EXPECT_TRUE(v3.cross(v4) == res); // cross product produces displacement even when using position
	EXPECT_FALSE(v4.cross(v3) == res);
	res = res * (-1);
	EXPECT_FALSE(v1.cross(v2) == res);
	EXPECT_TRUE(v2.cross(v1) == res);
	EXPECT_FALSE(v3.cross(v4) == res);
	EXPECT_TRUE(v4.cross(v3) == res);

	EXPECT_FLOAT_EQ(v1.dot(v2), 304.0f);
	EXPECT_FLOAT_EQ(v2.dot(v1), 304.0f);
	EXPECT_FLOAT_EQ(v3.dot(v4), 304.0f); // dot product should ignore w
	EXPECT_FLOAT_EQ(v4.dot(v3), 304.0f);
	EXPECT_FLOAT_EQ(v1.dot(v5), 1220.9044f);
	EXPECT_FLOAT_EQ(v3.dot(v5), 1220.9044f);
}

TEST(Mat, Mat22operators) {
	M22f a(1.0f, 2.0f, 3.0f, 4.0f), b(0.5f, 1.5f, 2.5f, 3.5f), tmp;

	EXPECT_MF_EQ((a - b), M22f({ {0.5f, 0.5f}, {0.5f, 0.5f} }));
	EXPECT_MF_EQ((a + b), M22f({ {1.5f, 3.5f}, {5.5f, 7.5f} }));
	EXPECT_MF_EQ((a * 2), M22f({ {2.0f, 4.0f}, {6.0f, 8.0f} }));
	EXPECT_MF_EQ((a / 2), M22f({ {0.5f, 1.0f}, {1.5f, 2.0f} }));
	EXPECT_VF_EQ((a * V2f(3.0f, 7.0f)), V2f(17.0f, 37.0f));
	EXPECT_MF_EQ((a * b), M22f({ {5.5f, 8.5f}, {11.5f, 18.5f} }));
}

TEST(Mat, Mat22methods) {
	M22f a(1.0f, 2.0f, 3.0f, 4.0f);
	EXPECT_FLOAT_EQ(a.trace(), 5.0f);
	EXPECT_MF_EQ(a.t(), M22f({ {1.0f, 3.0f}, {2.0f, 4.0f} }));
	EXPECT_FLOAT_EQ(a.det(), -2.0f);
}

TEST(Mat, Mat33operators) {
	M33f a({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f }), b({ 0.5f, 1.5f, 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f, 8.5f }), tmp;

	EXPECT_MF_EQ((a - b), M33f({ {0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f} }));
	EXPECT_MF_EQ((a + b), M33f({ {1.5f, 3.5f, 5.5f}, {7.5f, 9.5f, 11.5f}, {13.5f, 15.5f, 17.5f} }));
	EXPECT_MF_EQ((a * 2), M33f({ 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f }));
	EXPECT_MF_EQ((a / 2), M33f({ 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f }));
	EXPECT_VF_EQ((a * V3f(3.0f, 7.0f, 11.0f)), V3f(50.0f, 113.0f, 176.0f));
	EXPECT_MF_EQ((a * b), M33f({ {27.0f, 33.0f, 39.0f}, {58.5f, 73.5f, 88.5f}, {90.0f, 114.0f, 138.0f} }));
}

TEST(Mat, Mat33methods) {
	M33f a({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f });
	EXPECT_FLOAT_EQ(a.trace(), 15.0f);
	EXPECT_MF_EQ(a.t(), M33f({ 1.0f, 4.0f, 7.0f, 2.0f, 5.0f, 8.0f, 3.0f, 6.0f, 9.0f }));
	EXPECT_FLOAT_EQ(a.det(), 0.0f);
}

TEST(Mat, Mat44operators) {
	M44f a({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f }), b({ 0.5f, 1.5f, 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f, 8.5f, 9.5f, 10.5f, 11.5f, 12.5f, 13.5f, 14.5f, 15.5f }), tmp;

	EXPECT_MF_EQ((a - b), M44f({ {0.5f, 0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f, 0.5f} }));
	EXPECT_MF_EQ((a + b), M44f({ {1.5f, 3.5f, 5.5f, 7.5f}, {9.5f, 11.5f, 13.5f, 15.5f}, {17.5f, 19.5f, 21.5f, 23.5f}, {25.5f, 27.5f, 29.5f, 31.5f} }));
	EXPECT_MF_EQ((a * 2), M44f({ 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f }));
	EXPECT_MF_EQ((a / 2), M44f({ 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f }));
	EXPECT_VF_EQ((a * V4f(3.0f, 7.0f, 11.0f, 0.0f)), V4f(50.0f, 134.0f, 218.0f, 302.0f));
	EXPECT_MF_EQ((a * b), M44f({ {85.0f, 95.0f, 105.0f, 115.0f}, {189.0f, 215.0f, 241.0f, 267.0f}, {293.0f, 335.0f, 377.0f, 419.0f}, {397.0f, 455.0f, 513.0f, 571.0f} }));
}

TEST(Mat, Mat44methods) {
	M44f a({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f });
	EXPECT_FLOAT_EQ(a.trace(), 34.0f);
	EXPECT_MF_EQ(a.t(), M44f({ 1.0f, 5.0f, 9.0f, 13.0f, 2.0f, 6.0f, 10.0f, 14.0f, 3.0f, 7.0f, 11.0f, 15.0f, 4.0f, 8.0f, 12.0f, 16.0f }));
	EXPECT_FLOAT_EQ(a.det(), 0.0f);
}

TEST(Mat, Mat23operators) {
	M23f a({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f }), b({ 0.5f, 1.5f, 2.5f, 3.5f, 4.5f, 5.5f }), tmp;

	EXPECT_MF_EQ((a - b), M23f( {0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f} ));
	EXPECT_MF_EQ((a + b), M23f( {1.5f, 3.5f, 5.5f, 7.5f, 9.5f, 11.5f} ));
	EXPECT_MF_EQ((a * 2), M23f({ 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f }));
	EXPECT_MF_EQ((a / 2), M23f({ 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f }));
	EXPECT_VF_EQ((a * V3f(3.0f, 7.0f, 11.0f)), V2f(50.0f, 113.0f));
}

TEST(Mat, Mat23methods) {
	// no methods for M23f so far
	EXPECT_TRUE(true);
}

TEST(Mat, Mat34operators) {
	M34f a({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f }), b({ 0.5f, 1.5f, 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f, 8.5f, 9.5f, 10.5f, 11.5f }), tmp;

	EXPECT_MF_EQ((a - b), M34f({ 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f}));
	EXPECT_MF_EQ((a + b), M34f({ 1.5f, 3.5f, 5.5f, 7.5f, 9.5f, 11.5f, 13.5f, 15.5f, 17.5f, 19.5f, 21.5f, 23.5f }));
	EXPECT_MF_EQ((a * 2), M34f({ 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f, 22.0f, 24.0f }));
	EXPECT_MF_EQ((a / 2), M34f({ 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f }));
	EXPECT_VF_EQ((a * V4f(3.0f, 7.0f, 11.0f, 0.0f)), V3f(50.0f, 134.0f, 218.0f));
}

TEST(Mat, Mat34methods) {
	// no methods for M34f so far
	EXPECT_TRUE(true);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}