#include "pch.h"
#include "../Bngine/include/util/math/Mat.h"

using namespace Mat;

TEST(Mat, V2fTests) {
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