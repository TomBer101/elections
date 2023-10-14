#pragma once
#include "District.h"

namespace elections
{
	class distptr_arr
	{
	private:
		district** arr;
		int  logSize = 0; //each dist number will be current distlog
		int phySize = 0;

		void resize();
	public:
		distptr_arr();
		~distptr_arr();

		void add_dist(int chairs, const char* name);
		bool add_legal_citizen_to_dist(int dist, citizen* loc);
		const int getNumOfDistricts() const { return logSize; }

		district& operator[](int ind) const;

	};
}


