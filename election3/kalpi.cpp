#include "kalpi.h"


namespace elections {

	kalpi::kalpi()
		: amount_of_votes(0), _kalpi_arr(nullptr), _kalpi_logSize(0), _remainders_arr(nullptr), _winnig_party_in_dist(-1)
	{
	}
	kalpi::~kalpi()
	{
		delete[] _remainders_arr;
		delete[] _kalpi_arr;
	}

	void kalpi::resizeBox(int partyLog) // if there is a new party
	{
		int i;
		box* tmp_box = new box[partyLog];
		for (i = 0; i < partyLog - 1; i++)
		{
			tmp_box[i] = _kalpi_arr[i];
		}

		tmp_box[i].chairs = 0;
		tmp_box[i].counter = 0;

		delete[]_kalpi_arr;
		_kalpi_arr = tmp_box;

		_kalpi_logSize = partyLog;
	}

	void kalpi::addVote(int party)
	{
		bool flag = false;

		for (int i = 0; i < _kalpi_logSize && !flag; i++)
		{
			if (i == party)
			{
				_kalpi_arr[i].counter++;
				flag = true;
			}
		}

		amount_of_votes++;
	}

	void kalpi::calc_chairs(int _chairs)
	{
		float remain, deleg_per_vote;
		int chair, count = _chairs, j = 0;

		_remainders_arr = new chairs_remainders[_kalpi_logSize];

		deleg_per_vote = (static_cast<float>(amount_of_votes / static_cast<float>(_chairs)));
		//deleg_per_vote=allvotes/num of chairs in district - sets how many votes need to get a chair

		for (int i = 0; i < _kalpi_logSize; i++)
		{
			chair = static_cast<int>(_kalpi_arr[i].counter / deleg_per_vote);
			//sets how many chairs the party gets - the intiger part
			remain = static_cast<float>((static_cast<float>(_kalpi_arr[i].counter) / deleg_per_vote) - chair);
			//sets how many chairs the party gets - the float part
			_kalpi_arr[i].chairs = chair;
			_remainders_arr[i].remain = remain;
			_remainders_arr[i].party = i;
			count -= chair;
		}

		bubbleSort(_remainders_arr); //sorts the remains array

		while (count > 0) //if there are stil free chairs devide them
		{
			if (_remainders_arr[j].remain > 0)
				_kalpi_arr[_remainders_arr[j].party].chairs++;
			j++;
			count--;
		}
	}

	void kalpi::bubbleSort(chairs_remainders* remainders)
	{
		int i, j;
		for (i = 0; i < _kalpi_logSize - 1; i++)
		{
			for (j = 0; j < _kalpi_logSize - i - 1; j++)
			{
				if (remainders[j].remain < remainders[j + 1].remain)
				{
					chairs_remainders tmpRemain = remainders[j];
					remainders[j] = remainders[j + 1];
					remainders[j + 1] = tmpRemain;
				}
			}
		}
	}

	const int kalpi::getWinParty()
	{
		int i, winParty;
		if (_kalpi_logSize == 0 || amount_of_votes == 0)
			return -1;
		else
		{
			box tmp_win_party = _kalpi_arr[0]; //if tie the party with the smalles serial_num wins
			winParty = 0;
			for (i = 0; i < _kalpi_logSize; i++)
			{
				if (_kalpi_arr[i].counter > tmp_win_party.counter)
				{
					tmp_win_party = _kalpi_arr[i];
					winParty = i;
				}
			}
			return winParty;
		}
	}


}
