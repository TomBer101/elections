#pragma once 
#include "citizen_list.h"


namespace elections
{
	class party
	{
	private:
		struct partyData
		{
			int distNum;
			citizen_list* distDelegators = nullptr;
		};

		char* _name;
		int _serial_num;
		const citizen* _candidate;
		partyData* _delegators;
		int _logSize, _phySize, sum_of_chairs, sum_of_votes;

		void copyName(const char* src);

	public:
		party(const char* name, int serialNum, citizen* candidate);
		~party();
		const citizen* getCndidate() const { return _candidate; }
		const char* getName() const { return _name; }
		const int getSerialNum() const { return _serial_num; }
		const int getDelgSize() const { return _logSize; }
		int getChairs() const { return sum_of_chairs; }
		int const getVotes() const { return sum_of_votes; } //how many votes the party get from all districts

		void addDelegatoer(citizen* newDelg, int district);
		void setChairs(int num);
		void setVotes(int num);
		const citizen_list& getList(int dist_num) const;
		bool has_delegators(int dist_num) const;

		friend ostream& operator<<(ostream& os, const party& toPrint);


	};
}


