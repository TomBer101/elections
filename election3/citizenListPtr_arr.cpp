#include "citizenListPtr_arr.h"
#include "distptr_arr.h"

namespace elections
{
	void citizenListPtr_arr::resize()
	{
		citizen_list** tmp = new citizen_list * [phy_size * 2 + 1];

		for (int i = 0; i < logSize; i++)
			tmp[i] = arr[i];

		delete[] arr;
		arr = tmp;
		this->phy_size = phy_size * 2 + 1;

	}

	citizenListPtr_arr::citizenListPtr_arr()
	{
		arr = nullptr;
	}

	citizenListPtr_arr::~citizenListPtr_arr()
	{
		for (int i = 0; i < logSize; i++)
		{
			int size = arr[i]->getSize();
			for (int j = 0; j < size; j++)
			{
				delete arr[i]->getCitizen(j);
			}
			delete arr[i];
		}
		delete arr;
	}

	citizen* citizenListPtr_arr::add_citizien(const citizen& new_citizen)
	{
		int dist = new_citizen.getDist();

		citizen_list& tmp = *arr[dist];
		return tmp.add_to_list(new_citizen);
	}

	bool citizenListPtr_arr::add_list_ptr()
	{
		if (logSize == phy_size)
		{
			resize();
		}
		arr[logSize] = new citizen_list();
		logSize++;

		return true;

	}

	citizen_list& citizenListPtr_arr::operator[](int index)const
	{
		return *arr[index];
	}


}
