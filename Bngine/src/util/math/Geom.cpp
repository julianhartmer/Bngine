#include <math.h>
#include "util/math/Geom.h"

namespace Geom {
	Tri::Tri(const V3f(&vecs)[3]) {
		for (int i = 0; i < 3; ++i)
			_vecs[i] = V4f(vecs[i].x, vecs[i].y, vecs[i].z, 1);
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

	//V2f Tri::project(M44f)
	//{
	//	// TODO
	//}

	V4f Tri::update_normal(void)
	{
		V4f a, b;
		a = _vecs[1] - _vecs[0];
		b = _vecs[2] - _vecs[0];
		return a.cross(b).normalized();
	}

	Tri2D Tri::project(Camera c)
	{
		Tri2D projected;
		V4f tmp;
		for (int i = 0; i < 3; ++i) {
			tmp = c.projection() * _vecs[i];

			projected.tris[i] = (V2f(tmp.x, tmp.y));
		}
		return projected;
	}


	//////////
	// Mesh //
	//////////
	Mesh::Mesh(std::vector<Tri> tris)
	{
		this->tris = tris;
	}

	Mesh::Mesh() {
		tris.clear();
	}

	void Mesh::operator<<(Tri t) {
		tris.push_back(t);
	}

	std::vector<Tri2D> Mesh::project(Camera c)
	{
		std::vector<Tri2D> o;

		for (auto it = tris.begin(); it != tris.end(); ++it) {
			o.push_back(it->project(c));
		}


		return o;
	}

	Cube::Cube(V3f pos, float l)
		: Mesh(calculateTris(pos, l))
	{
	}

	std::vector<Tri> Cube::calculateTris(V3f pos, float l)
	{
		std::vector<Tri> tris;
		V3f front[4];
		V3f back[4];
		front[0] = pos;
		front[1] = V3f(pos.x + l, pos.y, pos.z);
		front[2] = V3f(pos.x + l, pos.y + l, pos.z);
		front[3] = V3f(pos.x, pos.y + l, pos.z);
		back[0] = V3f(pos.x, pos.y, pos.z + l);
		back[1] = V3f(pos.x + l, pos.y, pos.z + l);
		back[2] = V3f(pos.x + l, pos.y + l, pos.z + l);
		back[3] = V3f(pos.x, pos.y + l, pos.z + l);

		// front
		tris.push_back(Tri({ front[0], front[1], front[3] }));
		tris.push_back(Tri({ front[1], front[2], front[3] }));

		// back
		tris.push_back(Tri({ back[0], back[1], back[3] }));
		tris.push_back(Tri({ back[1], back[2], back[3] }));

		// right
		tris.push_back(Tri({ front[1], back[2], front[2] }));
		tris.push_back(Tri({ front[1], back[1], back[2] }));

		// left
		tris.push_back(Tri({ front[0], back[3], front[3] }));
		tris.push_back(Tri({ front[0], back[0], back[3] }));

		// top
		tris.push_back(Tri({ front[3], front[2], back[3] }));
		tris.push_back(Tri({ front[2], back[2], back[3] }));

		// bottom
		tris.push_back(Tri({ front[0], front[1], back[0] }));
		tris.push_back(Tri({ front[1], back[1], back[0] }));

		return tris;
	}
}