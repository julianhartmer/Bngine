#include <math.h>
#include "util/math/Geom.h"

namespace Geom {
	Tri::Tri(const V3f(&vecs)[3]) {
		memcpy(&this->_vecs, vecs, sizeof(vecs));
		for (V4f v : _vecs) {
			v.w = 1;
		}
		_normal = update_normal();
	}

	//void Tri::operator=(Tri t) {
	//	_v[0] = t.v(0);
	//	_v[1] = t.v(1);
	//	_v[2] = t.v(2);
	//	_normal = t.normal();
	//}

	/*Tri Tri::operator*(float f) {
		return Tri({ _v[0] * f, _v[1] * f, _v[2] * f });
	}

	Tri Tri::operator/(float f) {
		return Tri({ _v[0] / f, _v[1] / f, _v[2] / f });
	}

	void Tri::operator*=(float f) {
		Tri o = *this;

		for (int i = 0; i < 3; ++i) {
			_v[i] = _v[i] * f;
		}

		return o;
	}*/

	//void Tri::operator/=(float f) {
	//	Tri o = *this;

	//	for (int i = 0; i < 3; ++i) {
	//		_v[i] = _v[i] / f;
	//	}

	//	return o;
	//}


	/**
	*
	*	Calculates surface normal via counter-clockwise convention.
	*
	*	\return surface normal
	**/
	V4f Tri::normal(void) {
		return _normal;
	}

	V4f Tri::vecs(int i)
	{
		if (0 > i || i >= 3)
			throw std::out_of_range("index of out range");
		return _vecs[i];
	}

	V2f Tri::project(M44f)
	{
		// TODO
	}

	V4f Tri::update_normal(void)
	{
		V4f a, b;
		a = _vecs[1] - _vecs[0];
		b = _vecs[2] - _vecs[0];
		return a.cross(b).normalized();
	}


	//////////
	// Mesh //
	//////////
	Mesh::Mesh() {
		tris.clear();
	}

	void Mesh::operator<<(Tri t) {
		tris.push_back(t);
	}
}