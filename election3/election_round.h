#pragma once

#include "partyptr_arr.h"
#include "citizenListPtr_arr.h"
#include "distptr_arr.h"

namespace elections
{
#define YEAR 2020
#define MONTH 9
#define DAY 25

	class election_round
	{
	private:
		int day, month, year;

		citizenListPtr_arr all_citizen;// each cell is the same index as a district.

		distptr_arr all_dist;

		partyptr_arr all_parties;

		// private methode //
		const citizen* findCitizen(const citizen& new_citizen); // added const because of list.getCitizen
		const citizen* findCitizen(const char* ID);

		bool findDist(const char* name);
		bool findParty(const char* name);

		bool findParty(const int serial_num);
		const district* findDist(const int serial_num);

	public:

		election_round(int _day, int _month, int _year);
		~election_round();

		bool addDistrict(const char* name, int num);
		bool addCitizen(const char* name, const char* ID, int year, int dist);
		int addParty(const char* name, const char* ID);
		int addDeligate(const char* ID, int party, int dist);

		void showAllDistrict()const;
		void showAllCitizen()const;
		void showAllParties()const;

		int addVote(const char* id, int party_num);

		void showResults(); //when user press 9
	};
}


