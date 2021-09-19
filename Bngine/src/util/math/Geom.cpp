#define _USE_MATH_DEFINES
#include <math.h>
#include "util/math/Geom.h"

#define BARYCENTER_CENTER_OF_VERTICES 0
#define BARYCENTER_CENTER_OF_EDGES 1
#define BARYCENTER_CENTER_OF_POLYGON 2
#define BARYCENTER BARYCENTER_CENTER_OF_VERTICES // 1: center of vertices, 2: center of edges, 3: center of polygon

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
	V4f Tri::normal(void) 
	{
		return _normal;
	}

	float Tri::area(void)
	{
		return (_vecs[1] - _vecs[0]).cross((_vecs[2] - _vecs[0])).norm() / 2.0f; // half cross-product formula
	}

	V4f Tri::vecs(int i)
	{
		if (0 > i || i >= 3)
			throw std::out_of_range("index of out range");
		return _vecs[i];
	}

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
			tmp = c.mProjection() * (c.mPosition() * _vecs[i]);
			tmp.x += 1;
			tmp.x *= x / 2.0f;
			tmp.y += 1;
			tmp.y *= y / 2.0f;
			projected.vertices[i] = (V2f(tmp.x, tmp.y));
		}
		return projected;
	}

	void Tri::move(V4f center, M44f move_mat)
	{
		for (int it = 0; it < 3; ++it)
		{
			_vecs[it] = (move_mat * (_vecs[it] - center)) + center;
		}
	}

	//////////
	// Geom //
	//////////

	V4f Geom::center()
	{
		return _center;
	}

	std::vector<Tri> Geom::tris()
	{
		return _tris;
	}

	std::vector<Tri2D> Geom::project(Camera c)
	{
		std::vector<Tri2D> o;

		for (auto it = _tris.begin(); it != _tris.end(); ++it) {
			o.push_back(it->project(c));
		}

		return o;
	}

	void Geom::_calc_center(void)
	{
		V4f avg = V4f(0, 0, 0, 0);
#if BARYCENTER == BARYCENTER_CENTER_OF_VERTICES
		// center of vertices: simple average of vertex coordinates
		for (auto it1 = _tris.begin(); it1 != _tris.end(); ++it1) {
			for (int it2 = 0; it2 < 3; ++it2)
			{
				avg += it1->vecs(it2); // averaging handled internally by V4f class (w component)
			}
		}
#elif BARYCENTER == BARYCENTER_CENTER_OF_EDGES
		// center of edges: average of edge midpoints weighted by edge length
		for (auto it1 = tris.begin(); it1 != tris.end(); ++it1) {
			// averaging handled again by V4f class (w component)
			avg += ((it1->vecs(0) - it1->vecs(1)) / 2 + it1->vecs(1)) * (it1->vecs(0) - it1->vecs(1)).norm();
			avg += ((it1->vecs(1) - it1->vecs(2)) / 2 + it1->vecs(2)) * (it1->vecs(1) - it1->vecs(2)).norm();
			avg += ((it1->vecs(2) - it1->vecs(0)) / 2 + it1->vecs(0)) * (it1->vecs(2) - it1->vecs(0)).norm();
		}
#elif BARYCENTER == BARYCENTER_CENTER_OF_POLYGON
		// center of polygon: average of the vertex coordinates weighted by polygon (tri) area
		for (auto it1 = tris.begin(); it1 != tris.end(); ++it1) {
			V4f avg_tmp = V4f(0, 0, 0, 0);
			for (int it2 = 0; it2 < 3; ++it2)
			{
				avg_tmp += it1->vecs(it2); // averaging handled internally by V4f class (w component)
			}
			avg += avg_tmp * it1->area();
		}
#endif // BARYCENTER
		avg.w = 0; // we want to use the center as a displacement later on, even though it's an actual location
		_center = avg;
	}

	void Geom::_move(M44f move_mat)
	{
		// uses the center vector to virtually displace the mesh such that its center is in the origin, then apply the 4x4 mat, then add the center displacement again
		for (auto it1 = _tris.begin(); it1 != _tris.end(); ++it1) {
			it1->move(_center, move_mat);
		}
		_center.x += move_mat.m[0][3];
		_center.y += move_mat.m[1][3];
		_center.z += move_mat.m[2][3];
	}

	void Geom::move(V3f translation, V3f rotation)
	{
		M44f move_mat = id44();
		if (translation)
		{
			move_mat.m[0][3] = translation.x;
			move_mat.m[1][3] = translation.y;
			move_mat.m[2][3] = translation.z;
		}
		if (rotation)
		{
			V3f rotation_rad = rotation * (M_PI / 180.0f);
			move_mat.m[0][1] = cos(rotation_rad.z) * sin(rotation_rad.y) * sin(rotation_rad.x) - sin(rotation_rad.z) * cos(rotation_rad.x);
			move_mat.m[0][2] = cos(rotation_rad.z) * sin(rotation_rad.y) * cos(rotation_rad.x) + sin(rotation_rad.z) * cos(rotation_rad.x);
			move_mat.m[1][1] = sin(rotation_rad.z) * sin(rotation_rad.y) * sin(rotation_rad.x) + cos(rotation_rad.z) * cos(rotation_rad.x);
			move_mat.m[1][2] = sin(rotation_rad.z) * sin(rotation_rad.y) * cos(rotation_rad.x) - cos(rotation_rad.z) * sin(rotation_rad.x);
			move_mat.m[2][0] = -sin(rotation_rad.y);
			move_mat.m[0][0] = cos(rotation_rad.z) * cos(rotation_rad.y);
			move_mat.m[1][0] = sin(rotation_rad.z) * cos(rotation_rad.y);
			move_mat.m[2][1] = cos(rotation_rad.y) * sin(rotation_rad.x);
			move_mat.m[2][2] = cos(rotation_rad.y) * cos(rotation_rad.x);
		}
		_move(move_mat);
	}

	//////////
	// Mesh //
	//////////

	Mesh::Mesh(std::vector<Tri> _tris)
	{
		this->_tris = _tris;
		_calc_center();
	}

	Mesh::Mesh() {
		_tris.clear();
	}

	void Mesh::operator<<(Tri t) {
		_tris.push_back(t);
	}

	//////////
	// Cube //
	//////////

	Cube::Cube(V3f pos, float l)
	{
		_tris = _calc_tris(pos.x, pos.y, pos.z, l);
		_calc_center();
	}

	Cube::Cube(float x, float y, float z, float l)
	{
		_tris = _calc_tris(x, y, z, l);
		_calc_center();
	}

	std::vector<Tri> Cube::_calc_tris(float x, float y, float z, float l)
	{
		std::vector<Tri> _tris;
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
		_tris.push_back(Tri({ front[0], front[1], front[3] }));
		_tris.push_back(Tri({ front[1], front[2], front[3] }));

		// back
		_tris.push_back(Tri({ back[0], back[1], back[3] }));
		_tris.push_back(Tri({ back[1], back[2], back[3] }));

		// right
		_tris.push_back(Tri({ front[1], back[2], front[2] }));
		_tris.push_back(Tri({ front[1], back[1], back[2] }));

		// left
		_tris.push_back(Tri({ front[0], back[3], front[3] }));
		_tris.push_back(Tri({ front[0], back[0], back[3] }));

		// top
		_tris.push_back(Tri({ front[3], front[2], back[3] }));
		_tris.push_back(Tri({ front[2], back[2], back[3] }));

		// bottom
		_tris.push_back(Tri({ front[0], front[1], back[0] }));
		_tris.push_back(Tri({ front[1], back[1], back[0] }));

		return _tris;
	}

	/////////////
	// Pyramid //
	/////////////

	Pyramid::Pyramid(float x, float y, float z, float l, float h)
	{
		_tris = _calc_tris(x, y, z, l, h);
		_calc_center();
	}

	std::vector<Tri> Pyramid::_calc_tris(float x, float y, float z, float l, float h)
	{
		std::vector<Tri> _tris;
		V3f baseandtip[5];
		baseandtip[0] = V3f(x, y, z);
		baseandtip[1] = V3f(x + l, y, z);
		baseandtip[2] = V3f(x + l, y, z + l);
		baseandtip[3] = V3f(x, y, z + l);
		baseandtip[4] = V3f(x + (l / 2.0f), y + h, z + (l / 2.0f));

		// bottom
		_tris.push_back(Tri({ baseandtip[0], baseandtip[1], baseandtip[3] }));
		_tris.push_back(Tri({ baseandtip[1], baseandtip[2], baseandtip[3] }));

		// front
		_tris.push_back(Tri({ baseandtip[0], baseandtip[1], baseandtip[4] }));

		// right
		_tris.push_back(Tri({ baseandtip[1], baseandtip[2], baseandtip[4] }));

		// left
		_tris.push_back(Tri({ baseandtip[0], baseandtip[3], baseandtip[4] }));

		// back
		_tris.push_back(Tri({ baseandtip[2], baseandtip[3], baseandtip[4] }));

		return _tris;
	}

	/////////////////
	// Icosahedron //
	/////////////////

	Icosahedron::Icosahedron(float x, float y, float z, float l)
	{
		_tris = _calc_tris(x, y, z, l);
		_calc_center();
	}

	std::vector<Tri> Icosahedron::_calc_tris(float x, float y, float z, float l)
	{
		float phi = 2.61803f; // golden ratio
		std::vector<Tri> _tris;
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

		_tris.push_back(Tri({ corners[0], corners[2], corners[8] }));
		_tris.push_back(Tri({ corners[0], corners[2], corners[10] }));
		_tris.push_back(Tri({ corners[0], corners[4], corners[8] }));
		_tris.push_back(Tri({ corners[0], corners[4], corners[6] }));
		_tris.push_back(Tri({ corners[0], corners[10], corners[6] }));

		_tris.push_back(Tri({ corners[2], corners[7], corners[5] }));
		_tris.push_back(Tri({ corners[2], corners[7], corners[10] }));
		_tris.push_back(Tri({ corners[2], corners[5], corners[8] }));
		_tris.push_back(Tri({ corners[8], corners[5], corners[9] }));
		_tris.push_back(Tri({ corners[8], corners[4], corners[9] }));
		
		_tris.push_back(Tri({ corners[10], corners[11], corners[7] }));
		_tris.push_back(Tri({ corners[3], corners[11], corners[1] }));
		_tris.push_back(Tri({ corners[3], corners[11], corners[7] }));
		_tris.push_back(Tri({ corners[3], corners[5], corners[7] }));
		_tris.push_back(Tri({ corners[3], corners[9], corners[1] }));

		_tris.push_back(Tri({ corners[3], corners[5], corners[9] }));
		_tris.push_back(Tri({ corners[1], corners[6], corners[11] }));
		_tris.push_back(Tri({ corners[1], corners[4], corners[6] }));
		_tris.push_back(Tri({ corners[1], corners[9], corners[4] }));
		_tris.push_back(Tri({ corners[6], corners[10], corners[11] }));

		return _tris;
	}
}