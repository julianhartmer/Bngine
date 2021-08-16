#include "pch.h"
#include "../Bngine/include/util/math/Mat.h"

using namespace Mat;

TEST(Mat, V2foperators) {
	V2f v1(1, 2), v2(3, 4), res;
	res = v2 - v1;
	EXPECT_FLOAT_EQ(res.x, 2.0f);
	EXPECT_FLOAT_EQ(res.y, 2.0f);

	res = v2 * 2;
	EXPECT_FLOAT_EQ(res.x, 6.0f);
	EXPECT_FLOAT_EQ(res.y, 8.0f);

	res = v1 + v2;
	EXPECT_FLOAT_EQ(res.x, 4.0f);
	EXPECT_FLOAT_EQ(res.y, 6.0f);

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
	res = v2 - v1;
	EXPECT_FLOAT_EQ(res.x, 3.0f);
	EXPECT_FLOAT_EQ(res.y, 3.0f);
	EXPECT_FLOAT_EQ(res.z, 3.0f);

	res = v2 * 2;
	EXPECT_FLOAT_EQ(res.x, 8.0f);
	EXPECT_FLOAT_EQ(res.y, 10.0f);
	EXPECT_FLOAT_EQ(res.z, 12.0f);

	res = v1 + v2;
	EXPECT_FLOAT_EQ(res.x, 5.0f);
	EXPECT_FLOAT_EQ(res.y, 7.0f);
	EXPECT_FLOAT_EQ(res.z, 9.0f);

	EXPECT_FALSE(v1 == v2);

	res = v1;
	EXPECT_TRUE(v1 == res);
}

TEST(Mat, V3fmethods) {
	V3f v1(1, 12, 12), v2(4, 5,20), v3(19.542f, 4.21f, 12.5943f), res;
	EXPECT_FLOAT_EQ(v1.norm(), 17.0f);
	EXPECT_FLOAT_EQ(v2.norm(), 21.0f);

	res = v3.normalized();
	EXPECT_FLOAT_EQ(res.norm(), 1.0f);
	res = v1.normalized();
	EXPECT_FLOAT_EQ(res.x, 0.05882352941f);
	EXPECT_FLOAT_EQ(res.y, 0.70588235294f);
	EXPECT_FLOAT_EQ(res.z, 0.70588235294f);

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

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}