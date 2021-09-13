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
		int x = c.camera_width();
		int y = c.camera_height();
		for (int i = 0; i < 3; ++i) {
			tmp = c.projection() * _vecs[i];
			tmp.x += 1;
			tmp.x *= x / 2.0f;
			tmp.y += 1;
			tmp.y *= y / 2.0f;
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
		: Mesh(calculateTris(pos.x, pos.y, pos.z, l))
	{
	}

	Cube::Cube(float x, float y, float z, float l)
		: Mesh(calculateTris(x, y, z, l))
	{
	}

	std::vector<Tri> Cube::calculateTris(float x, float y, float z, float l)
	{
		std::vector<Tri> tris;
		V3f front[4];
		V3f back[4];
		front[0] = V3f(x, y, z);
		front[1] = V3f(x + l, y, z);
		front[2] = V3f(x + l, y + l, z);
		front[3] = V3f(x, y + l, z);
		back[0] = V3f(x, y, z + l);
		back[1] = V3f(x + l, y, z + l);
		back[2] = V3f(x + l, y + l, z + l);
		back[3] = V3f(x, y + l, z + l);

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

	Pyramid::Pyramid(float x, float y, float z, float l, float h)
		: Mesh(calculateTris(x, y, z, l, h))
	{
	}

	std::vector<Tri> Pyramid::calculateTris(float x, float y, float z, float l, float h)
	{
		std::vector<Tri> tris;
		V3f baseandtip[5];
		baseandtip[0] = V3f(x, y, z);
		baseandtip[1] = V3f(x + l, y, z);
		baseandtip[2] = V3f(x + l, y, z + l);
		baseandtip[3] = V3f(x, y, z + l);
		baseandtip[4] = V3f(x + (l / 2.0f), y + h, z + (l / 2.0f));

		// bottom
		tris.push_back(Tri({ baseandtip[0], baseandtip[1], baseandtip[3] }));
		tris.push_back(Tri({ baseandtip[1], baseandtip[2], baseandtip[3] }));

		// front
		tris.push_back(Tri({ baseandtip[0], baseandtip[1], baseandtip[4] }));

		// right
		tris.push_back(Tri({ baseandtip[1], baseandtip[2], baseandtip[4] }));

		// left
		tris.push_back(Tri({ baseandtip[0], baseandtip[3], baseandtip[4] }));

		// back
		tris.push_back(Tri({ baseandtip[2], baseandtip[3], baseandtip[4] }));

		return tris;
	}

	Icosahedron::Icosahedron(float x, float y, float z, float l)
		: Mesh(calculateTris(x, y, z, l))
	{
	}

	std::vector<Tri> Icosahedron::calculateTris(float x, float y, float z, float l)
	{
		float phi = 2.61803; //golden ratio
		std::vector<Tri> tris;
		V3f displacement = V3f(x, y, z);
		V3f corners[12];
		float len_mul = l / 2.0f;
		// corners of a Icosahedron of edge length 2 taken from Wikipedia
		corners[0] = V3f(0, 1, phi) * len_mul + displacement;
		corners[1] = V3f(0, 1, -phi) * len_mul + displacement;
		corners[2] = V3f(0, -1, phi) * len_mul + displacement;
		corners[3] = V3f(0, -1, -phi) * len_mul + displacement;

		corners[4] = V3f(1, phi, 0) * len_mul + displacement;
		corners[5] = V3f(1, -phi, 0) * len_mul + displacement;
		corners[6] = V3f(-1, phi, 0) * len_mul + displacement;
		corners[7] = V3f(-1, -phi, 0) * len_mul + displacement;

		corners[8] = V3f(phi, 0, 1) * len_mul + displacement;
		corners[9] = V3f(phi, 0, -1) * len_mul + displacement;
		corners[10] = V3f(-phi, 0, 1) * len_mul + displacement;
		corners[11] = V3f(-phi, 0, -1) * len_mul + displacement;

		tris.push_back(Tri({ corners[0], corners[2], corners[8] }));
		tris.push_back(Tri({ corners[0], corners[2], corners[10] }));
		tris.push_back(Tri({ corners[0], corners[4], corners[8] }));
		tris.push_back(Tri({ corners[0], corners[4], corners[6] }));
		tris.push_back(Tri({ corners[0], corners[10], corners[6] }));

		tris.push_back(Tri({ corners[2], corners[7], corners[5] }));
		tris.push_back(Tri({ corners[2], corners[7], corners[10] }));
		tris.push_back(Tri({ corners[2], corners[5], corners[8] }));
		tris.push_back(Tri({ corners[8], corners[5], corners[9] }));
		tris.push_back(Tri({ corners[8], corners[4], corners[9] }));
		
		tris.push_back(Tri({ corners[10], corners[11], corners[7] }));
		tris.push_back(Tri({ corners[3], corners[11], corners[1] }));
		tris.push_back(Tri({ corners[3], corners[11], corners[7] }));
		tris.push_back(Tri({ corners[3], corners[5], corners[7] }));
		tris.push_back(Tri({ corners[3], corners[9], corners[1] }));

		tris.push_back(Tri({ corners[3], corners[5], corners[9] }));
		tris.push_back(Tri({ corners[1], corners[6], corners[11] }));
		tris.push_back(Tri({ corners[1], corners[4], corners[6] }));
		tris.push_back(Tri({ corners[1], corners[9], corners[4] }));
		tris.push_back(Tri({ corners[6], corners[10], corners[11] }));

		return tris;
	}
}