#pragma once
#include "Mat.h"
#include <vector>

using namespace Mat;

namespace Geom
{
	class Tri {
	public:
		Tri(const V3f (&vecs)[3]);

		/*Tri operator*(float f);
		Tri operator/(float f);
		void operator*=(float f);
		void operator/=(float f);
		void operator=(Tri t);*/

		V4f normal(void);
		V4f vecs(int i);
		// ?
		V2f project(M44f);

	private:
		V4f _vecs[3];
		V4f _normal;

		V4f update_normal(void);
	};

	// TODO after triangle rendered
	class Mesh {
	public:
		std::vector<Tri> tris;
		void operator=(Mesh t);
		void operator<<(Tri t);
		/*void operator*(float f);
		void operator*=(Mesh t);
		void operator/(Mesh t);
		void operator/=(Mesh t);*/

		Mesh(std::vector<Tri> tris);
		Mesh();
		
	private:
	};

}