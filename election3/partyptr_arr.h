#pragma once
#include "party.h"

namespace elections
{
	class partyptr_arr
	{
	private:
		party** arr;
		int partyLog = 0; // each party number, will be the current partylog
		int partyPhy = 0;

		void QuickSort(party** tmp, int left, int right) const;
		int partition(party** arr, int left, int right) const;

		void resize();

	public:
		partyptr_arr();
		~partyptr_arr();

		void add_party(const char* name, citizen* candi);
		void add_citizen_as_deligator(int dist, int party, citizen* loc);

		const int getSize() const { return partyLog; } // new
		party& operator[](int ind)const;
		void print_by_order() const;
	};

}


