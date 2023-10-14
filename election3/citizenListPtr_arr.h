#pragma once
#include "citizen_list.h"

namespace elections
{
	class distptr_arr;

	class citizenListPtr_arr
	{
	private:
		citizen_list** arr;
		int logSize = 0;
		int phy_size = 0;

		void resize();

	public:
		citizenListPtr_arr();
		~citizenListPtr_arr();

		int getSize()const { return logSize; }
		citizen* add_citizien(const citizen& new_citizen); // UPDATED
		bool add_list_ptr(); // open a new needed list.

		citizen_list& operator[](int index)const;

	};
}


