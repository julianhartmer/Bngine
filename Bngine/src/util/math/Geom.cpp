#define _USE_MATH_DEFINES
#include <math.h>
#include "util/math/Geom.h"
#include "SDL.h"

#define BARYCENTER_CENTER_OF_VERTICES 0
#define BARYCENTER_CENTER_OF_EDGES 1
#define BARYCENTER_CENTER_OF_POLYGON 2
#define BARYCENTER BARYCENTER_CENTER_OF_VERTICES // 1: center of vertices, 2: center of edges, 3: center of polygon

namespace Bngine {
	Tri::Tri(const V3f(&vecs)[3]) {
		for (int i = 0; i < 3; ++i)
			_vecs[i] = V4f(vecs[i].x, vecs[i].y, vecs[i].z, 1);
		_normal = _update_normal();
	}

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

	V4f Tri::_update_normal(void)
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
		int x = c.projection_width();
		int y = c.projection_height();
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

	void Tri::move(V4f center, M44f& move_mat)
	{
		for (int it = 0; it < 3; ++it)
		{
			_vecs[it] = (move_mat * (_vecs[it] - center)) + center;
		}
		_update_normal();
	}

	//////////
	// Geom //
	//////////

	V4f Geom::position()
	{
		return _position;
	}

	V3f Geom::rotation()
	{
		return _rotation;
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

	V4f Geom::_calc_center(void)
	{
		V4f avg = V4f(0, 0, 0, 0); // we want to use the center as a displacement later on, even though it's an actual location, so w=0
		
		int normalize = _tris.size()*3;
#if BARYCENTER == BARYCENTER_CENTER_OF_VERTICES
		// center of vertices: simple average of vertex coordinates
		for (auto it1 = _tris.begin(); it1 != _tris.end(); ++it1) {
			for (int it2 = 0; it2 < 3; ++it2)
			{
				avg.x += it1->vecs(it2).x;
				avg.y += it1->vecs(it2).y;
				avg.z += it1->vecs(it2).z;
			}
		}
#elif BARYCENTER == BARYCENTER_CENTER_OF_EDGES
		// center of edges: average of edge midpoints weighted by edge length
		V4f tmp1, tmp2, tmp3;
		for (auto it1 = _tris.begin(); it1 != _tris.end(); ++it1) {
			tmp1 = ((it1->vecs(0) - it1->vecs(1)) / 2 + it1->vecs(1)) * (it1->vecs(0) - it1->vecs(1)).norm();
			tmp2 = ((it1->vecs(1) - it1->vecs(2)) / 2 + it1->vecs(2)) * (it1->vecs(1) - it1->vecs(2)).norm();
			tmp3 = ((it1->vecs(2) - it1->vecs(0)) / 2 + it1->vecs(0)) * (it1->vecs(2) - it1->vecs(0)).norm();

			avg.x += tmp1.x;
			avg.y += tmp1.y;
			avg.z += tmp1.z;
			avg.x += tmp2.x;
			avg.y += tmp2.y;
			avg.z += tmp2.z;
			avg.x += tmp3.x;
			avg.y += tmp3.y;
			avg.z += tmp3.z;
		}
#elif BARYCENTER == BARYCENTER_CENTER_OF_POLYGON
		// center of polygon: average of the vertex coordinates weighted by polygon (tri) area
		for (auto it1 = _tris.begin(); it1 != _tris.end(); ++it1) {
			V4f avg_tmp = V4f(0, 0, 0, 0);
			for (int it2 = 0; it2 < 3; ++it2)
			{
				avg_tmp.x += it1->vecs(it2).x;
				avg_tmp.y += it1->vecs(it2).y;
				avg_tmp.z += it1->vecs(it2).z;
			}
			avg += avg_tmp * it1->area();
		}
#endif // BARYCENTER 
		return (avg / float(normalize));
	}

	void Geom::_move(M44f& move_mat)
	{
		// uses the center vector to virtually displace the mesh such that its center is in the origin, then apply the 4x4 mat, then add the center displacement again
		for (auto it1 = _tris.begin(); it1 != _tris.end(); ++it1) {
			it1->move(_position, move_mat);
		}	
	}

	/**
	*
	*	Moves a geom via rotation and translation (in that order). Via the optional parameters it can be specified whether motion is relative to current position or to the origin. For rotation
	*   a point of reference can be given, otherwise the geom's center is used.
	*
	*	\param translation V3f vector that contains the desired displacement (or the target position of the geom's center, if addtive_motion is set to false)
	*   \param rotation V3f vector that contains the desired additive rotation around the geom's center (or rotation_point, if it is non-zero)
	*   \param additive_rotation Bool that determines whether translation will be added on top of the current position or interpreted as target coordinates for the geom's center
	*   \param rotation_point V3f that determines the point around which the rotation will be performed, if left out will default to geom's center
	**/
	void Geom::move(V3f translation, V3f rotation, bool additive_translation, V3f rotation_point)
	{
		M44f move_mat = id44();
		if (translation)
		{
			if (additive_translation)
			{
				move_mat.set_column(translation.add_w(1), 4);
			}
			else
			{
				V4f displacement = translation.add_w(1) - _position;
				move_mat.set_column(displacement, 4);
			}		
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
			if (rotation_point)
			{
				M44f trans_go, trans_back = id44();
				trans_go.set_column(-rotation_point.add_w(1), 4);
				trans_back.set_column(rotation_point.add_w(1), 4);
				move_mat = trans_back * move_mat * trans_go;
				//TODO: find out how rotation has to be changed
			}
			else
			{
				_rotation += rotation;
			}
		}
		_move(move_mat);
		// the following would also be affected by any rotation not around 0 0 0
		if (additive_translation)
		{
			_position += move_mat.get_column(4);
			_position.w = 0;
		}
		else
			_position = translation.add_w(0);
	}

	//////////
	// Mesh //
	//////////

	Mesh::Mesh(std::vector<Tri> _tris)
	{
		this->_tris = _tris;
		_position = _calc_center();
		_rotation = V3f(0, 0, 0);
	}

	Mesh::Mesh()
	{
		_tris.clear();
		_position = V4f(0, 0, 0, 0);
		_rotation = V3f(0, 0, 0);
	}

	Mesh::Mesh(std::string file_path, V3f pos)
	{
		SDL_RWops* file;
		uint32_t tris_num;
		float norm[3];
		V3f v[3];

		_tris.clear();
		file = SDL_RWFromFile(file_path.c_str(), "r");
		if (NULL == file)
			goto error;

		// first 80 bytes are header
		if (-1 == SDL_RWseek(file, 80, RW_SEEK_SET))
			goto error;

		// read number of triangles
		if (sizeof (tris_num) != SDL_RWread(file, &tris_num, 1, sizeof(tris_num)))
			goto error;

		for (uint32_t i = 0; i < tris_num; ++i)
		{
			// skip norm vector
			if (sizeof(norm) != SDL_RWread(file, &norm, 1, sizeof(norm)))
				goto error;
			// tri 1
			if (9 * sizeof (float) != SDL_RWread(file, v, 1, 9 * sizeof(float)))
				goto error;
			// skip attribute 16 byte
			if (-1 == SDL_RWseek(file, 2, RW_SEEK_CUR))
				goto error;

			_tris.push_back(Tri(v));
		}

		SDL_RWclose(file);
		_position = _calc_center();
		if (pos != _position.drop_w())
			move(pos, { 0,0,0 }, false);

		return;
	error:
		std::cout << SDL_GetError();
		return;
	}

	void Mesh::operator<<(Tri t) {
		_tris.push_back(t);
	}

	//////////
	// Cube //
	//////////

	Cube::Cube(V3f pos, float l)
	{
		_tris = _calc_tris(pos, l);
		_calc_center();
	}

	std::vector<Tri> Cube::_calc_tris(V3f pos, float l)
	{
		std::vector<Tri> _tris;
		V3f front[4];
		V3f back[4];
		front[0] = pos;
		front[1] = pos + V3f({ 1, 0, 0 });
		front[2] = pos + V3f({ 1, 1, 0 });
		front[3] = pos + V3f({ 0, l, 0 });
		back[0] = pos + V3f({ 0, 0, l });
		back[1] = pos + V3f({ l, 0, l });
		back[2] = pos + V3f({ l, l, l });
		back[3] = pos + V3f({ 0, l, l });

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

	Pyramid::Pyramid(V3f pos, float l, float h)
	{
		_tris = _calc_tris(pos, l, h);
		_calc_center();
	}

	std::vector<Tri> Pyramid::_calc_tris(V3f pos, float l, float h)
	{
		std::vector<Tri> _tris;
		V3f baseandtip[5];
		baseandtip[0] = pos;
		baseandtip[1] = pos + V3f(l, 0, 0);
		baseandtip[2] = pos + V3f(l, 0, l);
		baseandtip[3] = pos + V3f(0, 0, l);
		baseandtip[4] = pos + V3f(l / 2.0f, h, l / 2.0f);

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

	Icosahedron::Icosahedron(V3f pos, float l)
	{
		_tris = _calc_tris(pos, l);
		_calc_center();
	}

	std::vector<Tri> Icosahedron::_calc_tris(V3f pos, float l)
	{
		float phi = 2.61803f; // golden ratio
		std::vector<Tri> _tris;
		V3f displacement = V3f(pos);
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