#pragma once
#include <iostream>

using namespace std;

namespace elections
{
	class district;
	class citizen
	{
	private:
		char* _name;
		char _ID[10];
		int _year_of_birth;
		int _district;
		district* city;

		bool has_a_part;
		bool _vote;

		void copyName(const char* src);
	public:
		citizen(const char* name, const char* id, int year, int dist);
		citizen(const citizen& other);
		~citizen();

		const char* getID()const { return _ID; }
		const char* getName()const { return _name; }

		const int getDist() const { return _district; }
		const int getYear()const { return _year_of_birth; }

		const bool getVoteStat() const { return _vote; }
		const bool getPart()const { return has_a_part; }
		bool operator==(const char* ID) const;

		void setPart(bool work) { has_a_part = work; }
		void set_vote_stat(bool vote);
		void setCity(const district* new_city);

		friend ostream& operator<<(ostream& os, const citizen& person);

	};
}