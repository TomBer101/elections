#include "District.h"

namespace elections
{
	district::district(int chairs, int logSize, const char* name)
		: _chairs(chairs), _serial_num(logSize), _win_party(-1)
	{
		copyName(name);
		delegators = new citizen * [chairs];
		for (int i = 0; i < chairs; i++)
			delegators[i] = nullptr;
	}

	district::~district()
	{
		delete[] _name;

		for (int i = 0; i < _chairs; i++)
		{
			if (delegators[i] != nullptr)
				delete delegators[i];
		}
		delete[] delegators;
	}

	void district::show_delegators(const partyptr_arr& all_party) const
	{
		int vote_sum = dist_kalpi.get_amount_of_votes();
		int curr = 0;

		for (int i = 0; i < kalpi_size(); i++)
		{
			cout << "Delegators from " << all_party[i].getName() << " are: " << endl;
			for (int j = 0; j < party_chairs(i); j++)
			{
				cout << delegators[curr]->getName() << endl;
				curr++;
			}
			cout << "With " << party_votes(i);
			cout << " (" << (static_cast<float>(party_votes(i)) / static_cast<float>(vote_sum)) * 100 << "% of the votes)" << endl;
		}
	}

	bool district::set_delegators(const partyptr_arr& all_party)
	{
		currChair = 0; // The current cell to enter a deligator

		for (int i = 0; i < kalpi_size(); i++) // go through all relevant parties of this district
		{
			if (party_votes(i) != 0)
			{
				party& tmpParty = all_party[i]; // get referance to the current party from the main parties array
				if (!tmpParty.has_delegators(_serial_num))
				{
					cout << "The party " << tmpParty.getName() << " does not have enough representors for district " << _name << endl;
					return false;
				}
				const citizen_list& tmpList = tmpParty.getList(_serial_num);
				if (tmpList.getSize() < party_chairs(i))
				{
					cout << "The party " << tmpParty.getName() << " does not have enough representors for district " << _name << endl;
					return false;
				}
				tmpParty.setVotes(party_votes(i)); // add the votes of this district to the party
				tmpList.add_delegators_to_arr(delegators, party_chairs(i), currChair);
			}
		}
		return true;
	}

	void district::copyName(const char* src)
	{
		int size = strlen(src);
		_name = new char[size + 1];
		for (int i = 0; i < size; ++i)
		{
			_name[i] = src[i];
		}
		_name[size] = '\0';
	}

	const float district::getVotersPrecent() const //calculates the voters precent in the district
	{
		return (static_cast<float>((dist_kalpi.get_amount_of_votes()) / static_cast<float>(voters.getSize())) * 100);
	}

	bool district::add_citizen_to_voters(const citizen* loc) //add citizen to all legal citizens in dist
	{
		return voters.add_to_list(loc);
	}

	void district::calc_chairs_dist() //calls to kalpi's method which calculates the chairs of each party in district
	{
		dist_kalpi.calc_chairs(_chairs);
	}

	ostream& operator<<(ostream& os, const district& dist) //new . section 5
	{
		os << "District number: " << dist._serial_num << ". District name: " << dist._name << ". Amount of chair: " << dist._chairs << endl;
		return os;
	}
}
