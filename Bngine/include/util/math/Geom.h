#pragma once
#include "Mat.h"
#include "Camera.h"
#include <vector>

using namespace Mat;

namespace Bngine
{
	struct Tri2D {
		V2f vertices[3];
	};

	class Tri {
	public:
		Tri(const V3f(&vecs)[3]);
		V4f normal(void);
		V4f vecs(int i);
		float area(void);
		void move(V4f displacement, M44f& move_mat);
		Tri2D project(Camera c);

	private:
		V4f _vecs[3];
		V4f _normal;

		V4f _update_normal(void);
	};

	class Geom {
	public:
		std::vector<Tri> tris(void);
		std::vector<Tri2D> project(Camera c);
		V4f position();
		V3f rotation();
		void move(V3f translation, V3f rotation, bool additive_translation=true, V3f rotation_point = { 0,0,0 });

	protected:
		std::vector<Tri> _tris;
		V4f _position;
		V3f _rotation;
		V4f _calc_center(void);
		void _move(M44f& move_mat);
	};

	// TODO after triangle rendered
	class Mesh : public Geom {
	public:
		Mesh(std::vector<Tri> _tris);
		Mesh(std::string file_path, V3f pos);
		Mesh();

		void operator<<(Tri t);
	};

	class Cube : public Geom {
	public:
		// TODO add rotation m33f
		Cube(V3f pos, float l);

	private:
		std::vector<Tri> _calc_tris(V3f pos, float l);

	};

	class Pyramid : public Geom {
	public:
		// TODO add rotation m33f
		Pyramid(V3f pos, float l, float h);

	private:
		std::vector<Tri> _calc_tris(V3f pos, float l, float h);

	};

	class Icosahedron : public Geom {
	public:
		// TODO add rotation m33f
		Icosahedron(V3f pos, float l);

	private:
		std::vector<Tri> _calc_tris(V3f pos, float l);
	};

}