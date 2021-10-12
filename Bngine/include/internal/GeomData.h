#pragma once
#include "util/math/Geom.h"
#include <unordered_map>

namespace Bngine {

	struct index_info {
		int pos;
		int rot;
		int tri_start;
		int tri_end;
	};

	struct GeomData {
		std::vector<Tri> tris;
		std::vector<V4f> pos;
		std::vector<V3f> rot;

		V4f& get_pos(uint64_t id);
		V3f& get_rot(uint64_t id);
		bool get_tris(uint64_t id, std::vector<Tri>::iterator& out_start, std::vector<Tri>::iterator& out_end);

		std::unordered_map<uint64_t, index_info> indices;

		static GeomData& getInstance();

		uint64_t insert(std::vector<Tri>& tris, V4f pos, V3f rot);

		bool remove(uint64_t id);

		static uint64_t _next_id;
	};

}
