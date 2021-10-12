#include "..\..\include\internal\GeomData.h"

namespace Bngine{
	
	uint64_t GeomData::_next_id = 0;

	V4f& GeomData::get_pos(uint64_t id)
	{
		return pos[indices[id].pos];
	}

	V3f& GeomData::get_rot(uint64_t id)
	{
		return rot[indices[id].rot];
	}

	bool GeomData::get_tris(uint64_t id, std::vector<Tri>::iterator& out_start, std::vector<Tri>::iterator& out_end)
	{
		out_start = this->tris.begin() + indices[id].tri_start;
		out_end = this->tris.begin() + indices[id].tri_end;
		// TODO: maybe catch access errors here and return false
		return true;
	}

	GeomData& GeomData::getInstance()
	{
		static GeomData self;
		return self;
	}

	uint64_t GeomData::insert(std::vector<Tri>& tris, V4f pos, V3f rot)
	{
		indices[_next_id].tri_start = this->tris.size();
		indices[_next_id].tri_end = indices[_next_id].tri_start + this->tris.size();
		this->tris.insert(this->tris.end(), tris.begin(), tris.end());

		indices[_next_id].pos = this->pos.size();
		indices[_next_id].rot = this->rot.size();

		this->pos.push_back(pos);
		this->rot.push_back(rot);

		return _next_id++;
	}

	bool GeomData::remove(uint64_t id)
	{
		//TODO
		return false;
	}

}
