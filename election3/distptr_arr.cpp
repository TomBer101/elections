#include "distptr_arr.h"


namespace elections
{
	void distptr_arr::resize()
	{
		district** tmp = new district * [phySize * 2 + 1];

		for (int i = 0; i < logSize; i++)
			tmp[i] = arr[i];


		delete[] arr;
		arr = tmp;
		this->phySize = phySize * 2 + 1;
	}

	elections::distptr_arr::distptr_arr()
	{
		arr = nullptr;
	}

	distptr_arr::~distptr_arr()
	{
		for (int i = 0; i < logSize; i++)
		{
			delete arr[i];
		}
		delete[] arr;
	}

	void distptr_arr::add_dist(int chairs, const char* name)
	{
		if (logSize == phySize)
		{
			resize();
		}
		arr[logSize] = new district(chairs, logSize, name);
		logSize++;
	}

	bool distptr_arr::add_legal_citizen_to_dist(int dist, citizen* loc)
	{
		return arr[dist]->add_citizen_to_voters(loc);
	}

	district& distptr_arr:: operator[](int ind) const
	{
		return *arr[ind];
	}

}

