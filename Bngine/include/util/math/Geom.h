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

		/*Tri operator*(float f);
		Tri operator/(float f);
		void operator*=(float f);
		void operator/=(float f);
		void operator=(Tri t);*/

		V4f normal(void);
		V4f vecs(int i);
		float area(void);
		void move(V4f displacement, M44f& move_mat);
		// ?
		//V2f project(M44f);
		Tri2D project(Camera c);

	private:
		V4f _vecs[3];
		V4f _normal;

		V4f update_normal(void);
	};

	class Geom {
	public:
		std::vector<Tri> tris();
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
		Mesh(std::string file_path, float x, float y, float z);
		Mesh();

		void operator<<(Tri t);
	};

	class Cube : public Geom {
	public:
		// TODO add rotation m33f
		Cube(V3f pos, float l);
		Cube(float x, float y, float z, float l);

	private:
		std::vector<Tri> _calc_tris(float x, float y, float z, float l);

	};

	class Pyramid : public Geom {
	public:
		// TODO add rotation m33f
		Pyramid(float x, float y, float z, float l, float h);

	private:
		std::vector<Tri> _calc_tris(float x, float y, float z, float l, float h);

	};

	class Icosahedron : public Geom {
	public:
		// TODO add rotation m33f
		Icosahedron(float x, float y, float z, float l);

	private:
		std::vector<Tri> _calc_tris(float x, float y, float z, float l);
	};

}