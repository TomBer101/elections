#include "party.h"

namespace elections
{
	party::party(const char* name, int serialNum, citizen* candidate)
		: _candidate(candidate), _delegators(nullptr), _serial_num(serialNum), _logSize(0), _phySize(0), sum_of_chairs(0), sum_of_votes(0)
	{
		copyName(name);
	}

	party::~party()
	{
		delete[] _name;
		for (int i = 0; i < _logSize; i++)
			delete _delegators[i].distDelegators;
		delete[] _delegators;
	}

	void party::copyName(const char* src)
	{
		int size = strlen(src);
		_name = new char[size + 1];
		for (int i = 0; i < size; ++i)
		{
			_name[i] = src[i];
		}
		_name[size] = '\0';
	}

	void party::addDelegatoer(citizen* newDelg, int district)
	{
		int flag = 0, i = 0;
		while (i < _logSize && flag == 0)
		{
			if (district == _delegators[i].distNum)
			{
				_delegators[i].distDelegators->add_to_list(newDelg);
				flag = 1;
			}
			i++;
		}

		if (flag == 0)
		{
			if (_logSize == _phySize)
			{
				partyData* tmp;
				_phySize = (_phySize + 1) * 2;
				tmp = new partyData[_phySize];
				for (int i = 0; i < _logSize; i++)
				{
					tmp[i].distNum = _delegators[i].distNum;
					tmp[i].distDelegators = _delegators[i].distDelegators;
				}

				delete[]_delegators;
				_delegators = tmp;
			}

			_delegators[_logSize].distNum = district;
			_delegators[_logSize].distDelegators = new citizen_list;
			_delegators[_logSize].distDelegators->add_to_list(newDelg);
			_logSize++;
		}

		newDelg->setPart(true);
	}

	void party::setChairs(int num)
	{
		sum_of_chairs += num;
	}

	void party::setVotes(int num)
	{
		sum_of_votes += num;
	}

	const citizen_list& party::getList(int dist_num) const
	{
		for (int i = 0; i < _logSize; i++)
		{
			if (_delegators[i].distNum == dist_num)
			{
				return *_delegators[i].distDelegators;
			}
		}
	}

	ostream& operator<<(ostream& os, const party& toPrint)
	{
		os << "party number is: " << toPrint._serial_num << ". Party name: " << toPrint._name << ". Head: " << toPrint._candidate->getName() << "." << endl;
		os << "Lists of deligators: " << endl;

		for (int i = 0; i < toPrint._logSize; i++)
		{
			os << " Delegators in district " << toPrint._delegators[i].distNum << " are: " << endl;
			toPrint._delegators[i].distDelegators->print_list();
		}
		return os;
	}


	bool party::has_delegators(int dist_num) const //check if a party has delegators in a specipic district
	{
		for (int i = 0; i < _logSize; i++)
		{
			if (_delegators[i].distNum == dist_num)
				return true;
		}

		return false;
	}
}

