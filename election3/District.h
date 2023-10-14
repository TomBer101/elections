#pragma once
#include "citizen_list.h"
#include "partyptr_arr.h"
#include "kalpi.h"

namespace elections
{
	class partyptr_arr;

	class district
	{
	private:

		int _serial_num;
		char* _name;
		const int _chairs;
		int _win_party;

		kalpi dist_kalpi;

		citizen_list voters;
		citizen** delegators;
		int currChair = 0; //how many chairs alreay taken

		void copyName(const char* src);

	public:

		district(int chairs, int logSize, const char* name);
		~district();

		const float getVotersPrecent() const;
		const int getChairs() const { return _chairs; }
		const int getSerialNum() const { return _serial_num; }
		const char* getName() const { return _name; }
		const int get_amount_of_voters() { return dist_kalpi.get_amount_of_votes(); }
		const int getWinParty() { return dist_kalpi.getWinParty(); }
		kalpi& get_kalpi() { return dist_kalpi; }

		const int kalpi_size() const { return dist_kalpi.get_kalpi_size(); }
		const int party_chairs(int party) const { return dist_kalpi.get_party_kalpi_arr(party).chairs; }
		const int party_votes(int party) const { return dist_kalpi.get_party_kalpi_arr(party).counter; }

		bool add_citizen_to_voters(const citizen* loc);
		void calc_chairs_dist();
		void show_delegators(const partyptr_arr& all_party) const;
		bool set_delegators(const partyptr_arr& all_party);
		friend ostream& operator<<(ostream& os, const district& dist);



	};
}


