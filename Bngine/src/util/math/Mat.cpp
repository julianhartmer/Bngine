#include "../../../include/util/math/Mat.h"
#include <math.h>

namespace Mat {
	float V2f::norm(void) {
		return sqrt(x * x + y * y);
	}
}