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
	EXPECT_VF_EQ((v1 + v2), V2f({ 4.0f, 6.0f }));

	EXPECT_FALSE(v1 == v2);
	res = v1;
	EXPECT_TRUE(v1 == res);
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
	EXPECT_VF_EQ((v2 + v1), V3f({ 5.0f, 7.0f, 9.0f }));

	EXPECT_FALSE(v1 == v2);

	res = v1;
	EXPECT_TRUE(v1 == res);
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
	V4f v1({ 3.0f, 4.2f, 3.3f, 1.0f }), v2({ 10, 5, 20, 31 }), v3({ 19.542f, 4.21f, 12.5943f, 3.61f }), res;

	EXPECT_VF_EQ((v1 + v2), V4f({ 13.0f, 9.2f, 23.3f, 32.0f }));
	EXPECT_VF_EQ((v2 - v1), V4f({ 7.0f, 0.8f, 16.7f, 30.0f }));
	EXPECT_VF_EQ((v1 * 2), V4f({ 6.0f, 8.4f, 6.6f, 2.0f }));

	EXPECT_FALSE(v1 == v2);
	res = v1;
	EXPECT_TRUE(v1 == res);
}

TEST(Mat, V4fmethods) {
	// TODO
	EXPECT_TRUE(false);
}

TEST(Mat, Mat22operators) {
	M22f a(1.0f, 2.0f, 3.0f, 4.0f), b(0.5f, 1.5f, 2.5f, 3.5f), tmp;

	EXPECT_MF_EQ((a - b), M22f({ {0.5f, 0.5f}, {0.5f, 0.5f} }));
	EXPECT_MF_EQ((a + b), M22f({ {1.5f, 3.5f}, {5.5f, 7.5f} }));
	EXPECT_MF_EQ((a * 2), M22f({ {2.0f, 4.0f}, {6.0f, 8.0f} }));
	EXPECT_VF_EQ((a * V2f(3.0f, 7.0f)), V2f(17.0f, 37.0f));
	EXPECT_MF_EQ((a * b), M22f({ {5.5f, 8.5f}, {11.5f, 18.5f} }));
}

TEST(Mat, Mat22methods) {
	// TODO
	EXPECT_TRUE(false);
}

TEST(Mat, Mat33operators) {
	// TODO
	EXPECT_TRUE(false);
}

TEST(Mat, Mat33methods) {
	// TODO
	EXPECT_TRUE(false);
}

TEST(Mat, Mat44operators) {
	// TODO
	EXPECT_TRUE(false);
}

TEST(Mat, Mat44methods) {
	// TODO
	EXPECT_TRUE(false);
}

TEST(Mat, Mat23operators) {
	// TODO
	EXPECT_TRUE(false);
}

TEST(Mat, Mat23methods) {
	// TODO
	EXPECT_TRUE(false);
}

TEST(Mat, Mat34operators) {
	// TODO
	EXPECT_TRUE(false);
}

TEST(Mat, Mat34methods) {
	// TODO
	EXPECT_TRUE(false);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}